
#include "tinnet/includes/node/StandardNode.h"

#include "tinnet/includes/node/Node.h"

#include <cstdint>
#include <utility>

namespace tinnet::node {
	StandardNode::StandardNode(
		Type					eType,
		Shape &&				sShape,
		bool					bGradientEnabled,
		memory::ScopedStorage &&sOutput,
		std::vector<Node *> &&	sDeps,
		std::vector<GFunc> &&	sGFunction) :
		Node{eType,
			 std::move(sShape),
			 bGradientEnabled,
			 sOutput.aligned<std::uint8_t>(),
			 std::move(sDeps),
			 std::move(sGFunction)},
		sOutput{std::move(sOutput)}
	{
	}
}	 // namespace tinnet::node