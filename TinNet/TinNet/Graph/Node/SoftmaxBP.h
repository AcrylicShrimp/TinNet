
/*
	2018.06.16
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPH_NODE_SOFTMAXBP_H

#define _CLASS_TINNET_GRAPH_NODE_SOFTMAXBP_H

#include "../../TinNetDLL.h"

#include "../GraphNodeBP.h"
#include "Softmax.h"

#include <memory>
#include <string>
#include <vector>

namespace TinNet::Graph::Node
{
	class TINNET_DLL SoftmaxBP final : public GraphNodeBP
	{
	protected:
		std::vector<bool> sAxis;

	public:
		SoftmaxBP(const std::string &sName, const GraphNodeBP *pLeftNodeBP, const std::vector<bool> sAxis = {});
		SoftmaxBP(const SoftmaxBP &sSrc) = default;
		SoftmaxBP(SoftmaxBP &&sSrc) = default;
		~SoftmaxBP() = default;
		
	public:
		SoftmaxBP &operator=(const SoftmaxBP &sSrc) = default;
		SoftmaxBP &operator=(SoftmaxBP &&sSrc) = default;
		
	public:
		virtual std::unique_ptr<GraphNode> make(class Graph *pGraph) const;
	};
}

#endif