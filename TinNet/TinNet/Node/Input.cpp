
/*
	2019.03.13
	Created by AcrylicShrimp.
*/

#include "Input.h"

namespace TinNet::Node
{
	TINNET_NODE_TYPE_DEF(Input)

	Input::Input(Core::Graph *pGraph, std::string_view sName) :
		Node(pGraph, sName)
	{
		//Empty.
	}

	void Input::feed(Core::Span sSpan, Core::Shape sShape)
	{
		this->sInputSpan = sSpan;
		this->sInputShape = sShape;

		this->markDirty();
	}

	void Input::__evaluateShape()
	{
		this->sShape = this->sInputShape;
	}

	void Input::__evaluateOutput()
	{
		this->output().copyFrom(this->sInputSpan);
	}
}