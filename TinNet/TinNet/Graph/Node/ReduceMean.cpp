
/*
	2018.06.03
	Created by AcrylicShrimp.
*/

#include "ReduceMean.h"

namespace TinNet::Graph::Node
{
	ReduceMean::ReduceMean(const std::string &sName, Graph *pGraph, const std::vector<bool> &sAxis, bool bSqueeze) :
		FullCachedGraphNode(sName, pGraph),
		sShape{},
		sUnsqueezedShape{},
		sAxis{sAxis},
		bSqueeze{bSqueeze}
	{
		//Empty.
	}

	const Shape &ReduceMean::shape() const
	{
		return this->sShape;
	}

	std::size_t ReduceMean::maxBackwardNodeCount() const
	{
		return 1;
	}

	void ReduceMean::initNode()
	{
		if (this->sAxis.empty())
			this->sAxis.resize(this->sBackwardList.front()->shape().rank(), true);

		if (this->sAxis.size() != this->sBackwardList.front()->shape().rank())
			throw std::invalid_argument("length of axis list must be equal to rank of shape");
		else
		{
			std::size_t nFactor{1};

			this->sUnsqueezedShape = this->sBackwardList.front()->shape();

			for (std::size_t nAxis{0}, nRank{this->sUnsqueezedShape.rank()}; nAxis < nRank; ++nAxis)
				if (this->sAxis[nAxis])
				{
					nFactor *= this->sUnsqueezedShape[nAxis];
					this->sUnsqueezedShape.set(nAxis, 1);
				}

			this->sShape = this->bSqueeze ? this->sUnsqueezedShape.squeeze() : this->sUnsqueezedShape;
			this->nFactor = 1.f / nFactor;
		}

		this->sIterator.init(this->sBackwardList.front()->shape(), Accessor{this->sBackwardList.front()->shape()}, Accessor{this->sUnsqueezedShape});
	}

	void ReduceMean::forwardPass(Cache sDestination)
	{
		sDestination.zero();

		const auto &sLeft{this->sBackwardList.front()->forward()};

		for (this->sIterator.prepare(); this->sIterator; ++this->sIterator)
			sDestination[this->sIterator.index<1>()] += sLeft[this->sIterator.index<0>()];

		for (std::size_t nIndex{0}, nSize{sDestination.size()}; nIndex < nSize; ++nIndex)
			sDestination[nIndex] *= this->nFactor;
	}

	void ReduceMean::backwardPass(GraphNode *pBackward, Cache sDestination)
	{
		sDestination.zero();

		const auto &sBackward{this->backward()};

		for (this->sIterator.prepare(); this->sIterator; ++this->sIterator)
			sDestination[this->sIterator.index<0>()] += this->nFactor * sBackward[this->sIterator.index<1>()];
	}
}