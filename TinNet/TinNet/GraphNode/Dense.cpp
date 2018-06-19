
/*
	2018.06.19
	Created by AcrylicShrimp.
*/

#include "Dense.h"

namespace TinNet::GraphNode
{
	Dense::Dense(Graph *pGraph, const std::string &sName, std::size_t nFanOut) :
		VariableNode(pGraph, sName),
		nFanOut{nFanOut}
	{
		//Empty.
	}
	
	const Shape &Dense::shape() const
	{
		return this->sOutputShape;
	}

	std::string Dense::type() const
	{
		return Dense::typeName();
	}

	void Dense::notifyShapeUpdated()
	{
		if (!this->sVariableSizeList.empty())
		{
			this->VariableNode::notifyShapeUpdated();
			return;
		}

		this->sInputShape = this->sInputList.front()->shape();

		if (this->sInputShape.rank() < 2)
			this->sInputShape = this->sInputShape.expand(2);

		Shape sBias{this->nFanOut};
		this->sOutputShape = {this->sInputShape[0], sBias[0]};
		this->sWeightShape = {this->sInputShape[1], sBias[0]};

		this->sBiasIterator.init(this->sOutputShape, Accessor{this->sOutputShape}, Accessor{sBias});
		this->sWeightIterator.init(this->sOutputShape, Accessor{this->sOutputShape}, Accessor{this->sInputShape}, Accessor{this->sWeightShape});

		this->registerVariable(sBias.element());
		this->registerVariable(this->sWeightShape.element());

		this->VariableNode::notifyShapeUpdated();
	}

	std::size_t Dense::fanIn() const
	{
		return this->sInputShape[1];
	}

	std::size_t Dense::fanOut() const
	{
		return this->sOutputShape[1];
	}

	void Dense::initialize(std::function<float()> fInitializer)
	{
		this->sVariableList.front()->sCache.zero();
		//for (std::size_t nIndex{0}, nMaxIndex{this->sVariableSizeList.front()}; nIndex < nMaxIndex; ++nIndex)
		//	this->sVariableList.front()->sCache[nIndex] = fInitializer();

		for (std::size_t nIndex{0}, nMaxIndex{this->sVariableSizeList.back()}; nIndex < nMaxIndex; ++nIndex)
			this->sVariableList.back()->sCache[nIndex] = fInitializer();
	}

	void Dense::variablePass()
	{
		auto sGradient{this->backward()};

		this->sVariableGradientList.front()->sCache.zero();

		for (this->sBiasIterator.prepare(); this->sBiasIterator; ++this->sBiasIterator)
			this->sVariableGradientList.front()->sCache[this->sBiasIterator.index<1>()] += sGradient[this->sBiasIterator.index<0>()];

		GraphOp::dMatmulRightTransposedAVX(
			this->sInputShape,
			this->sWeightShape,
			sGradient,
			this->sInputList.front()->forward(),
			this->sVariableGradientList.back()->sCache,
			this->sWeightIterator);

		auto nFactor{1.f / this->sInputShape[0]};

		for (std::size_t nIndex{0}, nMaxIndex{this->sVariableSizeList.front()}; nIndex < nMaxIndex; ++nIndex)
			this->sVariableGradientList.front()->sCache[nIndex] *= nFactor;

		for (std::size_t nIndex{0}, nMaxIndex{this->sVariableSizeList.back()}; nIndex < nMaxIndex; ++nIndex)
			this->sVariableGradientList.back()->sCache[nIndex] *= nFactor;
	}

	void Dense::applyGradient(float nFactor)
	{
		for (std::size_t nIndex{0}, nMaxIndex{this->sVariableSizeList.front()}; nIndex < nMaxIndex; ++nIndex)
			this->sVariableList.front()->sCache[nIndex] += nFactor * this->sVariableGradientList.front()->sCache[nIndex];

		for (std::size_t nIndex{0}, nMaxIndex{this->sVariableSizeList.back()}; nIndex < nMaxIndex; ++nIndex)
			this->sVariableList.back()->sCache[nIndex] += nFactor * this->sVariableGradientList.back()->sCache[nIndex];
	}

	void Dense::forwardPass(Cache sDestination)
	{
		for (this->sBiasIterator.prepare(); this->sBiasIterator; ++this->sBiasIterator)
			sDestination[this->sBiasIterator.index<0>()] = this->sVariableList.front()->sCache[this->sBiasIterator.index<1>()];

		GraphOp::matmulAccumulateTransposedAVX(
			this->sInputShape,
			this->sWeightShape,
			this->sInputList.front()->forward(),
			this->sVariableList.back()->sCache,
			sDestination,
			this->sWeightIterator);
	}

	void Dense::backwardPass(Cache sDestination, NodePtr pInput)
	{
		GraphOp::dMatmulAccumulateLeftTransposedAVX(
			this->sInputShape,
			this->sWeightShape,
			this->backward(),
			this->sVariableList.back()->sCache,
			sDestination,
			this->sWeightIterator);
	}
}