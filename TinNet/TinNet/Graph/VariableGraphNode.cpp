
/*
	2018.06.05
	Created by AcrylicShrimp.
*/

#include "VariableGraphNode.h"

namespace TinNet::Graph
{
	VariableGraphNode::VariableGraphNode(const std::string &sName, Graph *pGraph) :
		FullCachedGraphNode(sName, pGraph)
	{
		this->pGraph->asVariable(this);
	}

	VariableGraphNode::~VariableGraphNode()
	{
		for (auto pVariable : this->sVariableList)
			this->pGraph->cacheContainer().release(pVariable);

		for (auto pVariableBackward : this->sVariableBackwardList)
			this->pGraph->cacheContainer().release(pVariableBackward);

		this->sVariableSizeList.clear();
		this->sVariableList.clear();
		this->sVariableBackwardList.clear();
	}

	void VariableGraphNode::enableBackward()
	{
		this->FullCachedGraphNode::enableBackward();

		if (!this->sVariableBackwardList.empty())
			return;

		for (auto nSize : this->sVariableSizeList)
			this->sVariableBackwardList.emplace_back(this->pGraph->cacheContainer().request(nSize));
	}

	void VariableGraphNode::disableBackward()
	{
		this->FullCachedGraphNode::disableBackward();

		for (auto pVariableBackward : this->sVariableBackwardList)
			this->pGraph->cacheContainer().release(pVariableBackward);

		this->sVariableBackwardList.clear();
	}

	void VariableGraphNode::initGraph()
	{
		this->FullCachedGraphNode::initGraph();

		if (!this->sVariableList.empty())
			return;

		for (auto nSize : this->sVariableSizeList)
			this->sVariableList.emplace_back(this->pGraph->cacheContainer().request(nSize));
	}

	void VariableGraphNode::initialize()
	{
		if (this->sVariableList.empty())
			return;

		std::mt19937_64 sEngine{std::random_device{}()};
		std::uniform_real_distribution<float> sDist{-1.f, 1.f};

		for (auto pVariable : this->sVariableList)
			for (std::size_t nIndex{0}, nSize{pVariable->sCache.size()}; nIndex < nSize; ++nIndex)
				pVariable->sCache[nIndex] = sDist(sEngine);
	}

	void VariableGraphNode::applyGradient(float nFactor)
	{
		for (std::size_t nVariableIndex{0}, nVariableSize{this->sVariableList.size()}; nVariableIndex < nVariableSize; ++nVariableIndex)
			for (std::size_t nIndex{0}, nSize{this->sVariableSizeList[nVariableIndex]}; nIndex < nSize; ++nIndex)
				this->sVariableList[nVariableIndex]->sCache[nIndex] -= nFactor * this->sVariableBackwardList[nVariableIndex]->sCache[nIndex];
	}
}