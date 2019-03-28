
/*
	2019.03.27
	Created by AcrylicShrimp.
*/

#include "Dense.h"

namespace TinNet::Node
{
	TINNET_NODE_TYPE_DEF(Dense)

		Dense::Dense(Core::Graph *pGraph, std::string_view sName) :
		Node(pGraph, sName),
		sInput{this, "input", [this](const auto *pDy) { this->__backwardOpInput(pDy); }},
		sInputWeight{this, "weight", [this](const auto *pDy) { this->__backwardOpWeight(pDy); }},
		sInputBias{this, "bias", [this](const auto *pDy) { this->__backwardOpBias(pDy); }}
	{
		this->sNodeInputMap["input"] = &this->sInput;
		this->sNodeInputMap["weight"] = &this->sInputWeight;
		this->sNodeInputMap["bias"] = &this->sInputBias;
	}

	void Dense::__evaluateShape()
	{
		if (this->sInput.inputNode()->shape().rank() != 2)
			throw std::exception{"the rank of the input shape must be 2."};

		if (this->sInputWeight.inputNode()->shape().rank() != 2)
			throw std::exception{"the rank of the weight shape must be 2."};

		if (this->sInputBias.inputNode()->shape().rank() != 1)
			throw std::exception{"the rank of the bias shape must be 1."};

		if (this->sInput.inputNode()->shape()[0] != this->sInputWeight.inputNode()->shape()[1])
			throw std::exception{"the shape of the input and the weight is not compatible."};

		if (this->sInputWeight.inputNode()->shape()[0] != this->sInputBias.inputNode()->shape()[0])
			throw std::exception{"the shape of the weight and the bias is not compatible."};

		this->sShape = {this->sInputWeight.inputNode()->shape()[0], this->sInput.inputNode()->shape()[1]};
	}

	void Dense::__evaluateOutput()
	{
		for (std::size_t nIndex{0}, nMaxIndex{this->sShape[1]}, nWidth{this->sShape[0]}; nIndex < nMaxIndex; ++nIndex)
			this->sOutput.span().subSpan(nIndex * nWidth).copyFrom(this->sInputBias.inputNode()->evalOutput().output());

		Compute::GEMM::multiplyAdd(
			this->sInput.inputNode()->shape()[0],
			this->sShape[1],
			this->sShape[0],
			this->sInput.inputNode()->evalOutput().output(),
			this->sInputWeight.inputNode()->evalOutput().output(),
			this->sOutput.span());
	}

	void Dense::__backwardOpInput(const Node *pDy)
	{
		Compute::GEMM::dMultiplyAddLeft(
			this->sInput.inputNode()->shape()[0],
			this->sShape[1],
			this->sShape[0],
			this->evalGradient(pDy).gradient(),
			this->sInputWeight.inputNode()->evalOutput().output(),
			this->sInput.inputNode()->gradient());
	}

	void Dense::__backwardOpWeight(const Node *pDy)
	{
		Compute::GEMM::dMultiplyAddRight(
			this->sInput.inputNode()->shape()[0],
			this->sShape[1],
			this->sShape[0],
			this->evalGradient(pDy).gradient(),
			this->sInput.inputNode()->evalOutput().output(),
			this->sInputWeight.inputNode()->gradient());
	}
	
	void Dense::__backwardOpBias(const Node *pDy)
	{
		this->sInputBias.inputNode()->gradient().accumulateFrom(this->evalGradient(pDy).gradient());
	}
}