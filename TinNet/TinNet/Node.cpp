
/*
	2018.06.17
	Created by AcrylicShrimp.
*/

#include "Node.h"

#include "Graph.h"

namespace TinNet
{
	Node::Node(Graph *pGraph, const std::string &sName) :
		pGraph{pGraph},
		sName{sName}
	{
		//Empty.
	}

	void Node::link(NodePtr pInput, NodePtr pOutput)
	{
		pInput->sOutputList.emplace_back(pOutput);
		pOutput->sInputList.emplace_back(pInput);
	}

	void Node::unlink(NodePtr pInput, NodePtr pOutput)
	{
		auto iOutput{std::find(pInput->sOutputList.cbegin(), pInput->sOutputList.cend(), pOutput)};
		auto iInput{std::find(pOutput->sInputList.cbegin(), pOutput->sInputList.cend(), pInput)};

		if (iOutput != pInput->sOutputList.cend())
			pInput->sOutputList.erase(iOutput);

		if (iInput != pOutput->sInputList.cend())
			pOutput->sInputList.erase(iInput);
	}

	void Node::computeForward(CachePtr pDestination)
	{
		if (!pDestination->bDirty)
			return;

		this->forwardPass(pDestination->sCache);

		pDestination->bDirty = false;
	}

	void Node::computeBackward(CachePtr pDestination, CachePtr pTemporary)
	{
		if (!pDestination->bDirty)
			return;

		if (this->isLeafOutput())
		{
			pDestination->sCache.one();

			pDestination->bDirty = false;
			pTemporary->bDirty = false;

			return;
		}

		pDestination->sCache.zero();

		for (auto pOutput : this->sOutputList)
		{
			pOutput->backwardPass(pTemporary->sCache, this);
			pDestination->sCache.accumulate(pTemporary->sCache);
		}

		pDestination->bDirty = false;
		pTemporary->bDirty = false;
	}
}