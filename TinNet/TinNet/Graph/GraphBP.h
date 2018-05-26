
/*
	2018.05.26
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPH_GRAPHBP_H

#define _CLASS_TINNET_GRAPH_GRAPHBP_H

#include "../TinNetDLL.h"

#include "GraphNodeBP.h"

#include <initializer_list>
#include <memory>
#include <utility>
#include <vector>

namespace TinNet::Graph
{
	class TINNET_DLL GraphBP final
	{
	private:
		std::vector<std::unique_ptr<GraphNodeBP>> sNodeBPList;
		
	public:
		GraphBP() = default;
		GraphBP(const GraphBP &sSrc) = delete;
		GraphBP(GraphBP &&sSrc) = default;
		~GraphBP() = default;
		
	public:
		GraphBP &operator=(const GraphBP &sSrc) = delete;
		GraphBP &operator=(GraphBP &&sSrc) = default;
		
	public:
		inline std::unique_ptr<GraphNodeBP> *begin();
		inline const std::unique_ptr<GraphNodeBP> *begin() const;
		inline const std::unique_ptr<GraphNodeBP> *cbegin() const;
		inline std::unique_ptr<GraphNodeBP> *end();
		inline const std::unique_ptr<GraphNodeBP> *end() const;
		inline const std::unique_ptr<GraphNodeBP> *cend() const;
		template<class T, class ...P> inline GraphNodeBP *node(P &&...sParam);
	};

	inline std::unique_ptr<GraphNodeBP> *GraphBP::begin()
	{
		return this->sNodeBPList.data();
	}

	inline const std::unique_ptr<GraphNodeBP> *GraphBP::begin() const
	{
		return this->sNodeBPList.data();
	}

	inline const std::unique_ptr<GraphNodeBP> *GraphBP::cbegin() const
	{
		return this->sNodeBPList.data();
	}

	inline std::unique_ptr<GraphNodeBP> *GraphBP::end()
	{
		return this->sNodeBPList.data() + this->sNodeBPList.size();
	}

	inline const std::unique_ptr<GraphNodeBP> *GraphBP::end() const
	{
		return this->sNodeBPList.data() + this->sNodeBPList.size();
	}

	inline const std::unique_ptr<GraphNodeBP> *GraphBP::cend() const
	{
		return this->sNodeBPList.data() + this->sNodeBPList.size();
	}

	template<class T, class ...P> inline GraphNodeBP *GraphBP::node(P &&...sParam)
	{
		this->sNodeBPList.push_back(std::make_unique<T>(std::forward<P>(sParam)...));

		return this->sNodeBPList.back().get();
	}
}

#endif