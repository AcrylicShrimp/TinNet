
/*
	2018.06.03
	Created by AcrylicShrimp.
*/

#include "Squeeze.h"

namespace TinNet::Graph::Node
{
	Squeeze::Squeeze(const std::string &sName, Graph *pGraph) :
		BackwardCachedGraphNode(sName, pGraph),
		sShape{}
	{
		//Empty.
	}

	const Shape &Squeeze::shape() const
	{
		return this->sShape;
	}

	std::size_t Squeeze::maxBackwardNodeCount() const
	{
		return 1;
	}

	void Squeeze::initNode()
	{
		this->sShape = this->sBackwardList.front()->shape().squeeze();
	}

	void Squeeze::initGraph()
	{
		//Empty.
	}

	const Cache &Squeeze::forward()
	{
		return this->sBackwardList.front()->forward();
	}

	void Squeeze::forwardPass(Cache sDestination)
	{
		//Empty.
	}

	void Squeeze::backwardPass(GraphNode *pBackward, Cache sDestination)
	{
		sDestination.copy(this->backward());
	}
}