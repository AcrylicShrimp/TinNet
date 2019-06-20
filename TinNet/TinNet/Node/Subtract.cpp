
/*
	2019.03.27
	Created by AcrylicShrimp.
*/

#include "Subtract.h"

namespace TinNet::Node
{
	TINNET_NODE_TYPE_DEF(Subtract)

	Subtract::Subtract(Core::Graph *pGraph, std::string_view sName) :
		Node(pGraph, sName),
		sInputLeft{this, "left", [this](const auto *pDy) { this->__backwardOpLeft(pDy); }},
		sInputRight{this, "right", [this](const auto *pDy) { this->__backwardOpRight(pDy); }}
	{
		this->sNodeInputMap["left"] = &this->sInputLeft;
		this->sNodeInputMap["right"] = &this->sInputRight;
	}

	void Subtract::__evaluateShape()
	{
		if (!this->sInputLeft)
			throw std::runtime_error{"no node attached at 'left'"};

		if (!this->sInputRight)
			throw std::runtime_error{"no node attached at 'right'"};

		if (this->sInputLeft.inputNode()->evalShape().shape() != this->sInputRight.inputNode()->evalShape().shape())
			throw std::runtime_error{"the shape of 'left' and 'right' must be equal"};

		this->sShape = this->sInputLeft.inputNode()->shape();
	}

	void Subtract::__evaluateOutput()
	{
		this->sInputLeft.inputNode()->evalOutput();
		this->sInputRight.inputNode()->evalOutput();

		for (std::size_t nIndex{0}, nMaxIndex{this->sOutput.size()}; nIndex < nMaxIndex; ++nIndex)
			this->sOutput.span()[nIndex] = this->sInputLeft.inputNode()->output()[nIndex] + this->sInputRight.inputNode()->output()[nIndex];
	}

	void Subtract::__backwardOpLeft(const Node *pDy)
	{
		this->sInputLeft.inputNode()->gradient().accumulateFrom(this->evalGradient(pDy).gradient());
	}

	void Subtract::__backwardOpRight(const Node *pDy)
	{
		this->sInputRight.inputNode()->gradient().accumulateFrom(-1.f, this->evalGradient(pDy).gradient());
	}
}