
/*
	2018.06.03
	Created by AcrylicShrimp.
*/

#include "ReduceSum.h"

namespace TinNet::Graph::Node
{
	ReduceSum::ReduceSum(const std::string &sName, Graph *pGraph, const std::vector<bool> &sAxis, bool bSqueeze) :
		FullCachedGraphNode(sName, pGraph),
		sShape{},
		sUnsqueezedShape{},
		sAxis{sAxis},
		bSqueeze{bSqueeze}
	{
		//Empty.
	}

	const Shape &ReduceSum::shape() const
	{
		return this->sShape;
	}

	std::size_t ReduceSum::maxBackwardNodeCount() const
	{
		return 1;
	}

	void ReduceSum::initNode()
	{
		if (this->sAxis.empty())
			this->sAxis.resize(this->sBackwardList.front()->shape().rank(), true);

		if (this->sAxis.size() != this->sBackwardList.front()->shape().rank())
			throw std::invalid_argument("length of axis list must be equal to rank of shape");
		else
		{
			this->sUnsqueezedShape = this->sBackwardList.front()->shape();

			for (std::size_t nIndex{0}, nRank{this->sUnsqueezedShape.rank()}; nIndex < nRank; ++nIndex)
				if (this->sAxis[nIndex])
					this->sUnsqueezedShape[nIndex] = 1;

			this->sShape = this->bSqueeze ? this->sUnsqueezedShape.squeeze() : this->sUnsqueezedShape;
		}

		this->sIterator.init(this->sBackwardList.front()->shape(), Accessor{this->sBackwardList.front()->shape()}, Accessor{this->sUnsqueezedShape});
	}

	void ReduceSum::forwardPass(Cache sDestination)
	{
		sDestination.zero();

		const auto &sLeft{this->sBackwardList.front()->forward()};

		for (this->sIterator.prepare(); this->sIterator; ++this->sIterator)
			sDestination[this->sIterator.index<1>()] += sLeft[this->sIterator.index<0>()];
	}

	void ReduceSum::backwardPass(GraphNode *pBackward, Cache sDestination)
	{
		sDestination.zero();

		const auto &sBackward{this->backward()};

		for (this->sIterator.prepare(); this->sIterator; ++this->sIterator)
			sDestination[this->sIterator.index<0>()] += sBackward[this->sIterator.index<1>()];
	}
}