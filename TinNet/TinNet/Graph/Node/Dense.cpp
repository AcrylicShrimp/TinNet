
/*
	2018.06.01
	Created by AcrylicShrimp.
*/

#include "Dense.h"

namespace TinNet::Graph::Node
{
	Dense::Dense(const std::string &sName, Graph *pGraph, std::size_t nFanOut) :
		VariableGraphNode(sName, pGraph),
		sInputShape{},
		sOutputShape{nFanOut},
		sWeightShape{}
	{
		//Empty.
	}

	const Shape &Dense::shape() const
	{
		return this->sOutputShape;
	}

	std::size_t Dense::maxBackwardNodeCount() const
	{
		return 1;
	}

	void Dense::initNode()
	{
		if (!this->sVariableSizeList.empty())
			return;

		if (2 < this->sBackwardList.front()->shape().rank())
			throw std::invalid_argument("need scalar or vector or matrix, not tensor");

		this->sInputShape = this->sBackwardList.front()->shape();

		if (this->sInputShape.rank() < 2)
			this->sInputShape = this->sInputShape.expand(2);

		Shape sBias{this->sOutputShape[0]};
		this->sOutputShape = {this->sInputShape[0], sBias[0]};
		this->sWeightShape = {this->sInputShape[1], sBias[0]};

		this->sBiasIterator.init(this->sOutputShape, Accessor{this->sOutputShape}, Accessor{sBias});
		this->sWeightIterator.init(this->sOutputShape, Accessor{this->sOutputShape}, Accessor{this->sInputShape}, Accessor{this->sWeightShape});

		this->variable(sBias.element());
		this->variable(this->sWeightShape.element());
	}

	void Dense::forwardPass(Cache sDestination)
	{
		for (this->sBiasIterator.prepare(); this->sBiasIterator; ++this->sBiasIterator)
			sDestination[this->sBiasIterator.index<0>()] = this->sVariableList.front()->sCache[this->sBiasIterator.index<1>()];

		GraphOp::matmulAccumulate(
			this->sInputShape,
			this->sWeightShape,
			this->sBackwardList.front()->forward(),
			this->sVariableList.back()->sCache,
			sDestination,
			this->sWeightIterator);
	}

	void Dense::backwardPass(GraphNode *pBackward, Cache sDestination)
	{
		GraphOp::dMatmulLeft(
			this->sInputShape,
			this->sWeightShape,
			this->backward(),
			this->sVariableList.back()->sCache,
			sDestination,
			this->sWeightIterator);
	}

	std::size_t Dense::fanIn() const
	{
		return this->sInputShape[1];
	}

	std::size_t Dense::fanOut() const
	{
		return this->sOutputShape[1];
	}

	void Dense::backwardVariablePass()
	{
		this->sVariableBackwardList.front()->sCache.zero();

		const auto &sBackward{this->backward()};

		for (this->sBiasIterator.prepare(); this->sBiasIterator; ++this->sBiasIterator)
			this->sVariableBackwardList.front()->sCache[this->sBiasIterator.index<1>()] += sBackward[this->sBiasIterator.index<0>()];

		GraphOp::dMatmulRight(
			this->sInputShape,
			this->sWeightShape,
			sBackward,
			this->sBackwardList.front()->forward(),
			this->sVariableBackwardList.back()->sCache,
			this->sWeightIterator);
	}
}