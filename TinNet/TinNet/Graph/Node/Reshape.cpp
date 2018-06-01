
/*
	2018.06.01
	Created by AcrylicShrimp.
*/

#include "Reshape.h"

namespace TinNet::Graph::Node
{
	Reshape::Reshape(const std::string &sName, Graph *pGraph, const Shape &sShape) :
		BackwardCachedGraphNode(sName, pGraph),
		sShape{sShape}
	{
		//Empty.
	}

	const Shape &Reshape::shape() const
	{
		return this->sShape;
	}

	std::size_t Reshape::maxBackwardNodeCount() const
	{
		return 1;
	}

	void Reshape::initNode()
	{
		if (this->sBackwardList.front()->shape().element() != this->sShape.element())
			throw std::invalid_argument("cannot reshape");
	}

	void Reshape::initGraph()
	{
		//Empty.
	}

	const Cache &Reshape::forward()
	{
		return this->sBackwardList.front()->forward();
	}

	void Reshape::forwardPass(Cache sDestination)
	{
		//Empty.
	}

	void Reshape::backwardPass(GraphNode *pBackward, Cache sDestination)
	{
		sDestination.copy(this->backward());
	}
}