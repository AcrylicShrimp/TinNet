
/*
	2018.05.27
	Created by AcrylicShrimp.
*/

#include "Subtract.h"

namespace TinNet::Graph::Node
{
	Subtract::Subtract(const std::string &sName, Graph *pGraph) :
		FullCachedGraphNode(sName, pGraph)
	{
		//Empty.
	}

	std::size_t Subtract::fanOut() const
	{
		return this->sBackwardList.front()->fanOut();
	}

	std::size_t Subtract::maxBackwardNodeCount() const
	{
		return 2;
	}

	void Subtract::forwardPass(Cache sDestination)
	{
		auto sLeft{this->sBackwardList.front()->forward()};
		auto sRight{this->sBackwardList.back()->forward()};

		for (std::size_t nIndex{0}, nSize{sDestination.size()}; nIndex < nSize; ++nIndex)
			sDestination[nIndex] = sLeft[nIndex] - sRight[nIndex];
	}

	void Subtract::backwardPass(GraphNode *pBackward, Cache sDestination)
	{
		if (pBackward == this->sBackwardList.front())
			sDestination.copy(this->backward());
		else
			sDestination.copyNegative(this->backward());
	}
}