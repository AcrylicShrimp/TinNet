
/*
	2018.06.17
	Created by AcrylicShrimp.
*/

#include "Initializable.h"

#include "Graph.h"

namespace TinNet
{
	Initializable::Initializable(Graph *pGraph)
	{
		pGraph->registerInitializable(this);
	}
}