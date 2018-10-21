
/*
	2018.06.18
	Created by AcrylicShrimp.
*/

#include "ReduceSum.h"

namespace TinNet::GraphNode
{
	ReduceSum::ReduceSum(Graph *pGraph, const std::string &sName, const std::vector<bool> &sAxis, bool bSqueeze) :
		FullNode(pGraph, sName),
		sAxis{sAxis},
		bSqueeze{bSqueeze}
	{
		//Empty.
	}
	
	Shape ReduceSum::shape() const
	{
		return this->sShape;
	}

	std::string ReduceSum::type() const
	{
		return ReduceSum::typeName();
	}

	void ReduceSum::notifyShapeUpdated()
	{
		if (this->sAxis.size() != this->sInputList.front()->shape().rank())
			this->sAxis.resize(this->sInputList.front()->shape().rank(), true);

		this->sUnsqueezedShape = this->sInputList.front()->shape();

		for (std::size_t nIndex{0}, nRank{this->sUnsqueezedShape.rank()}; nIndex < nRank; ++nIndex)
			if (this->sAxis[nIndex])
				this->sUnsqueezedShape.set(nIndex, 1);

		this->sShape = this->bSqueeze ? this->sUnsqueezedShape.squeeze() : this->sUnsqueezedShape;
		this->sIterator.init(this->sInputList.front()->shape(), Accessor{this->sInputList.front()->shape()}, Accessor{this->sUnsqueezedShape});

		this->FullNode::notifyShapeUpdated();
	}

	void ReduceSum::forwardPass(Cache sDestination)
	{
		auto sLeft{this->sInputList.front()->forward()};

		sDestination.zero();

		for (this->sIterator.prepare(); this->sIterator; ++this->sIterator)
			sDestination[this->sIterator.index<1>()] += sLeft[this->sIterator.index<0>()];
	}

	void ReduceSum::backwardPass(Cache sDestination, NodePtr pInput)
	{
		auto sGradient{this->backward()};

		for (this->sIterator.prepare(); this->sIterator; ++this->sIterator)
			sDestination[this->sIterator.index<0>()] += sGradient[this->sIterator.index<1>()];
	}
}