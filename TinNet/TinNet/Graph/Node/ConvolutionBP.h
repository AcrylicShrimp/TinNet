
/*
	2018.06.15
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPH_NODE_CONVOLUTIONBP_H

#define _CLASS_TINNET_GRAPH_NODE_CONVOLUTIONBP_H

#include "../../TinNetDLL.h"

#include "../GraphNodeBP.h"
#include "Convolution.h"

#include <memory>
#include <string>

namespace TinNet::Graph::Node
{
	class TINNET_DLL ConvolutionBP final : public GraphNodeBP
	{
	protected:
		std::size_t nKernelWidth;
		std::size_t nKernelHeight;
		std::size_t nOutputWidth;
		std::size_t nOutputHeight;
		std::size_t nOutputChannel;
		std::size_t nHStride;
		std::size_t nVStride;

	public:
		ConvolutionBP(const std::string &sName, const GraphNodeBP *pLeftNodeBP,
			std::size_t nKernelWidth,
			std::size_t nKernelHeight,
			std::size_t nOutputWidth,
			std::size_t nOutputHeight,
			std::size_t nOutputChannel,
			std::size_t nHStride,
			std::size_t nVStride);
		ConvolutionBP(const ConvolutionBP &sSrc) = default;
		ConvolutionBP(ConvolutionBP &&sSrc) = default;
		~ConvolutionBP() = default;
		
	public:
		ConvolutionBP &operator=(const ConvolutionBP &sSrc) = default;
		ConvolutionBP &operator=(ConvolutionBP &&sSrc) = default;
		
	public:
		virtual std::unique_ptr<GraphNode> make(class Graph *pGraph) const;
	};
}

#endif