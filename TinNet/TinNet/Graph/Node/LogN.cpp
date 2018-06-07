
/*
	2018.06.07
	Created by AcrylicShrimp.
*/

#include "LogN.h"

namespace TinNet::Graph::Node
{
	LogN::LogN(const std::string &sName, Graph *pGraph, float nBase) :
		FullCachedGraphNode(sName, pGraph),
		nLogBase{std::log(nBase)}
	{
		//Empty.
	}

	const Shape &LogN::shape() const
	{
		return this->sBackwardList.front()->shape();
	}

	std::size_t LogN::maxBackwardNodeCount() const
	{
		return 1;
	}

	void LogN::initNode()
	{
		//Empty.
	}

	void LogN::forwardPass(Cache sDestination)
	{
		const auto &sLeft{this->sBackwardList.front()->forward()};

		for (std::size_t nIndex{0}, nSize{sDestination.size()}; nIndex < nSize; ++nIndex)
			sDestination[nIndex] = std::log(sLeft[nIndex] + .0001f) / this->nLogBase;
	}

	void LogN::backwardPass(GraphNode *pBackward, Cache sDestination)
	{
		const auto &sForward{this->sBackwardList.front()->forward()};
		const auto &sBackward{this->backward()};

		for (std::size_t nIndex{0}, nSize{sDestination.size()}; nIndex < nSize; ++nIndex)
			sDestination[nIndex] = sBackward[nIndex] / (this->nLogBase * sForward[nIndex] + .0001f);
	}
}