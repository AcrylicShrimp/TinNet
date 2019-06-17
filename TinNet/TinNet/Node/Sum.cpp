
/*
	2019.03.31
	Created by AcrylicShrimp.
*/

#include "Sum.h"

namespace TinNet::Node
{
	TINNET_NODE_TYPE_DEF(Sum)

		Sum::Sum(Core::Graph *pGraph, std::string_view sName, bool bSqueeze, const std::vector<bool> &sReduceAxis) :
		Node(pGraph, sName),
		bSqueeze{bSqueeze},
		sInput{this, "input", [this](const auto *pDy) { this->__backwardOpInput(pDy); }},
		sReduceAxis{sReduceAxis}
	{
		this->sNodeInputMap["input"] = &this->sInput;
	}

	void Sum::__evaluateShape()
	{
		if (!this->sInput.inputNode())
			throw std::runtime_error{"no node attached at 'input'"};

		const auto &sShape{this->sInput.inputNode()->evalShape().shape()};

		if (!this->sReduceAxis.size())
		{
			this->sShape = {1};

			if (this->bSqueeze)
				this->sShape = this->sShape.squeeze();

			return;
		}

		if (this->sReduceAxis.size() == 1)
		{
			this->sShape = this->sReduceAxis[0] ? Core::Shape{1} : sShape;

			if (this->bSqueeze)
				this->sShape = this->sShape.squeeze();

			return;
		}

		if (this->sReduceAxis.size() != sShape.rank())
			throw std::runtime_error{"the length of 'reduce axis' must be equal to the rank of 'input'"};

		this->sShape = sShape;

		for (std::size_t nIndex{0}, nMaxIndex{this->sReduceAxis.size()}; nIndex < nMaxIndex; ++nIndex)
			if (this->sReduceAxis[nIndex])
				this->sShape[nIndex] = 1;

		if (this->bSqueeze)
			this->sShape = this->sShape.squeeze();
	}

	void Sum::__evaluateOutput()
	{
		this->sOutput.span().fillZero();

		if (!this->sReduceAxis.size())
		{
			for (std::size_t nIndex{0}, nMaxIndex{this->sInput.inputNode()->output().length()}; nIndex < nMaxIndex; ++nIndex)
				this->sOutput.span()[0] += this->sInput.inputNode()->output()[nIndex];

			return;
		}

		if (this->sReduceAxis.size() == 1)
		{
			if (this->sReduceAxis[0])
				for (std::size_t nIndex{0}, nMaxIndex{this->sInput.inputNode()->output().length()}; nIndex < nMaxIndex; ++nIndex)
					this->sOutput.span()[0] += this->sInput.inputNode()->output()[nIndex];
			else
				for (std::size_t nIndex{0}, nMaxIndex{this->sInput.inputNode()->output().length()}; nIndex < nMaxIndex; ++nIndex)
					this->sOutput.span()[nIndex] += this->sInput.inputNode()->output()[nIndex];

			return;
		}

		const auto &sShape{this->sInput.inputNode()->evalShape().shape()};

		if (sShape.rank() != this->sReduceAxis.size())
			throw std::runtime_error{"the rank of 'input' must be equal to the length of 'reduce axis'"};

		std::vector<std::size_t> sMultipliedShape{1};
		std::vector<std::tuple<std::size_t, std::size_t, std::size_t>> sIndexFactorList;

		for (std::size_t nIndex{0}, nMaxIndex{sShape.rank() - 1}; nIndex < nMaxIndex; ++nIndex)
			sMultipliedShape.emplace_back(sMultipliedShape.back() * sMultipliedShape[nIndex]);

		for (std::size_t nIndex{0}, nMaxIndex{sShape.rank()}; nIndex < nMaxIndex; ++nIndex)
			if (this->sReduceAxis[nIndex])
				sIndexFactorList.emplace_back(sMultipliedShape[nIndex], sMultipliedShape[nIndex + 1], sMultipliedShape[nIndex]);

		auto fReduceIndex{[&sIndexFactorList](std::size_t nIndex)
		{
			std::size_t nResult{nIndex};

			for (const auto &sIndexFactorTuple : sIndexFactorList)
				nResult -= nIndex / std::get<0>(sIndexFactorTuple) % std::get<1>(sIndexFactorTuple) * std::get<2>(sIndexFactorTuple);

			return nResult;
		}};

		for (std::size_t nIndex{0}, nMaxIndex{this->sInput.inputNode()->output().length()}; nIndex < nMaxIndex; ++nIndex)
			this->sOutput.span()[fReduceIndex(nIndex)] += this->sInput.inputNode()->output()[nIndex];
	}

	void Sum::__backwardOpInput(const Node *pDy)
	{
		this->evalGradient(pDy);

		if (!this->sReduceAxis.size())
		{
			for (std::size_t nIndex{0}, nMaxIndex{this->sInput.inputNode()->output().length()}; nIndex < nMaxIndex; ++nIndex)
				this->sInput.inputNode()->gradient()[nIndex] += this->sGradient.span()[0];

			return;
		}

		if (this->sReduceAxis.size() == 1)
		{
			if (this->sReduceAxis[0])
				for (std::size_t nIndex{0}, nMaxIndex{this->sInput.inputNode()->output().length()}; nIndex < nMaxIndex; ++nIndex)
					this->sInput.inputNode()->gradient()[nIndex] += this->sGradient.span()[0];
			else
				for (std::size_t nIndex{0}, nMaxIndex{this->sInput.inputNode()->output().length()}; nIndex < nMaxIndex; ++nIndex)
					this->sInput.inputNode()->gradient()[nIndex] += this->sGradient.span()[nIndex];

			return;
		}

		const auto &sShape{this->sInput.inputNode()->evalShape().shape()};

		if (sShape.rank() != this->sReduceAxis.size())
			throw std::runtime_error{"the rank of 'input' must be equal to the length of 'reduce axis'"};

		std::vector<std::size_t> sMultipliedShape{1};
		std::vector<std::tuple<std::size_t, std::size_t, std::size_t>> sIndexFactorList;

		for (std::size_t nIndex{0}, nMaxIndex{sShape.rank() - 1}; nIndex < nMaxIndex; ++nIndex)
			sMultipliedShape.emplace_back(sMultipliedShape.back() * sMultipliedShape[nIndex]);

		for (std::size_t nIndex{0}, nMaxIndex{sShape.rank()}; nIndex < nMaxIndex; ++nIndex)
			if (this->sReduceAxis[nIndex])
				sIndexFactorList.emplace_back(sMultipliedShape[nIndex], sMultipliedShape[nIndex + 1], sMultipliedShape[nIndex]);

		auto fReduceIndex{[&sIndexFactorList](std::size_t nIndex)
		{
			std::size_t nResult{nIndex};

			for (const auto &sIndexFactorTuple : sIndexFactorList)
				nResult -= nIndex / std::get<0>(sIndexFactorTuple) % std::get<1>(sIndexFactorTuple) * std::get<2>(sIndexFactorTuple);

			return nResult;
		}};

		for (std::size_t nIndex{0}, nMaxIndex{this->sInput.inputNode()->output().length()}; nIndex < nMaxIndex; ++nIndex)
			this->sInput.inputNode()->gradient()[nIndex] += this->sGradient.span()[fReduceIndex(nIndex)];
	}
}