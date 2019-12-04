
#include "tinnet/includes/node/StandardNode.h"

#include "tinnet/includes/node/Node.h"

#include <utility>

namespace tinnet::node {
	StandardNode::StandardNode(
		Type							  eType,
		Shape &&						  sShape,
		bool							  bGradientEnabled,
		std::unique_ptr<std::uint8_t[]> &&pOutputBuffer,
		std::vector<Node *> &&			  sDeps,
		std::vector<GFunc> &&			  sGFunction) :
		Node{eType, std::move(sShape), bGradientEnabled, pOutputBuffer.get(), std::move(sDeps), std::move(sGFunction)},
		pOutputBuffer{std::move(pOutputBuffer)}
	{
	}
}	 // namespace tinnet::node