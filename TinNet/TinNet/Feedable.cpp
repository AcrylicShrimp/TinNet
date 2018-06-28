
/*
	2018.06.17
	Created by AcrylicShrimp.
*/

#include "Feedable.h"

#include "Graph.h"
#include "Node.h"

namespace TinNet
{
	Feedable::Feedable(Graph *pGraph, Node *pNode)
	{
		pGraph->registerFeedable(pNode, this);
	}
}