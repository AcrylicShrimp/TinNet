
/*
	2018.06.02
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPH_NODE_MATMULBP_H

#define _CLASS_TINNET_GRAPH_NODE_MATMULBP_H

#include "../../TinNetDLL.h"

#include "../GraphNodeBP.h"
#include "MatMul.h"

#include <memory>
#include <string>

namespace TinNet::Graph::Node
{
	class TINNET_DLL MatMulBP final : public GraphNodeBP
	{
	public:
		MatMulBP(const std::string &sName, const GraphNodeBP *pLeftNodeBP, const GraphNodeBP *pRightNodeBP);
		MatMulBP(const MatMulBP &sSrc) = default;
		MatMulBP(MatMulBP &&sSrc) = default;
		~MatMulBP() = default;
		
	public:
		MatMulBP &operator=(const MatMulBP &sSrc) = default;
		MatMulBP &operator=(MatMulBP &&sSrc) = default;
		
	public:
		virtual std::unique_ptr<GraphNode> make(class Graph *pGraph) const;
	};
}

#endif