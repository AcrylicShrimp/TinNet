
/*
	2018.06.07
	Created by AcrylicShrimp.
*/

#include "Negative.h"

namespace TinNet::Graph::Node
{
	Negative::Negative(const std::string &sName, Graph *pGraph) :
		FullCachedGraphNode(sName, pGraph)
	{
		//Empty.
	}

	const Shape &Negative::shape() const
	{
		return this->sBackwardList.front()->shape();
	}

	std::size_t Negative::maxBackwardNodeCount() const
	{
		return 1;
	}

	void Negative::initNode()
	{
		//Empty.
	}

	void Negative::forwardPass(Cache sDestination)
	{
		const auto &sLeft{this->sBackwardList.front()->forward()};

		for (std::size_t nIndex{0}, nSize{sDestination.size()}; nIndex < nSize; ++nIndex)
			sDestination[nIndex] = -sLeft[nIndex];
	}

	void Negative::backwardPass(GraphNode *pBackward, Cache sDestination)
	{
		const auto &sBackward{this->backward()};

		for (std::size_t nIndex{0}, nSize{sDestination.size()}; nIndex < nSize; ++nIndex)
			sDestination[nIndex] = -sBackward[nIndex];
	}
}