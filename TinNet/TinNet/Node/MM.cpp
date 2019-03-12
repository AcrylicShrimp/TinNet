
/*
	2019.03.11
	Created by AcrylicShrimp.
*/

#include "MM.h"

namespace TinNet::Node
{
	MM::MM(std::string_view sName) :
		Node(sName),
		sInputLeft{this, "left", [this](const auto *pDy) { return this->backwardOpLeft(pDy); }},
		sInputRight{this, "right", [this](const auto *pDy) { return this->backwardOpRight(pDy); }}
	{
		this->sNodeInputMap["left"] = &this->sInputLeft;
		this->sNodeInputMap["right"] = &this->sInputRight;
	}

	void MM::updateShape()
	{
		this->sShape = {this->sInputRight.pNode->shape()[0], this->sInputLeft.pNode->shape()[1]};
	}

	void MM::evaluate()
	{
		Compute::GEMM::multiply(
			this->sInputLeft.pNode->shape()[0],
			this->sShape[1],
			this->sShape[0],
			this->sInputLeft.pNode->evalOutput().output(),
			this->sInputRight.pNode->evalOutput().output(),
			this->sOutput.span());
	}

	Core::Span MM::backwardOpLeft(const Core::Node *pDy)
	{
		Compute::GEMM::dMultiplyLeft(
			this->sInputLeft.pNode->shape()[0],
			this->sShape[1],
			this->sShape[0],
			this->sInputLeft.pNode->evalGradient(pDy).output(),
			this->sInputRight.pNode->evalGradient(pDy).output(),
			this->sGradient.span());

		return this->sGradient.span();
	}

	Core::Span MM::backwardOpRight(const Core::Node *pDy)
	{
		Compute::GEMM::dMultiplyRight(
			this->sInputLeft.pNode->shape()[0],
			this->sShape[1],
			this->sShape[0],
			this->sInputLeft.pNode->evalGradient(pDy).output(),
			this->sInputRight.pNode->evalGradient(pDy).output(),
			this->sGradient.span());

		return this->sGradient.span();
	}
}