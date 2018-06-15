
/*
	2018.06.15
	Created by AcrylicShrimp.
*/

#include "ConvolutionBP.h"

namespace TinNet::Graph::Node
{
	ConvolutionBP::ConvolutionBP(const std::string &sName, const GraphNodeBP *pLeftNodeBP,
		std::size_t nKernelWidth,
		std::size_t nKernelHeight,
		std::size_t nOutputWidth,
		std::size_t nOutputHeight,
		std::size_t nOutputChannel,
		std::size_t nHStride,
		std::size_t nVStride) :
		GraphNodeBP(sName),
		nKernelWidth{nKernelWidth},
		nKernelHeight{nKernelHeight},
		nOutputWidth{nOutputWidth},
		nOutputHeight{nOutputHeight},
		nOutputChannel{nOutputChannel},
		nHStride{nHStride},
		nVStride{nVStride}
	{
		this->asBackwardNode(pLeftNodeBP);
	}

	std::unique_ptr<GraphNode> ConvolutionBP::make(class Graph *pGraph) const
	{
		return std::make_unique<Convolution>(this->sName, pGraph,
			this->nKernelWidth,
			this->nKernelHeight,
			this->nHStride,
			this->nVStride,
			this->nOutputWidth,
			this->nOutputHeight,
			this->nOutputChannel
			);
	}
}