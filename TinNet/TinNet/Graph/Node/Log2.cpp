
/*
	2018.06.07
	Created by AcrylicShrimp.
*/

#include "Log2.h"

namespace TinNet::Graph::Node
{
	Log2::Log2(const std::string &sName, Graph *pGraph) :
		FullCachedGraphNode(sName, pGraph)
	{
		//Empty.
	}

	const Shape &Log2::shape() const
	{
		return this->sBackwardList.front()->shape();
	}

	std::size_t Log2::maxBackwardNodeCount() const
	{
		return 1;
	}

	void Log2::initNode()
	{
		//Empty.
	}

	void Log2::forwardPass(Cache sDestination)
	{
		const auto &sLeft{this->sBackwardList.front()->forward()};

		for (std::size_t nIndex{0}, nSize{sDestination.size()}; nIndex < nSize; ++nIndex)
			sDestination[nIndex] = std::log2(sLeft[nIndex] + .0001f);
	}

	void Log2::backwardPass(GraphNode *pBackward, Cache sDestination)
	{
		const auto &sForward{this->sBackwardList.front()->forward()};
		const auto &sBackward{this->backward()};

		for (std::size_t nIndex{0}, nSize{sDestination.size()}; nIndex < nSize; ++nIndex)
			sDestination[nIndex] = sBackward[nIndex] / (0.6931472f * sForward[nIndex] + .0001f);
	}
}