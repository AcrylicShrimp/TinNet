
/*
	2018.06.17
	Created by AcrylicShrimp.
*/

#include "VariableNode.h"

namespace TinNet::GraphNode
{
	VariableNode::VariableNode(Graph *pGraph, const std::string &sName, NodePtr pSharingNode) :
		FullNode(pGraph, sName),
		Initializable(pGraph),
		pSharingNode{static_cast<VariableNode *>(pSharingNode)}
	{
		//Empty.
	}

	VariableNode::~VariableNode()
	{
		if (!this->pSharingNode)
			for (auto sVariable : this->sVariableList)
				this->pGraph->cacheContainer().release(sVariable);

		for (auto sVariableGradient : this->sVariableGradientList)
			this->pGraph->cacheContainer().release(sVariableGradient);

		this->sVariableSizeList.clear();
		this->sVariableList.clear();
		this->sVariableGradientList.clear();
	}

	void VariableNode::notifyShapeUpdated()
	{
		if (this->sVariableList.empty())
			if (this->pSharingNode)
			{
				this->sVariableSizeList = this->pSharingNode->sVariableSizeList;
				this->sVariableList = this->pSharingNode->sVariableList;
			}
			else
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