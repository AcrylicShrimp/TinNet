
/*
	2018.05.27
	Created by AcrylicShrimp.
*/

#include "Input.h"

namespace TinNet::Graph::Node
{
	Input::Input(const std::string &sName, Graph *pGraph, std::size_t nFanOut) :
		BackwardCachedGraphNode(sName, pGraph),
		nFanOut{nFanOut}
	{
		//Empty.
	}

	std::size_t Input::fanOut() const
	{
		return this->nFanOut;
	}

	std::size_t Input::maxBackwardNodeCount() const
	{
		return 0;
	}

	void Input::init()
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
		//Empty.
	}
}