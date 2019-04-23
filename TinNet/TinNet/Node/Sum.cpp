
/*
	2019.03.31
	Created by AcrylicShrimp.
*/

#include "Sum.h"

namespace TinNet::Node
{
	TINNET_NODE_TYPE_DEF(Sum)

	Sum::Sum(Core::Graph *pGraph, std::string_view sName, bool bSqueeze) :
		Node(pGraph, sName),
		bSqueeze{bSqueeze},
		sInput{this, "input", [this](const auto *pDy) { this->__backwardOpInput(pDy); }},
		sInputAxis{this, "axis", [this](const auto *pDy) { /* Do nothing. */ }}
	{
		this->sNodeInputMap["input"] = &this->sInput;
		this->sNodeInputMap["axis"] = &this->sInputAxis;
	}

	void Sum::__evaluateShape()
	{
		if (!this->sInput.inputNode())
			throw std::logic_error{ "no node attached at 'input'" };

		if (!this->sInputAxis.inputNode())
		{
			this->sShape = {1};
			return;
		}

		const auto &sShape{this->sInputAxis.inputNode()->evalShape().shape()};

		//if (sShape.rank())

		this->sShape;
	}

	void Sum::__evaluateOutput()
	{

	}

	void Sum::__backwardOpInput(const Node *pDy)
	{

	}
}