
/*
	2018.05.27
	Created by AcrylicShrimp.
*/

#include "Add.h"

namespace TinNet::Graph::Node
{
	Add::Add(const std::string &sName, Graph *pGraph) :
		FullCachedGraphNode(sName, pGraph)
	{
		//Empty.
	}

	std::size_t Add::fanOut() const
	{
		return this->sBackwardList.front()->fanOut();
	}

	std::size_t Add::maxBackwardNodeCount() const
	{
		return 2;
	}

	void Add::forwardPass(Cache sDestination)
	{
		auto sLeft{this->sBackwardList.front()->forward()};
		auto sRight{this->sBackwardList.back()->forward()};

		for (std::size_t nIndex{0}, nSize{sDestination.size()}; nIndex < nSize; ++nIndex)
			sDestination[nIndex] = sLeft[nIndex] + sRight[nIndex];
	}

	void Add::backwardPass(GraphNode *pBackward, Cache sDestination)
	{
		sDestination.copy(this->backward());
	}
}