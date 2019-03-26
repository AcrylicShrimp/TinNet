
/*
	2019.03.13
	Created by AcrylicShrimp.
*/

#include "SigmoidCrossEntropy.h"

namespace TinNet::Node
{
	TINNET_NODE_TYPE_DEF(SigmoidCrossEntropy)

	SigmoidCrossEntropy::SigmoidCrossEntropy(Core::Graph *pGraph, std::string_view sName) :
		Node(pGraph, sName),
		sInputLabel{this, "label", [this](const auto *pDy) { this->__backwardOpLabel(pDy); }},
		sInputProb{this, "prob", [this](const auto *pDy) { this->__backwardOpProb(pDy); }}
	{
		this->sNodeInputMap["label"] = &this->sInputLabel;
		this->sNodeInputMap["prob"] = &this->sInputProb;
	}

	void SigmoidCrossEntropy::__evaluateShape()
	{
		this->sShape = {1};
	}

	void SigmoidCrossEntropy::__evaluateOutput()
	{
		this->sInputLabel.inputNode()->evalOutput();
		this->sInputProb.inputNode()->evalOutput();

		this->sOutput.span()[0] = .0f;

		for (std::size_t nIndex{0}, nMaxIndex{this->sInputLabel.inputNode()->shape().size()}; nIndex < nMaxIndex; ++nIndex)
			this->sOutput.span()[0] += -this->sInputLabel.inputNode()->output()[nIndex] * std::log(this->sInputProb.inputNode()->output()[nIndex] + 1e-4f) + (this->sInputLabel.inputNode()->output()[nIndex] - 1.f) * std::log(1.f - this->sInputProb.inputNode()->output()[nIndex] + 1e-4f);

		this->sOutput.span()[0] /= this->sInputLabel.inputNode()->shape().size();
	}

	void SigmoidCrossEntropy::__backwardOpLabel(const Node *pDy)
	{
		//TODO : Implement this method.
	}

	void SigmoidCrossEntropy::__backwardOpProb(const Node *pDy)
	{
		this->sInputLabel.inputNode()->evalOutput();
		this->sInputProb.inputNode()->evalOutput();
		this->evalGradient(pDy);

		const auto nFactor{1.f / this->sInputLabel.inputNode()->shape().size()};

		for (std::size_t nIndex{0}, nMaxIndex{this->sInputProb.inputNode()->gradient().length()}; nIndex < nMaxIndex; ++nIndex)
			this->sInputProb.inputNode()->gradient()[nIndex] += (this->sInputProb.inputNode()->output()[nIndex] - this->sInputLabel.inputNode()->output()[nIndex]) / (this->sInputProb.inputNode()->output()[nIndex] * (1.f - this->sInputProb.inputNode()->output()[nIndex]) + 1e-4f) * nFactor * this->sGradient.span()[0];
	}
}