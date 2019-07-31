
/*
	2019.07.31
	Created by AcrylicShrimp.
*/

#include "Multiply.h"

namespace TinNet::Node
{
	TINNET_NODE_TYPE_DEF(Multiply)
	
	Multiply::Multiply(Core::Graph *pGraph, std::string_view sName) :
		Node(pGraph, sName),
		sInputLeft{this, "left", [this](const auto *pDy) { this->__backwardOpLeft(pDy); }},
		sInputRight{this, "right", [this](const auto *pDy) { this->__backwardOpRight(pDy); }}
	{
		this->sNodeInputMap["left"] = &this->sInputLeft;
		this->sNodeInputMap["right"] = &this->sInputRight;
	}
	
	void Multiply::__evaluateShape()
	{
		if (!this->sInputLeft)
			throw std::runtime_error{"no node attached at 'left'"};

		if (!this->sInputRight)
			throw std::runtime_error{"no node attached at 'right'"};

		if (this->sInputLeft.inputNode()->evalShape().shape() != this->sInputRight.inputNode()->evalShape().shape())
			throw std::runtime_error{"the shape of 'left' and 'right' must be equal"};

		this->sShape = this->sInputLeft.inputNode()->shape();
	}

	void Multiply::__evaluateOutput()
	{
		this->sInputLeft.inputNode()->evalOutput();
		this->sInputRight.inputNode()->evalOutput();

		for (std::size_t nIndex{0}, nMaxIndex{this->sOutput.size()}; nIndex < nMaxIndex; ++nIndex)
			this->sOutput.span()[nIndex] = this->sInputLeft.inputNode()->output()[nIndex] * this->sInputRight.inputNode()->output()[nIndex];
	}

	void Multiply::__backwardOpLeft(const Node *pDy)
	{
		this->sInputRight.inputNode()->evalOutput();
		this->evalGradient(pDy);

		for (std::size_t nIndex{0}, nMaxIndex{this->sInputLeft.inputNode()->gradient().length()}; nIndex < nMaxIndex; ++nIndex)
			this->sInputLeft.inputNode()->gradient()[nIndex] += this->sGradient.span()[nIndex] * this->sInputRight.inputNode()->output()[nIndex];
	}

	void Multiply::__backwardOpRight(const Node *pDy)
	{
		this->sInputLeft.inputNode()->evalOutput();
		this->evalGradient(pDy);

		for (std::size_t nIndex{0}, nMaxIndex{this->sInputRight.inputNode()->gradient().length()}; nIndex < nMaxIndex; ++nIndex)
			this->sInputRight.inputNode()->gradient()[nIndex] += this->sGradient.span()[nIndex] * this->sInputLeft.inputNode()->output()[nIndex];
	}
}