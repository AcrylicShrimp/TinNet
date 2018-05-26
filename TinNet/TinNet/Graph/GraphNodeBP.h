
/*
	2018.05.26
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPH_GRAPHNODEBP_H

#define _CLASS_TINNET_GRAPH_GRAPHNODEBP_H

#include "../TinNetDLL.h"

#include "GraphNode.h"

#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace TinNet::Graph
{
	class TINNET_DLL GraphNodeBP
	{
	protected:
		std::string sName;
		std::vector<const GraphNodeBP *> sBackwardBPList;
		
	public:
		GraphNodeBP(const std::string &sName);
		GraphNodeBP(const GraphNodeBP &sSrc) = default;
		GraphNodeBP(GraphNodeBP &&sSrc) = default;
		virtual ~GraphNodeBP() = default;
		
	public:
		GraphNodeBP &operator=(const GraphNodeBP &sSrc) = default;
		GraphNodeBP &operator=(GraphNodeBP &&sSrc) = default;
		
	public:
		inline const std::string &name() const;
		std::unique_ptr<GraphNode> instantiate(class Graph *pGraph) const;

	protected:
		virtual std::unique_ptr<GraphNode> make(class Graph *pGraph) const = 0;
		inline void asBackwardNode(const GraphNodeBP *pNodeBP);
	};

	inline const std::string &GraphNodeBP::name() const
	{
		return this->sName;
	}

	inline void GraphNodeBP::asBackwardNode(const GraphNodeBP *pNodeBP)
	{
		this->sBackwardBPList.emplace_back(pNodeBP);
	}
}

#endif