
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
		this->sFeedableList.clear();
		this->sInitializableList.clear();

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
		for (auto pNode : this->sOrderedNodeList)
			pNode->notifyBackwardEnabled();
	}

	void Graph::disableBackward()
	{
		for (auto pNode : this->sOrderedNodeList)
			pNode->notifyBackwardDisabled();
	}

	void Graph::feed(const std::vector<ShapedCache> &sFeedList)
	{
		std::size_t nIndex{0};

		for (auto pFeedable : this->sFeedableList)
			pFeedable->feed(sFeedList[nIndex++]);

		for (auto pNode : this->sOrderedNodeList)
			pNode->notifyShapeUpdated();

		this->sCacheContainer.setDirtyAll();
	}

	void Graph::feed(std::initializer_list<ShapedCache> sFeedList)
	{
		std::size_t nIndex{0};

		for (auto pFeedable : this->sFeedableList)
			pFeedable->feed(sFeedList.begin()[nIndex++]);

		for (auto pNode : this->sOrderedNodeList)
			pNode->notifyShapeUpdated();

		this->sCacheContainer.setDirtyAll();
	}
}