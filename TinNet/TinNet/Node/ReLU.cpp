
/*
	2019.03.28
	Created by AcrylicShrimp.
*/

#include "ReLU.h"

namespace TinNet::Node
{
	TINNET_NODE_TYPE_DEF(ReLU)

		ReLU::ReLU(Core::Graph *pGraph, std::string_view sName, float nAlpha) :
		Node(pGraph, sName),
		nAlpha{nAlpha},
		sInputLogit{this, "logit", [this](const auto *pDy) { this->__backwardOp(pDy); }}
	{
		this->sNodeInputMap["logit"] = &this->sInputLogit;
	}

	void ReLU::__evaluateShape()
	{
		if (!this->sInputLogit.inputNode())
			throw std::logic_error{"no node attached at 'logit'"};

		this->sShape = this->sInputLogit.inputNode()->shape();
	}

	void ReLU::__evaluateOutput()
	{
		if (!this->sInputLogit.inputNode())
			throw std::logic_error{ "no node attached at 'logit'" };

		this->sInputLogit.inputNode()->evalOutput();

		const auto fRectify = [](float nValue, float nAlpha)
		{
			return nValue < .0f ? nAlpha * nValue : nValue;
		};

		for (std::size_t nIndex{0}, nMaxIndex{this->sOutput.size()}; nIndex < nMaxIndex; ++nIndex)
			this->sOutput.span()[nIndex] = fRectify(this->sInputLogit.inputNode()->output()[nIndex], this->nAlpha);
	}

	void ReLU::__backwardOp(const Node *pDy)
	{
		if (!this->sInputLogit.inputNode())
			throw std::logic_error{ "no node attached at 'logit'" };

		this->sInputLogit.inputNode()->evalOutput();
		this->evalGradient(pDy);

		const auto fRectify = [](float nValue, float nAlpha, float nGradient)
		{
			return nValue < .0f ? nAlpha * nGradient : nGradient;
		};

		for (std::size_t nIndex{0}, nMaxIndex{this->sInputLogit.inputNode()->gradient().length()}; nIndex < nMaxIndex; ++nIndex)
			this->sInputLogit.inputNode()->gradient()[nIndex] += fRectify(this->sInputLogit.inputNode()->output()[nIndex], this->nAlpha, this->sGradient.span()[nIndex]);
	}
}