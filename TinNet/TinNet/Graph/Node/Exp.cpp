
/*
	2018.06.07
	Created by AcrylicShrimp.
*/

#include "Exp.h"

namespace TinNet::Graph::Node
{
	Exp::Exp(const std::string &sName, Graph *pGraph) :
		FullCachedGraphNode(sName, pGraph)
	{
		//Empty.
	}

	const Shape &Exp::shape() const
	{
		return this->sBackwardList.front()->shape();
	}

	std::size_t Exp::maxBackwardNodeCount() const
	{
		return 1;
	}

	void Exp::initNode()
	{
		//Empty.
	}

	void Exp::forwardPass(Cache sDestination)
	{
		const auto &sLeft{this->sBackwardList.front()->forward()};

		for (std::size_t nIndex{0}, nSize{sDestination.size()}; nIndex < nSize; ++nIndex)
			sDestination[nIndex] = std::exp(sLeft[nIndex]);
	}

	void Exp::backwardPass(GraphNode *pBackward, Cache sDestination)
	{
		const auto &sForward{this->sBackwardList.front()->forward()};
		const auto &sBackward{this->backward()};

		for (std::size_t nIndex{0}, nSize{sDestination.size()}; nIndex < nSize; ++nIndex)
			sDestination[nIndex] = std::exp(sForward[nIndex]) * sBackward[nIndex];
	}
}