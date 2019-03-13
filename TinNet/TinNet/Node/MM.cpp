
/*
	2019.03.11
	Created by AcrylicShrimp.
*/

#include "MM.h"

namespace TinNet::Node
{
	MM::MM(std::string_view sName) :
		Node(sName),
		sInputLeft{this, "left", [this](const auto *pDy) { this->__backwardOpLeft(pDy); }},
		sInputRight{this, "right", [this](const auto *pDy) { this->__backwardOpRight(pDy); }}
	{
		this->sNodeInputMap["left"] = &this->sInputLeft;
		this->sNodeInputMap["right"] = &this->sInputRight;
	}

	void MM::__evaluateShape()
	{
		this->sShape = {this->sInputRight.inputNode()->shape()[0], this->sInputLeft.inputNode()->shape()[1]};
	}

	void MM::__evaluateOutput()
	{
		Compute::GEMM::multiply(
			this->sInputLeft.inputNode()->shape()[0],
			this->sShape[1],
			this->sShape[0],
			this->sInputLeft.inputNode()->evalOutput().output(),
			this->sInputRight.inputNode()->evalOutput().output(),
			this->sOutput.span());
	}

	void MM::__backwardOpLeft(const Node *pDy)
	{
		Compute::GEMM::dMultiplyAddLeft(
			this->sInputLeft.inputNode()->shape()[0],
			this->sShape[1],
			this->sShape[0],
			this->evalGradient(pDy).gradient(),
			this->sInputRight.inputNode()->evalOutput().output(),
			this->sInputLeft.inputNode()->gradient());
	}

	void MM::__backwardOpRight(const Node *pDy)
	{
		Compute::GEMM::dMultiplyAddRight(
			this->sInputLeft.inputNode()->shape()[0],
			this->sShape[1],
			this->sShape[0],
			this->evalGradient(pDy).gradient(),
			this->sInputLeft.inputNode()->evalOutput().output(),
			this->sInputRight.inputNode()->gradient());
	}
}