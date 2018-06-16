
/*
	2018.06.15
	Created by AcrylicShrimp.
*/

#include "Softmax.h"

namespace TinNet::Graph::Node
{
	Softmax::Softmax(const std::string &sName, Graph *pGraph, const std::vector<bool> &sAxis) :
		FullCachedGraphNode(sName, pGraph),
		sAxis{sAxis}
	{
		//Empty.
	}

	const Shape &Softmax::shape() const
	{
		return this->sBackwardList.front()->shape();
	}

	std::size_t Softmax::maxBackwardNodeCount() const
	{
		return 1;
	}

	void Softmax::initNode()
	{
		if (this->sAxis.empty())
			this->sAxis.resize(this->sBackwardList.front()->shape().rank(), true);

		if (this->sAxis.size() != this->sBackwardList.front()->shape().rank())
			throw std::invalid_argument("length of axis list must be equal to rank of shape");

		Shape sShape = this->sBackwardList.front()->shape();

		for (std::size_t nIndex{0}, nRank{sShape.rank()}; nIndex < nRank; ++nIndex)
			if (this->sAxis[nIndex])
				sShape.set(nIndex, 1);

		this->sIterator.init(this->sBackwardList.front()->shape(), Accessor{this->sBackwardList.front()->shape()}, Accessor{sShape});
		this->sSum.resize(sShape.element());
		this->sSumBackward.resize(sShape.element());
		this->sSumCache = this->sSum;
		this->sSumBackwardCache = this->sSumBackward;
	}

	void Softmax::forwardPass(Cache sDestination)
	{
		const auto &sLeft{this->sBackwardList.front()->forward()};

		auto nMax{.0f};

		for (auto nValue : sLeft)
			if (nMax < nValue)
				nMax = nValue;

		this->sSumCache.zero();

		for (this->sIterator.prepare(); this->sIterator; ++this->sIterator)
			this->sSumCache[this->sIterator.index<1>()] += std::exp(sLeft[this->sIterator.index<0>()] - nMax);

		for (auto &nSum : this->sSumCache)
			nSum = 1.f / (nSum + .0001f);

		for (this->sIterator.prepare(); this->sIterator; ++this->sIterator)
			sDestination[this->sIterator.index<0>()] = std::exp(sLeft[this->sIterator.index<0>()] - nMax) * this->sSumCache[this->sIterator.index<1>()];
	}

	void Softmax::backwardPass(GraphNode *pBackward, Cache sDestination)
	{
		const auto &sLeft{this->sBackwardList.front()->forward()};
		const auto &sForward{this->forward()};
		const auto &sBackward{this->backward()};

		auto nMax{.0f};

		for (auto nValue : sLeft)
			if (nMax < nValue)
				nMax = nValue;

		this->sSumBackwardCache.zero();

		for (this->sIterator.prepare(); this->sIterator; ++this->sIterator)
			this->sSumBackwardCache[this->sIterator.index<1>()] -= sBackward[this->sIterator.index<0>()] * std::exp(sLeft[this->sIterator.index<0>()] - nMax) / (this->sSumCache[this->sIterator.index<1>()] * this->sSumCache[this->sIterator.index<1>()]);

		for (this->sIterator.prepare(); this->sIterator; ++this->sIterator)
			sDestination[this->sIterator.index<0>()] = std::exp(sLeft[this->sIterator.index<0>()] - nMax) * (this->sSumBackwardCache[this->sIterator.index<1>()] + sBackward[this->sIterator.index<0>()] / this->sSumCache[this->sIterator.index<1>()]);
	}
}