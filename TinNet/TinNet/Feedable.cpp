
/*
	2018.06.17
	Created by AcrylicShrimp.
*/

#include "Feedable.h"

#include "Graph.h"

namespace TinNet
{
	Feedable::Feedable(Graph *pGraph)
	{
		pGraph->registerFeedable(this);
	}
}