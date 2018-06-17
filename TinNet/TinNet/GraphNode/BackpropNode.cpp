
/*
	2018.06.17
	Created by AcrylicShrimp.
*/

#include "BackpropNode.h"

namespace TinNet::GraphNode
{
	BackpropNode::BackpropNode(Graph *pGraph, const std::string &sName) :
		Node(pGraph, sName),
		pGradient{nullptr},
		pGradientTemp{nullptr}
	{
		//Empty.
	}

	const std::string &BackpropNode::type() const
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

		if (this->pGradientTemp && this->pGradientTemp->sCache.size() < this->shape().element())
		{
			this->pGraph->cacheContainer().release(this->pGradientTemp);
			this->pGradientTemp = this->pGraph->cacheContainer().request(this->shape().element());
		}
	}

	void BackpropNode::notifyBackwardEnabled()
	{
		if (!this->pGradient)
			this->pGradient = this->pGraph->cacheContainer().request(this->shape().element());

		if (!this->pGradientTemp)
			this->pGradientTemp = this->pGraph->cacheContainer().request(this->shape().element());
	}

	void BackpropNode::notifyBackwardDisabled()
	{
		if (this->pGradient)
			this->pGraph->cacheContainer().release(this->pGradient);

		if (this->pGradientTemp)
			this->pGraph->cacheContainer().release(this->pGradientTemp);

		this->pGradient = nullptr;
		this->pGradientTemp = nullptr;
	}

	Cache BackpropNode::backward()
	{
		this->computeBackward(this->pGradient, this->pGradientTemp);

		return this->pGradient->sCache;
	}
}