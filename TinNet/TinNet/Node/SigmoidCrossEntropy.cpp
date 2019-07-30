
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
		if (!this->sInputLabel)
			throw std::runtime_error{"no node attached at 'label'"};

		if (!this->sInputProb)
			throw std::runtime_error{"no node attached at 'prob'"};

		if (this->sInputLabel.inputNode()->evalShape().shape() != this->sInputProb.inputNode()->evalShape().shape())
			throw std::runtime_error{"the shape of 'label' and 'prob' must be equal"};

		this->sShape = {1};
	}

	void SigmoidCrossEntropy::__evaluateOutput()
	{
		this->sInputLabel.inputNode()->evalOutput();
		this->sInputProb.inputNode()->evalOutput();

		this->sOutput.span()[0] = .0f;

		for (std::size_t nIndex{0}, nMaxIndex{this->sInputLabel.inputNode()->shape().size()}; nIndex < nMaxIndex; ++nIndex)
			this->sOutput.span()[0] += this->sInputLabel.inputNode()->output()[nIndex] * std::log(this->sInputProb.inputNode()->output()[nIndex] + 1e-6f) + (this->sInputLabel.inputNode()->output()[nIndex] - 1.f) * std::log(1.f - this->sInputProb.inputNode()->output()[nIndex] + 1e-6f);

		this->sOutput.span()[0] /= -static_cast<float>(this->sInputLabel.inputNode()->shape().size());
	}

	void SigmoidCrossEntropy::__backwardOpLabel(const Node *pDy)
	{
		this->sInputProb.inputNode()->evalOutput();
		this->evalGradient(pDy);

		const auto nFactor{this->sGradient.span()[0] / this->sInputProb.inputNode()->shape().size()};

		for (std::size_t nIndex{0}, nMaxIndex{this->sInputProb.inputNode()->gradient().length()}; nIndex < nMaxIndex; ++nIndex)
			this->sInputLabel.inputNode()->gradient()[nIndex] += nFactor * (std::log(1.f - this->sInputProb.inputNode()->output()[nIndex] + 1e-6f) - std::log(this->sInputProb.inputNode()->output()[nIndex] + 1e-6f));
	}

	void SigmoidCrossEntropy::__backwardOpProb(const Node *pDy)
	{
		this->sInputLabel.inputNode()->evalOutput();
		this->sInputProb.inputNode()->evalOutput();
		this->evalGradient(pDy);

		const auto nFactor{this->sGradient.span()[0] / this->sInputProb.inputNode()->shape().size()};

		for (std::size_t nIndex{0}, nMaxIndex{this->sInputProb.inputNode()->gradient().length()}; nIndex < nMaxIndex; ++nIndex)
			this->sInputProb.inputNode()->gradient()[nIndex] += nFactor * (this->sInputProb.inputNode()->output()[nIndex] - this->sInputLabel.inputNode()->output()[nIndex]) / (this->sInputProb.inputNode()->output()[nIndex] * (1.f - this->sInputProb.inputNode()->output()[nIndex]) + 1e-6f);
	}
}