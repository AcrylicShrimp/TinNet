
/*
	2018.06.03
	Created by AcrylicShrimp.
*/

#include "Square.h"

namespace TinNet::Graph::Node
{
	Square::Square(const std::string &sName, Graph *pGraph) :
		FullCachedGraphNode(sName, pGraph)
	{
		//Empty.
	}

	const Shape &Square::shape() const
	{
		return this->sBackwardList.front()->shape();
	}

	std::size_t Square::maxBackwardNodeCount() const
	{
		return 1;
	}

	void Square::initNode()
	{
		//Empty.
	}

	void Square::forwardPass(Cache sDestination)
	{
		const auto &sLeft{this->sBackwardList.front()->forward()};

		for (std::size_t nIndex{0}, nSize{sDestination.size()}; nIndex < nSize; ++nIndex)
			sDestination[nIndex] = sLeft[nIndex] * sLeft[nIndex];
	}

	void Square::backwardPass(GraphNode *pBackward, Cache sDestination)
	{
		const auto &sBackward{this->backward()};

		for (std::size_t nIndex{0}, nSize{sDestination.size()}; nIndex < nSize; ++nIndex)
			sDestination[nIndex] = 2.f * sBackward[nIndex];
	}
}