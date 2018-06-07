
/*
	2018.06.07
	Created by AcrylicShrimp.
*/

#include "Log.h"

namespace TinNet::Graph::Node
{
	Log::Log(const std::string &sName, Graph *pGraph) :
		FullCachedGraphNode(sName, pGraph)
	{
		//Empty.
	}

	const Shape &Log::shape() const
	{
		return this->sBackwardList.front()->shape();
	}

	std::size_t Log::maxBackwardNodeCount() const
	{
		return 1;
	}

	void Log::initNode()
	{
		//Empty.
	}

	void Log::forwardPass(Cache sDestination)
	{
		const auto &sLeft{this->sBackwardList.front()->forward()};

		for (std::size_t nIndex{0}, nSize{sDestination.size()}; nIndex < nSize; ++nIndex)
			sDestination[nIndex] = std::log(sLeft[nIndex] + .0001f);
	}

	void Log::backwardPass(GraphNode *pBackward, Cache sDestination)
	{
		const auto &sForward{this->sBackwardList.front()->forward()};
		const auto &sBackward{this->backward()};

		for (std::size_t nIndex{0}, nSize{sDestination.size()}; nIndex < nSize; ++nIndex)
			sDestination[nIndex] = sBackward[nIndex] / (sForward[nIndex] + .0001f);
	}
}