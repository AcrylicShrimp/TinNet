
/*
	2018.06.17
	Created by AcrylicShrimp.
*/

#include "VariableNode.h"

namespace TinNet::GraphNode
{
	VariableNode::VariableNode(Graph *pGraph, const std::string &sName) :
		FullNode(pGraph, sName),
		Initializable(pGraph)
	{
		//Empty.
	}

	VariableNode::~VariableNode()
	{
		for (auto sVariableList : this->sVariableGradientList)
			this->pGraph->cacheContainer().release(sVariableList);

		this->sVariableGradientList.clear();
	}

	void VariableNode::notifyShapeUpdated()
	{
		if (this->sVariableList.empty())
			for (auto nVariableSize : this->sVariableSizeList)
				this->sVariableList.emplace_back(this->pGraph->cacheContainer().request(nVariableSize));

		this->FullNode::notifyShapeUpdated();
	}

	void VariableNode::notifyBackwardEnabled()
	{
		this->FullNode::notifyBackwardEnabled();

		if (this->sVariableGradientList.empty())
			for (auto nVariableSize : this->sVariableSizeList)
				this->sVariableGradientList.emplace_back(this->pGraph->cacheContainer().request(nVariableSize));
	}

	void VariableNode::notifyBackwardDisabled()
	{
		this->FullNode::notifyBackwardDisabled();

		for (auto pVariableGradient : this->sVariableGradientList)
			this->pGraph->cacheContainer().release(pVariableGradient);

		this->sVariableGradientList.clear();
	}

	std::vector<std::size_t> &VariableNode::gradientSizeList()
	{
		return this->sVariableSizeList;
	}

	std::vector<CachePtr> &VariableNode::gradientList()
	{
		return this->sVariableGradientList;
	}
}