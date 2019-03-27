
/*
	2019.03.27
	Created by AcrylicShrimp.
*/

#include "Dense.h"

namespace TinNet::Node
{
	TINNET_NODE_TYPE_DEF(Dense)

		Dense::Dense(Core::Graph *pGraph, std::string_view sName) :
		Node(pGraph, sName),
		sInput{this, "input", [this](const auto *pDy) { this->__backwardOpInput(pDy); }},
		sInputWeight{this, "weight", [this](const auto *pDy) { this->__backwardOpWeight(pDy); }},
		sInputBias{this, "bias", [this](const auto *pDy) { this->__backwardOpBias(pDy); }}
	{
		this->sNodeInputMap["input"] = &this->sInput;
		this->sNodeInputMap["weight"] = &this->sInputWeight;
		this->sNodeInputMap["bias"] = &this->sInputBias;
	}

	void Dense::__evaluateShape()
	{
		//TODO: Implement this method.
	}

	void Dense::__evaluateOutput()
	{
		//TODO: Implement this method.
	}

	void Dense::__backwardOpInput(const Node *pDy)
	{
		//TODO: Implement this method.
	}

	void Dense::__backwardOpWeight(const Node *pDy)
	{
		//TODO: Implement this method.
	}
	
	void Dense::__backwardOpBias(const Node *pDy)
	{
		//TODO: Implement this method.
	}
}