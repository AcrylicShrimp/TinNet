
/*
	2018.06.17
	Created by AcrylicShrimp.
*/

#include "Graph.h"

namespace TinNet
{
	Graph::~Graph()
	{
		this->disableBackward();

		this->sOrderedNodeList.clear();
		this->sInitializableList.clear();

		this->sFeedableMap.clear();
		this->sNodeMap.clear();
	}

	void Graph::initialize()
	{
		std::mt19937_64 sEngine{std::random_device{}()};

		for (auto pInitializable : this->sInitializableList)
		{
			std::normal_distribution<float> sDist{.0f, std::sqrt(2.f / pInitializable->fanIn())};

			pInitializable->initialize([&]()
			{
				return sDist(sEngine);
			});
		}
	}

	void Graph::enableBackward()
	{
		if (this->bEnabledBackward)
			return;

		this->bEnabledBackward = true;

		for (auto pNode : this->sOrderedNodeList)
			pNode->notifyBackwardEnabled();
	}

	void Graph::disableBackward()
	{
		if (!this->bEnabledBackward)
			return;

		this->bEnabledBackward = false;

		for (auto pNode : this->sOrderedNodeList)
			pNode->notifyBackwardDisabled();
	}

	void Graph::feed(NodeRef sNode, const ShapedCache &sShapedCache)
	{
		auto iIndex{this->sFeedableMap.find(&sNode)};

		if (iIndex != this->sFeedableMap.cend())
			iIndex->second->feed(sShapedCache);
	}

	void Graph::endFeed()
	{
		for (auto pNode : this->sOrderedNodeList)
			pNode->notifyShapeUpdated();

		this->sCacheContainer.setDirtyAll();
	}
}