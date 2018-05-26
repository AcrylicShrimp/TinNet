
/*
	2018.05.27
	Created by AcrylicShrimp.
*/

#include "Divide.h"

namespace TinNet::Graph::Node
{
	Divide::Divide(const std::string &sName, Graph *pGraph) :
		FullCachedGraphNode(sName, pGraph)
	{
		//Empty.
	}

	std::size_t Divide::fanOut() const
	{
		return this->sBackwardList.front()->fanOut();
	}

	std::size_t Divide::maxBackwardNodeCount() const
	{
		return 2;
	}

	void Divide::forwardPass(Cache sDestination)
	{
		auto sLeft{this->sBackwardList.front()->forward()};
		auto sRight{this->sBackwardList.back()->forward()};

		for (std::size_t nIndex{0}, nSize{sDestination.size()}; nIndex < nSize; ++nIndex)
			sDestination[nIndex] = sLeft[nIndex] / sRight[nIndex];
	}

	void Divide::backwardPass(GraphNode *pBackward, Cache sDestination)
	{
		auto sBackward{this->backward()};

		if (pBackward == this->sBackwardList.front())
		{
			auto sForward{this->sBackwardList.back()->forward()};

			for (std::size_t nIndex{0}, nSize{sDestination.size()}; nIndex < nSize; ++nIndex)
				sDestination[nIndex] = sBackward[nIndex] / sForward[nIndex];
		}
		else
		{
			auto sForward{this->sBackwardList.front()->forward()};

			for (std::size_t nIndex{0}, nSize{sDestination.size()}; nIndex < nSize; ++nIndex)
				sDestination[nIndex] = sBackward[nIndex] * sForward[nIndex];
		}
	}
}