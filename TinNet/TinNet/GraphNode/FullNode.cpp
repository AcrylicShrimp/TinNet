
/*
	2018.06.17
	Created by AcrylicShrimp.
*/

#include "FullNode.h"

namespace TinNet::GraphNode
{
	FullNode::FullNode(Graph *pGraph, const std::string &sName) :
		BackpropNode(pGraph, sName),
		pOutput{nullptr}
	{
		//Empty.
	}

	FullNode::~FullNode()
	{
		if (this->pOutput)
			this->pGraph->cacheContainer().release(this->pOutput);

		this->pOutput = nullptr;
	}

	std::string FullNode::type() const
	{
		return "full";
	}

	void FullNode::notifyShapeUpdated()
	{
		if (!this->pOutput)
			this->pOutput = this->pGraph->cacheContainer().request(this->shape().element());
		else if (this->pOutput && this->pOutput->sCache.size() < this->shape().element())
		{
			this->pGraph->cacheContainer().release(this->pOutput);
			this->pOutput = this->pGraph->cacheContainer().request(this->shape().element());
		}

		this->BackpropNode::notifyShapeUpdated();
	}

	Cache FullNode::forward()
	{
		this->computeForward(this->pOutput);

		return this->pOutput->sCache;
	}
}