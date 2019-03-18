
/*
	2019.03.17
	Created by AcrylicShrimp.
*/

#include "Parameter.h"

namespace TinNet::Node
{
	Parameter::Parameter(std::string_view sName, Core::Shape sShape) :
		Node(sName),
		sParameterShape{sShape}
	{
		//Empty.
	}

	void Parameter::__evaluateShape()
	{
		this->sShape = this->sParameterShape;
	}

	void Parameter::__evaluateOutput()
	{
		this->output().copyFrom(this->sParameter.span());
	}
}