
/*
	2018.05.27
	Created by AcrylicShrimp.
*/

#include "Multiply.h"

namespace TinNet::Graph::Node
{
	Multiply::Multiply(const std::string &sName, Graph *pGraph) :
		FullCachedGraphNode(sName, pGraph)
	{
		//Empty.
	}

	std::size_t Multiply::fanOut() const
	{
		return this->sBackwardList.front()->fanOut();
	}

	std::size_t Multiply::maxBackwardNodeCount() const
	{
		return 2;
	}

	void Multiply::forwardPass(Cache sDestination)
	{
		auto sLeft{this->sBackwardList.front()->forward()};
		auto sRight{this->sBackwardList.back()->forward()};

		for (std::size_t nIndex{0}, nSize{sDestination.size()}; nIndex < nSize; ++nIndex)
			sDestination[nIndex] = sLeft[nIndex] * sRight[nIndex];
	}

	void Multiply::backwardPass(GraphNode *pBackward, Cache sDestination)
	{
		auto sBackward{this->backward()};
		auto sForward{pBackward == this->sBackwardList.front() ? this->sBackwardList.back()->forward() : this->sBackwardList.front()->forward()};

		for (std::size_t nIndex{0}, nSize{sDestination.size()}; nIndex < nSize; ++nIndex)
			sDestination[nIndex] = sBackward[nIndex] * sForward[nIndex];
	}
}