
/*
	2018.06.09
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPH_NODE_CONVOLUTION_H

#define _CLASS_TINNET_GRAPH_NODE_CONVOLUTION_H

#include "../../TinNetDLL.h"

#include "../../Accessor.h"
#include "../../Cache.h"
#include "../../Iterator.h"
#include "../../Shape.h"
#include "../CacheContainer.h"
#include "../Graph.h"
#include "../GraphOp.h"
#include "../VariableGraphNode.h"

#include <cstddef>
#include <string>
#include <vector>

namespace TinNet::Graph::Node
{
	class TINNET_DLL Convolution final : public VariableGraphNode
	{
	protected:
		Shape sInputShape;
		Shape sInputInternalShape;
		Shape sOutputShape;
		Shape sKernelShape;
		Accessor sInputAccessor;
		Accessor sResultAccessor;
		Iterator<Accessor, Accessor, Accessor> sIterator;
		std::vector<std::size_t> sInputIndexList;
		std::size_t nKernelWidth;
		std::size_t nKernelHeight;
		std::size_t nHStride;
		std::size_t nVStride;
		std::size_t nHPaddingN;
		std::size_t nHPaddingP;
		std::size_t nVPaddingN;
		std::size_t nVPaddingP;
		
	public:
		Convolution(const std::string &sName, Graph *pGraph,
			std::size_t nKernelWidth,
			std::size_t nKernelHeight,
			std::size_t nHStride,
			std::size_t nVStride,
			std::size_t nOutputWidth,
			std::size_t nOutputHeight,
			std::size_t nOutputChannel);
		Convolution(const Convolution &sSrc) = delete;
		~Convolution() = default;
		
	public:
		Convolution &operator=(const Convolution &sSrc) = delete;
		
	public:
		virtual const Shape &shape() const override;
		virtual std::size_t maxBackwardNodeCount() const override;
		virtual void initNode() override;
		virtual void forwardPass(Cache sDestination) override;
		virtual void backwardPass(GraphNode *pBackward, Cache sDestination) override;
		virtual std::size_t fanIn() const override;
		virtual std::size_t fanOut() const override;
		virtual void backwardVariablePass() override;
	};
}

#endif