
/*
	2018.06.17
	Created by AcrylicShrimp.
*/

#include "BackpropNode.h"

namespace TinNet::GraphNode
{
	BackpropNode::BackpropNode(Graph *pGraph, const std::string &sName) :
		Node(pGraph, sName),
		pGradient{nullptr}
	{
		//Empty.
	}

	std::string BackpropNode::type() const
	{
		return "backprop";
	}

	void BackpropNode::notifyShapeUpdated()
	{
		if (this->pGradient && this->pGradient->sCache.size() < this->shape().element())
		{
			this->pGraph->cacheContainer().release(this->pGradient);
			this->pGradient = this->pGraph->cacheContainer().request(this->shape().element());
		}
	}

	void BackpropNode::notifyBackwardEnabled()
	{
		if (!this->pGradient)
			this->pGradient = this->pGraph->cacheContainer().request(this->shape().element());
	}

	void BackpropNode::notifyBackwardDisabled()
	{
		if (this->pGradient)
			this->pGraph->cacheContainer().release(this->pGradient);

		this->pGradient = nullptr;
	}

	Cache BackpropNode::backward()
	{
		this->computeBackward(this->pGradient);

		return this->pGradient->sCache;
	}

	void BackpropNode::beginGradient()
	{
		this->pGradient->sCache.one();
		this->pGradient->bDirty = false;
	}
}