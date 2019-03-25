
/*
	2019.03.25
	Created by AcrylicShrimp.
*/

#include "MSE.h"

namespace TinNet::Node
{
	TINNET_NODE_TYPE_DEF(MSE)

	MSE::MSE(Core::Graph *pGraph, std::string_view sName) :
		Node(pGraph, sName),
		sInputLabel{this, "label", [this](const auto *pDy) { this->__backwardOpLabel(pDy); }},
		sInputPrediction{this, "prediction", [this](const auto *pDy) { this->__backwardOpPrediction(pDy); }}
	{
		this->sNodeInputMap["label"] = &this->sInputLabel;
		this->sNodeInputMap["prediction"] = &this->sInputPrediction;
	}

	void MSE::__evaluateShape()
	{
		this->sShape = {1};
	}

	void MSE::__evaluateOutput()
	{
		this->sInputLabel.inputNode()->evalOutput();
		this->sInputPrediction.inputNode()->evalOutput();

		this->sOutput.span()[0] = .0f;

		for (std::size_t nIndex{0}, nMaxIndex{this->sInputLabel.inputNode()->shape().size()}; nIndex < nMaxIndex; ++nIndex)
			this->sOutput.span()[0] += std::pow(this->sInputLabel.inputNode()->output()[nIndex] - this->sInputPrediction.inputNode()->output()[nIndex], 2);

		this->sOutput.span()[0] /= this->sInputLabel.inputNode()->shape().size();
	}

	void MSE::__backwardOpLabel(const Node *pDy)
	{
		this->sInputLabel.inputNode()->evalOutput();
		this->sInputPrediction.inputNode()->evalOutput();
		this->evalGradient(pDy);

		const auto nFactor{2.f / this->sInputLabel.inputNode()->shape().size()};

		for (std::size_t nIndex{0}, nMaxIndex{this->sInputLabel.inputNode()->gradient().length()}; nIndex < nMaxIndex; ++nIndex)
			this->sInputLabel.inputNode()->gradient()[nIndex] += (this->sInputLabel.inputNode()->output()[nIndex] - this->sInputPrediction.inputNode()->output()[nIndex]) * nFactor * this->sGradient.span()[0];
	}

	void MSE::__backwardOpPrediction(const Node *pDy)
	{
		this->sInputLabel.inputNode()->evalOutput();
		this->sInputPrediction.inputNode()->evalOutput();
		this->evalGradient(pDy);

		const auto nFactor{2.f / this->sInputLabel.inputNode()->shape().size()};

		for (std::size_t nIndex{0}, nMaxIndex{this->sInputPrediction.inputNode()->gradient().length()}; nIndex < nMaxIndex; ++nIndex)
			this->sInputPrediction.inputNode()->gradient()[nIndex] += (this->sInputPrediction.inputNode()->output()[nIndex] - this->sInputLabel.inputNode()->output()[nIndex]) * nFactor * this->sGradient.span()[0];
	}
}