
/*
	2018.06.07
	Created by AcrylicShrimp.
*/

#include "Exp2.h"

namespace TinNet::Graph::Node
{
	Exp2::Exp2(const std::string &sName, Graph *pGraph) :
		FullCachedGraphNode(sName, pGraph)
	{
		//Empty.
	}

	const Shape &Exp2::shape() const
	{
		return this->sBackwardList.front()->shape();
	}

	std::size_t Exp2::maxBackwardNodeCount() const
	{
		return 1;
	}

	void Exp2::initNode()
	{
		//Empty.
	}

	void Exp2::forwardPass(Cache sDestination)
	{
		const auto &sLeft{this->sBackwardList.front()->forward()};

		for (std::size_t nIndex{0}, nSize{sDestination.size()}; nIndex < nSize; ++nIndex)
			sDestination[nIndex] = std::exp2(sLeft[nIndex]);
	}

	void Exp2::backwardPass(GraphNode *pBackward, Cache sDestination)
	{
		const auto &sForward{this->sBackwardList.front()->forward()};
		const auto &sBackward{this->backward()};

		for (std::size_t nIndex{0}, nSize{sDestination.size()}; nIndex < nSize; ++nIndex)
			sDestination[nIndex] = 0.6931472f * std::exp2(sForward[nIndex]) * sBackward[nIndex];
	}
}