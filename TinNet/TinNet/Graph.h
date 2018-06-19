
/*
	2018.06.17
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPH_H

#define _CLASS_TINNET_GRAPH_H

#include "TinNetDLL.h"

#include "CacheContainer.h"
#include "Feedable.h"
#include "Initializable.h"
#include "Node.h"
#include "ShapedCache.h"

#include <algorithm>
#include <cstddef>
#include <cctype>
#include <initializer_list>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

//DELETEME
#include <cmath>
#include <random>

namespace TinNet
{
	class TINNET_DLL Graph final
	{
	private:
		std::vector<NodePtr> sOrderedNodeList;
		std::vector<FeedablePtr> sFeedableList;
		std::vector<InitializablePtr> sInitializableList;
		std::unordered_map<std::string, std::unique_ptr<Node>> sNodeMap;
		CacheContainer sCacheContainer;

	public:
		Graph() = default;
		Graph(const Graph &sSrc) = delete;
		~Graph();

	public:
		Graph &operator=(const Graph &sSrc) = delete;

	public:
		inline CacheContainer &cacheContainer();
		inline const CacheContainer &cacheContainer() const;
		inline void registerFeedable(FeedablePtr pFeedable);
		inline void registerInitializable(InitializablePtr pInitialiable);
		inline NodePtr node(const std::string &sName);
		inline const NodePtr node(const std::string &sName) const;
		template<class T> inline T *node(const std::string &sName);
		template<class T> inline const T *node(const std::string &sName) const;
		template<class T, class ...P> inline T *addNode(const std::string &sName, P &&...sParam);
		void initialize();
		void enableBackward();
		void disableBackward();
		void feed(const std::vector<ShapedCache> &sFeedList);
		void feed(std::initializer_list<ShapedCache> sFeedList);
		void computeGradient();
		void applyGradient(float nFactor);
	};

	inline CacheContainer &Graph::cacheContainer()
	{
		return this->sCacheContainer;
	}

	inline const CacheContainer &Graph::cacheContainer() const
	{
		return this->sCacheContainer;
	}

	inline void Graph::registerFeedable(FeedablePtr pFeedable)
	{
		this->sFeedableList.emplace_back(pFeedable);
	}

	inline void Graph::registerInitializable(InitializablePtr pInitialiable)
	{
		this->sInitializableList.emplace_back(pInitialiable);
	}

	inline NodePtr Graph::node(const std::string &sName)
	{
		auto iIndex{this->sNodeMap.find(sName)};

		return iIndex == this->sNodeMap.cend() ? nullptr : iIndex->second.get();
	}

	inline const NodePtr Graph::node(const std::string &sName) const
	{
		auto iIndex{this->sNodeMap.find(sName)};

		return iIndex == this->sNodeMap.cend() ? nullptr : iIndex->second.get();
	}

	template<class T> inline T *Graph::node(const std::string &sName)
	{
		auto iIndex{this->sNodeMap.find(sName)};

		return iIndex == this->sNodeMap.cend() ? nullptr : static_cast<T *>(iIndex->second.get());
	}

	template<class T> inline const T *Graph::node(const std::string &sName) const
	{
		auto iIndex{this->sNodeMap.find(sName)};

		return iIndex == this->sNodeMap.cend() ? nullptr : static_cast<T *>(iIndex->second.get());
	}

	template<class T, class ...P> inline T *Graph::addNode(const std::string &sName, P &&...sParam)
	{
		auto sTrimmedName{sName};

		sTrimmedName.erase(sTrimmedName.cbegin(), std::find_if(sTrimmedName.cbegin(), sTrimmedName.cend(), [](int nCharacter)
		{
			return !std::isspace(nCharacter);
		}));
		sTrimmedName.erase(std::find_if(sTrimmedName.crbegin(), sTrimmedName.crend(), [](int nCharacter)
		{
			return !std::isspace(nCharacter);
		}).base(), sTrimmedName.cend());

		if (sTrimmedName.empty())
		{
			std::size_t nIndex{0};

			do
			{
				sTrimmedName = T::typeName();
				sTrimmedName += std::to_string(nIndex++);
			} while (this->sNodeMap.find(sTrimmedName) != this->sNodeMap.cend());
		}
		else if (this->sNodeMap.find(sTrimmedName) != this->sNodeMap.cend())
		{
			std::size_t nIndex{0};

			while (this->sNodeMap.find(sTrimmedName + std::to_string(++nIndex)) != this->sNodeMap.cend());

			sTrimmedName += std::to_string(nIndex);
		}

		this->sOrderedNodeList.emplace_back(this->sNodeMap.emplace(std::move(sTrimmedName), std::make_unique<T>(this, sTrimmedName, std::forward<P>(sParam)...)).first->second.get());

		return static_cast<T *>(this->sOrderedNodeList.back());
	}
}

#endif