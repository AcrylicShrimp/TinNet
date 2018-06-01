
/*
	2018.05.27
	Created by AcrylicShrimp.
*/

#include "Input.h"

namespace TinNet::Graph::Node
{
	Input::Input(const std::string &sName, Graph *pGraph, const Shape &sShape) :
		BackwardCachedGraphNode(sName, pGraph),
		sShape{sShape}
	{
		//Empty.
	}

	const Shape &Input::shape() const
	{
		return this->sShape;
	}

	std::size_t Input::maxBackwardNodeCount() const
	{
		return 0;
	}

	void Input::initNode()
	{
		//Empty.
	}
	
	void Input::initGraph()
	{
		//Empty.
	}

	const Cache &Input::forward()
	{
		return this->sCache;
	}

	void Input::forwardPass(Cache sDestination)
	{
		//Empty.
	}

	void Input::backwardPass(GraphNode *pBackward, Cache sDestination)
	{
		sDestination.zero();
	}
}