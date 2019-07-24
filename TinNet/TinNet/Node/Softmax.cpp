
/*
	2019.06.22
	Created by AcrylicShrimp.
*/

#include "Softmax.h"

namespace TinNet::Node
{
	TINNET_NODE_TYPE_DEF(Softmax)
	
	Softmax::Softmax(Core::Graph *pGraph, std::string_view sName, const std::vector<bool> &sGroupAxis) :
		Node(pGraph, sName),
		sGroupAxis{sGroupAxis},
		sInputLogit{this, "logit", [this](const auto *pDy) { this->__backwardOp(pDy); }}
	{
		this->sNodeInputMap["logit"] = &this->sInputLogit;
	}
	
	void Softmax::__evaluateShape()
	{
		if (!this->sInputLogit)
			throw std::runtime_error{"no node attached at 'logit'"};

		const auto &sShape{this->sInputLogit.inputNode()->shape()};

		this->sShape = sShape;

		if (!this->sGroupAxis.size())
			return;

		if (this->sGroupAxis.size() == 1)
			return;

		if (this->sGroupAxis.size() != sShape.rank())
			throw std::runtime_error{"the length of 'group axis' must be equal to the rank of 'logit'"};

		std::vector<std::size_t> sMultipliedShape{1};

		for (std::size_t nIndex{0}, nMaxIndex{sShape.rank() - 1}; nIndex < nMaxIndex; ++nIndex)
			sMultipliedShape.emplace_back(sMultipliedShape.back() * sShape[nIndex]);

		this->sIndexFactorList.clear();

		std::size_t nSummationSize{this->sShape.size()};

		for (std::size_t nIndex{0}, nMaxIndex{this->sGroupAxis.size()}; nIndex < nMaxIndex; ++nIndex)
			if (this->sGroupAxis[nIndex])
				nSummationSize /= this->sShape[nIndex];
			else
				this->sIndexFactorList.emplace_back(sShape[nIndex], sMultipliedShape[nIndex], this->sIndexFactorList.size() ? std::get<0>(this->sIndexFactorList.back()) * std::get<2>(this->sIndexFactorList.back()) : 1);

		this->sSummation.resize(nSummationSize);
	}

	void Softmax::__evaluateOutput()
	{
		this->sInputLogit.inputNode()->evalOutput();

		auto nMaxInput{*this->sInputLogit.inputNode()->output().max()};

		if (!this->sGroupAxis.size())
		{
			auto nExpSumInv{.0f};

			for (auto nInputValue : this->sInputLogit.inputNode()->output())
				nExpSumInv += std::exp(nInputValue - nMaxInput);

			nExpSumInv = 1.f / (nExpSumInv + .0001f);

			for (std::size_t nIndex{0}, nMaxIndex{this->sInputLogit.inputNode()->output().length()}; nIndex < nMaxIndex; ++nIndex)
				this->sOutput.span()[nIndex] = nExpSumInv * std::exp(this->sInputLogit.inputNode()->output()[nIndex] - nMaxInput);

			return;
		}

		if (this->sGroupAxis.size() == 1)
		{
			if (this->sGroupAxis[0])
			{
				auto nExpSumInv{.0f};

				for (auto nInputValue : this->sInputLogit.inputNode()->output())
					nExpSumInv += std::exp(nInputValue - nMaxInput);

				nExpSumInv = 1.f / (nExpSumInv + .0001f);

				for (std::size_t nIndex{0}, nMaxIndex{this->sInputLogit.inputNode()->output().length()}; nIndex < nMaxIndex; ++nIndex)
					this->sOutput.span()[0] = nExpSumInv * std::exp(this->sInputLogit.inputNode()->output()[nIndex] - nMaxInput);
			}
			else
				this->sOutput.span().fillOne();

			return;
		}

		auto fReduceIndex{[this](std::size_t nIndex)
		{
			std::size_t nResult{0};

			for (const auto &sIndexFactorTuple : this->sIndexFactorList)
				nResult += nIndex / std::get<1>(sIndexFactorTuple) % std::get<0>(sIndexFactorTuple) * std::get<2>(sIndexFactorTuple);

			return nResult;
		}};

		this->sSummation.span().fillZero();

		for (std::size_t nIndex{0}, nMaxIndex{this->sInputLogit.inputNode()->output().length()}; nIndex < nMaxIndex; ++nIndex)
			this->sSummation.span()[fReduceIndex(nIndex)] += std::exp(this->sInputLogit.inputNode()->output()[nIndex] - nMaxInput);

		for (auto &nSummationValue : this->sSummation.span())
			nSummationValue = 1.f / (nSummationValue + .0001f);

		for (std::size_t nIndex{0}, nMaxIndex{this->sInputLogit.inputNode()->output().length()}; nIndex < nMaxIndex; ++nIndex)
			this->sOutput.span()[nIndex] = this->sSummation.span()[fReduceIndex(nIndex)] * std::exp(this->sInputLogit.inputNode()->output()[nIndex] - nMaxInput);
	}

	void Softmax::__backwardOp(const Node *pDy)
	{
		this->evalOutput();
		this->evalGradient(pDy);

		if (!this->sGroupAxis.size())
		{
			auto nSum{.0f};

			for (std::size_t nIndex{0}, nMaxIndex{this->sOutput.size()}; nIndex < nMaxIndex; ++nIndex)
				nSum += this->sGradient.span()[nIndex] * this->sOutput.span()[nIndex];

			for (std::size_t nIndex{0}, nMaxIndex{this->sOutput.size()}; nIndex < nMaxIndex; ++nIndex)
				this->sInputLogit.inputNode()->gradient()[nIndex] += this->sOutput.span()[nIndex] * (this->sGradient.span()[nIndex] - nSum);

			return;
		}

		if (this->sGroupAxis.size() == 1)
		{
			if (this->sGroupAxis[0])
			{
				auto nSum{.0f};

				for (std::size_t nIndex{0}, nMaxIndex{this->sOutput.size()}; nIndex < nMaxIndex; ++nIndex)
					nSum += this->sGradient.span()[nIndex] * this->sOutput.span()[nIndex];

				for (std::size_t nIndex{0}, nMaxIndex{this->sOutput.size()}; nIndex < nMaxIndex; ++nIndex)
					this->sInputLogit.inputNode()->gradient()[nIndex] += this->sOutput.span()[nIndex] * (this->sGradient.span()[nIndex] - nSum);
			}
			else
				this->sInputLogit.inputNode()->gradient().fillZero();

			return;
		}

		auto fReduceIndex{[this](std::size_t nIndex)
		{
			std::size_t nResult{0};

			for (const auto &sIndexFactorTuple : this->sIndexFactorList)
				nResult += nIndex / std::get<1>(sIndexFactorTuple) % std::get<0>(sIndexFactorTuple) * std::get<2>(sIndexFactorTuple);

			return nResult;
		}};

		this->sSummation.span().fillZero();

		for (std::size_t nIndex{0}, nMaxIndex{this->sOutput.size()}; nIndex < nMaxIndex; ++nIndex)
			this->sSummation.span()[fReduceIndex(nIndex)] += this->sGradient.span()[nIndex] * this->sOutput.span()[nIndex];

		for (std::size_t nIndex{0}, nMaxIndex{this->sOutput.size()}; nIndex < nMaxIndex; ++nIndex)
			this->sInputLogit.inputNode()->gradient()[nIndex] += this->sOutput.span()[nIndex] * (this->sGradient.span()[nIndex] - this->sSummation.span()[fReduceIndex(nIndex)]);
	}
}