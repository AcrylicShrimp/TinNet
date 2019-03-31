
/*
	2019.03.31
	Created by AcrylicShrimp.
*/

#include "Sum.h"

namespace TinNet::Node
{
	TINNET_NODE_TYPE_DEF(Sum)

	Sum::Sum(Core::Graph *pGraph, std::string_view sName) :
		Node(pGraph, sName),
		sInput{this, "input", [this](const auto *pDy) { this->__backwardOpInput(pDy); }}
	{
		this->sNodeInputMap["input"] = &this->sInput;
	}
}