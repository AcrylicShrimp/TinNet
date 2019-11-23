
/*
	2019.07.27
	Created by AcrylicShrimp.
*/

#include "SoftmaxCrossEntropy.h"

namespace TinNet::Node
{
	TINNET_NODE_TYPE_DEF(SoftmaxCrossEntropy)
	
	SoftmaxCrossEntropy::SoftmaxCrossEntropy(Core::Graph *pGraph, std::string_view sName) :
		Node(pGraph, sName),
		sInputLabel{this, "label", [this](const auto *pDy) { this->__backwardOpLabel(pDy); }},
		sInputProb{this, "prob", [this](const auto *pDy) { this->__backwardOpProb(pDy); }}
	{
		this->sNodeInputMap["label"] = &this->sInputLabel;
		this->sNodeInputMap["prob"] = &this->sInputProb;
	}
	
	void SoftmaxCrossEntropy::__evaluateShape()
	{
		if (!this->sInputLabel)
			throw std::runtime_error{"no node attached at 'label'"};

		if (!this->sInputProb)
			throw std::runtime_error{"no node attached at 'prob'"};

		if (this->sInputLabel.inputNode()->evalShape().shape() != this->sInputProb.inputNode()->evalShape().shape())
			throw std::runtime_error{"the shape of 'label' and 'prob' must be equal"};

		this->sShape = {1};
	}

	void SoftmaxCrossEntropy::__evaluateOutput()
	{
		this->sInputLabel.inputNode()->evalOutput();
		this->sInputProb.inputNode()->evalOutput();

		this->sOutput.span()[0] = .0f;

		for (std::size_t nIndex{0}, nMaxIndex{this->sInputLabel.inputNode()->shape().size()}; nIndex < nMaxIndex; ++nIndex)
			this->sOutput.span()[0] += this->sInputLabel.inputNode()->output()[nIndex] * std::log(this->sInputProb.inputNode()->output()[nIndex] + 1e-4f);

		this->sOutput.span()[0] /= -static_cast<float>(this->sInputLabel.inputNode()->shape()[1]);
	}

	void SoftmaxCrossEntropy::__backwardOpLabel(const Node *pDy)
	{
		this->sInputProb.inputNode()->evalOutput();
		this->evalGradient(pDy);

		const auto nFactor{-this->sGradient.span()[0] / this->sInputProb.inputNode()->shape()[1]};

		for (std::size_t nIndex{0}, nMaxIndex{this->sInputProb.inputNode()->gradient().length()}; nIndex < nMaxIndex; ++nIndex)
			this->sInputLabel.inputNode()->gradient()[nIndex] += nFactor * std::log(this->sInputProb.inputNode()->output()[nIndex] + 1e-4f);
	}

	void SoftmaxCrossEntropy::__backwardOpProb(const Node *pDy)
	{
		this->sInputLabel.inputNode()->evalOutput();
		this->sInputProb.inputNode()->evalOutput();
		this->evalGradient(pDy);

		const auto nFactor{-this->sGradient.span()[0] / this->sInputProb.inputNode()->shape()[1]};

		for (std::size_t nIndex{0}, nMaxIndex{this->sInputProb.inputNode()->gradient().length()}; nIndex < nMaxIndex; ++nIndex)
			this->sInputProb.inputNode()->gradient()[nIndex] += nFactor * this->sInputLabel.inputNode()->output()[nIndex] / (this->sInputProb.inputNode()->output()[nIndex] + 1e-4f);
	}
}