
/*
	2019.07.31
	Created by AcrylicShrimp.
*/

#include "Log.h"

namespace TinNet::Node
{
	TINNET_NODE_TYPE_DEF(Log)
	
	Log::Log(Core::Graph *pGraph, std::string_view sName) :
		Node(pGraph, sName),
		sInput{this, "input", [this](const auto *pDy) { this->__backwardOp(pDy); }}
	{
		this->sNodeInputMap["input"] = &this->sInput;
	}
	
	void Log::__evaluateShape()
	{
		if (!this->sInput)
			throw std::runtime_error{"no node attached at 'input'"};

		this->sShape = this->sInput.inputNode()->shape();
	}

	void Log::__evaluateOutput()
	{
		this->sInput.inputNode()->evalOutput();

		for (std::size_t nIndex{0}, nMaxIndex{this->sOutput.size()}; nIndex < nMaxIndex; ++nIndex)
			this->sOutput.span()[nIndex] = std::log(this->sInput.inputNode()->output()[nIndex] + 1e-4f);
	}

	void Log::__backwardOp(const Node *pDy)
	{
		this->sInput.inputNode()->evalOutput();
		this->evalGradient(pDy);

		for (std::size_t nIndex{0}, nMaxIndex{this->sInput.inputNode()->gradient().length()}; nIndex < nMaxIndex; ++nIndex)
			this->sInput.inputNode()->gradient()[nIndex] += this->sGradient.span()[nIndex] / (this->sInput.inputNode()->output()[nIndex] + 1e-4f);
	}
}