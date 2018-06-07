
/*
	2018.06.04
	Created by AcrylicShrimp.
*/

#include "Tanh.h"

namespace TinNet::Graph::Node
{
	Tanh::Tanh(const std::string &sName, Graph *pGraph) :
		FullCachedGraphNode(sName, pGraph)
	{
		//Empty.
	}

	const Shape &Tanh::shape() const
	{
		return this->sBackwardList.front()->shape();
	}

	std::size_t Tanh::maxBackwardNodeCount() const
	{
		return 1;
	}

	void Tanh::initNode()
	{
		//Empty.
	}

	void Tanh::forwardPass(Cache sDestination)
	{
		const auto &sLeft{this->sBackwardList.front()->forward()};

		for (std::size_t nIndex{0}, nSize{sDestination.size()}; nIndex < nSize; ++nIndex)
			sDestination[nIndex] = std::tanh(sLeft[nIndex]);
	}

	void Tanh::backwardPass(GraphNode *pBackward, Cache sDestination)
	{
		const auto &sForward{this->forward()};
		const auto &sBackward{this->backward()};

		for (std::size_t nIndex{0}, nSize{sDestination.size()}; nIndex < nSize; ++nIndex)
			sDestination[nIndex] = sBackward[nIndex] * (1.f - sForward[nIndex] * sForward[nIndex]);
	}
}