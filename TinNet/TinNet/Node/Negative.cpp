
/*
	2019.07.31
	Created by AcrylicShrimp.
*/

#include "Negative.h"

namespace TinNet::Node
{
	TINNET_NODE_TYPE_DEF(Negative)
	
	Negative::Negative(Core::Graph *pGraph, std::string_view sName) :
		Node(pGraph, sName),
		sInput{this, "input", [this](const auto *pDy) { this->__backwardOp(pDy); }}
	{
		this->sNodeInputMap["input"] = &this->sInput;
	}
	
	void Negative::__evaluateShape()
	{
		if (!this->sInput)
			throw std::runtime_error{"no node attached at 'input'"};

		this->sShape = this->sInput.inputNode()->shape();
	}

	void Negative::__evaluateOutput()
	{
		this->sInput.inputNode()->evalOutput();

		for (std::size_t nIndex{0}, nMaxIndex{this->sOutput.size()}; nIndex < nMaxIndex; ++nIndex)
			this->sOutput.span()[nIndex] = -this->sInput.inputNode()->output()[nIndex];
	}

	void Negative::__backwardOp(const Node *pDy)
	{
		this->sInput.inputNode()->gradient().accumulateFrom(-1.f, this->evalGradient(pDy).gradient());
	}
}