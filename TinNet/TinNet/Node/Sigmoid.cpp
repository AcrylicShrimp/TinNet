
/*
	2019.03.13
	Created by AcrylicShrimp.
*/

#include "Sigmoid.h"

namespace TinNet::Node
{
	TINNET_NODE_TYPE_DEF(Sigmoid)

	Sigmoid::Sigmoid(Core::Graph *pGraph, std::string_view sName) :
		Node(pGraph, sName),
		sInputLogit{this, "logit", [this](const auto *pDy) { this->__backwardOp(pDy); }}
	{
		this->sNodeInputMap["logit"] = &this->sInputLogit;
	}

	void Sigmoid::__evaluateShape()
	{
		this->sShape = this->sInputLogit.inputNode()->shape();
	}

	void Sigmoid::__evaluateOutput()
	{
		this->sInputLogit.inputNode()->evalOutput();

		for (std::size_t nIndex{0}, nMaxIndex{this->sOutput.size()}; nIndex < nMaxIndex; ++nIndex)
			this->sOutput.span()[nIndex] = 1.f / (1.f + std::exp(-this->sInputLogit.inputNode()->output()[nIndex]));
	}

	void Sigmoid::__backwardOp(const Node *pDy)
	{
		this->evalOutput();
		this->evalGradient(pDy);
		
		for (std::size_t nIndex{0}, nMaxIndex{this->sInputLogit.inputNode()->gradient().length()}; nIndex < nMaxIndex; ++nIndex)
			this->sInputLogit.inputNode()->gradient()[nIndex] += this->sOutput.span()[nIndex] * (1.f - this->sOutput.span()[nIndex]) * this->sGradient.span()[nIndex];
	}
}