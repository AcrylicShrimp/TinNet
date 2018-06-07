
/*
	2018.06.07
	Created by AcrylicShrimp.
*/

#include "Log10.h"

namespace TinNet::Graph::Node
{
	Log10::Log10(const std::string &sName, Graph *pGraph) :
		FullCachedGraphNode(sName, pGraph)
	{
		//Empty.
	}

	const Shape &Log10::shape() const
	{
		return this->sBackwardList.front()->shape();
	}

	std::size_t Log10::maxBackwardNodeCount() const
	{
		return 1;
	}

	void Log10::initNode()
	{
		//Empty.
	}

	void Log10::forwardPass(Cache sDestination)
	{
		const auto &sLeft{this->sBackwardList.front()->forward()};

		for (std::size_t nIndex{0}, nSize{sDestination.size()}; nIndex < nSize; ++nIndex)
			sDestination[nIndex] = std::log10(sLeft[nIndex] + .0001f);
	}

	void Log10::backwardPass(GraphNode *pBackward, Cache sDestination)
	{
		const auto &sForward{this->sBackwardList.front()->forward()};
		const auto &sBackward{this->backward()};

		for (std::size_t nIndex{0}, nSize{sDestination.size()}; nIndex < nSize; ++nIndex)
			sDestination[nIndex] = sBackward[nIndex] / (2.302585f * sForward[nIndex] + .0001f);
	}
}