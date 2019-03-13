
/*
	2019.03.13
	Created by AcrylicShrimp.
*/

#include "Add.h"

namespace TinNet::Node
{
	Add::Add(std::string_view sName) :
		Node(sName),
		sInputLeft{this, "left", [this](const auto *pDy) { this->__backwardOpLeft(pDy); }},
		sInputRight{this, "right", [this](const auto *pDy) { this->__backwardOpRight(pDy); }}
	{
		this->sNodeInputMap["left"] = &this->sInputLeft;
		this->sNodeInputMap["right"] = &this->sInputRight;
	}

	void Add::__evaluateShape()
	{
		this->sShape = this->sInputLeft.inputNode()->shape();
	}

	void Add::__evaluateOutput()
	{
		this->sInputLeft.inputNode()->evalOutput();
		this->sInputRight.inputNode()->evalOutput();

		for (std::size_t nIndex{0}, nMaxIndex{this->sOutput.size()}; nIndex < nMaxIndex; ++nIndex)
			this->sOutput.span()[nIndex] = this->sInputLeft.inputNode()->output()[nIndex] + this->sInputRight.inputNode()->output()[nIndex];
	}

	void Add::__backwardOpLeft(const Node *pDy)
	{
		this->sInputLeft.inputNode()->gradient().accumulateFrom(this->evalGradient(pDy).gradient());
	}

	void Add::__backwardOpRight(const Node *pDy)
	{
		this->sInputRight.inputNode()->gradient().accumulateFrom(this->evalGradient(pDy).gradient());
	}
}