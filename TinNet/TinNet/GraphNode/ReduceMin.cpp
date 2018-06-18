
/*
	2018.06.19
	Created by AcrylicShrimp.
*/

#include "ReduceMin.h"

namespace TinNet::GraphNode
{
	ReduceMin::ReduceMin(Graph *pGraph, const std::string &sName, const std::vector<bool> &sAxis, bool bSqueeze) :
		FullNode(pGraph, sName),
		sAxis{sAxis},
		bSqueeze{bSqueeze}
	{
		//Empty.
	}

	const Shape &ReduceMin::shape() const
	{
		return this->sShape;
	}

	std::string ReduceMin::type() const
	{
		return ReduceMin::typeName();
	}

	void ReduceMin::notifyShapeUpdated()
	{
		if (this->sAxis.size() != this->sInputList.front()->shape().rank())
			this->sAxis.resize(this->sInputList.front()->shape().rank(), true);

		this->sUnsqueezedShape = this->sInputList.front()->shape();

		for (std::size_t nIndex{0}, nRank{this->sUnsqueezedShape.rank()}; nIndex < nRank; ++nIndex)
			if (this->sAxis[nIndex])
				this->sUnsqueezedShape.set(nIndex, 1);

		this->sIndex.resize(this->sUnsqueezedShape.element());
		this->sShape = this->bSqueeze ? this->sUnsqueezedShape.squeeze() : this->sUnsqueezedShape;
		this->sIterator.init(this->sInputList.front()->shape(), Accessor{this->sInputList.front()->shape()}, Accessor{this->sUnsqueezedShape});

		this->FullNode::notifyShapeUpdated();
	}

	void ReduceMin::forwardPass(Cache sDestination)
	{
		auto sLeft{this->sInputList.front()->forward()};

		sDestination.fill(std::numeric_limits<float>::max());

		float vTempValue[2];
		std::size_t vTempIndex[2];

		for (this->sIterator.prepare(); this->sIterator; ++this->sIterator)
		{
			vTempValue[0] = sDestination[this->sIterator.index<1>()];
			vTempValue[1] = sLeft[this->sIterator.index<0>()];
			sDestination[this->sIterator.index<1>()] = vTempValue[vTempValue[0] > vTempValue[1]];

			vTempIndex[0] = this->sIndex[this->sIterator.index<1>()];
			vTempIndex[1] = this->sIterator.index<0>();
			this->sIndex[this->sIterator.index<1>()] = vTempIndex[vTempValue[0] > vTempValue[1]];
		}
	}

	void ReduceMin::backwardPass(Cache sDestination, NodePtr pInput)
	{
		auto sGradient{this->backward()};

		this->forward();

		float vGradientTemp[2]{.0f, 1.f};

		for (this->sIterator.prepare(); this->sIterator; ++this->sIterator)
			sDestination[this->sIterator.index<0>()] += sGradient[this->sIterator.index<1>()] * vGradientTemp[this->sIndex[this->sIterator.index<1>()] == this->sIterator.index<0>()];
	}
}