
/*
	2018.06.19
	Created by AcrylicShrimp.
*/

#include "Softmax.h"

namespace TinNet::GraphNode
{
	Softmax::Softmax(Graph *pGraph, const std::string &sName, const std::vector<bool> &sAxis) :
		FullNode(pGraph, sName),
		sAxis{sAxis}
	{
		//Empty.
	}
	
	const Shape &Softmax::shape() const
	{
		return this->sInputList.front()->shape();
	}

	std::string Softmax::type() const
	{
		return Softmax::typeName();
	}

	void Softmax::notifyShapeUpdated()
	{
		if (this->sAxis.size() != this->sInputList.front()->shape().rank())
			this->sAxis.resize(this->sInputList.front()->shape().rank(), true);

		Shape sShape = this->sInputList.front()->shape();

		for (std::size_t nIndex{0}, nRank{sShape.rank()}; nIndex < nRank; ++nIndex)
			if (this->sAxis[nIndex])
				sShape.set(nIndex, 1);

		this->sIterator.init(this->sInputList.front()->shape(), Accessor{this->sInputList.front()->shape()}, Accessor{sShape});
		this->sSumReversed.resize(sShape.element());
		this->sSumGradient.resize(sShape.element());
		this->sSumReveredCache = this->sSumReversed;
		this->sSumGradientCache = this->sSumGradient;

		this->FullNode::notifyShapeUpdated();
	}

	void Softmax::forwardPass(Cache sDestination)
	{
		auto sLeft{this->sInputList.front()->forward()};

		auto nMax{.0f};

		for (auto nValue : sLeft)
			if (nMax < nValue)
				nMax = nValue;

		this->sSumReveredCache.zero();

		for (this->sIterator.prepare(); this->sIterator; ++this->sIterator)
			this->sSumReveredCache[this->sIterator.index<1>()] += std::exp(sLeft[this->sIterator.index<0>()] - nMax);

		for (auto &nSum : this->sSumReveredCache)
			nSum = 1.f / (nSum + .0001f);

		for (this->sIterator.prepare(); this->sIterator; ++this->sIterator)
			sDestination[this->sIterator.index<0>()] = std::exp(sLeft[this->sIterator.index<0>()] - nMax) * this->sSumReveredCache[this->sIterator.index<1>()];
	}

	void Softmax::backwardPass(Cache sDestination, NodePtr pInput)
	{
		auto sGradient{this->backward()};
		auto sLeft{this->sInputList.front()->forward()};

		this->forward();

		auto nMax{.0f};

		for (auto nValue : sLeft)
			if (nMax < nValue)
				nMax = nValue;

		this->sSumGradientCache.zero();

		for (this->sIterator.prepare(); this->sIterator; ++this->sIterator)
			this->sSumGradientCache[this->sIterator.index<1>()] -= sGradient[this->sIterator.index<0>()] * std::exp(sLeft[this->sIterator.index<0>()] - nMax) * this->sSumReveredCache[this->sIterator.index<1>()] * this->sSumReveredCache[this->sIterator.index<1>()];

		for (this->sIterator.prepare(); this->sIterator; ++this->sIterator)
			sDestination[this->sIterator.index<0>()] += std::exp(sLeft[this->sIterator.index<0>()] - nMax) * (this->sSumGradientCache[this->sIterator.index<1>()] + sGradient[this->sIterator.index<0>()] * this->sSumReveredCache[this->sIterator.index<1>()]);
	}
}