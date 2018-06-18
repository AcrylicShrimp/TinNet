
/*
	2018.06.19
	Created by AcrylicShrimp.
*/

#include "ReduceMean.h"

namespace TinNet::GraphNode
{
	ReduceMean::ReduceMean(Graph *pGraph, const std::string &sName, const std::vector<bool> &sAxis, bool bSqueeze) :
		FullNode(pGraph, sName),
		sAxis{sAxis},
		bSqueeze{bSqueeze}
	{
		//Empty.
	}

	const Shape &ReduceMean::shape() const
	{
		return this->sShape;
	}

	std::string ReduceMean::type() const
	{
		return ReduceMean::typeName();
	}

	void ReduceMean::notifyShapeUpdated()
	{
		if (this->sAxis.size() != this->sInputList.front()->shape().rank())
			this->sAxis.resize(this->sInputList.front()->shape().rank(), true);

		std::size_t nFactor{1};
		
		this->sUnsqueezedShape = this->sInputList.front()->shape();

		for (std::size_t nAxis{0}, nRank{this->sUnsqueezedShape.rank()}; nAxis < nRank; ++nAxis)
			if (this->sAxis[nAxis])
			{
				nFactor *= this->sUnsqueezedShape[nAxis];
				this->sUnsqueezedShape.set(nAxis, 1);
			}

		this->nFactor = 1.f / nFactor;
		this->sShape = this->bSqueeze ? this->sUnsqueezedShape.squeeze() : this->sUnsqueezedShape;
		this->sIterator.init(this->sInputList.front()->shape(), Accessor{this->sInputList.front()->shape()}, Accessor{this->sUnsqueezedShape});

		this->FullNode::notifyShapeUpdated();
	}

	void ReduceMean::forwardPass(Cache sDestination)
	{
		auto sLeft{this->sInputList.front()->forward()};

		sDestination.zero();

		for (this->sIterator.prepare(); this->sIterator; ++this->sIterator)
			sDestination[this->sIterator.index<1>()] += sLeft[this->sIterator.index<0>()];

		for (std::size_t nIndex{0}, nSize{sDestination.size()}; nIndex < nSize; ++nIndex)
			sDestination[nIndex] *= this->nFactor;
	}

	void ReduceMean::backwardPass(Cache sDestination, NodePtr pInput)
	{
		auto sGradient{this->backward()};

		for (this->sIterator.prepare(); this->sIterator; ++this->sIterator)
			sDestination[this->sIterator.index<0>()] += sGradient[this->sIterator.index<1>()] * this->nFactor;
	}
}