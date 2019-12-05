
#ifndef _TINNET_NODE_STANDARDNODE_H

#define _TINNET_NODE_STANDARDNODE_H

#include "tinnet/includes/memory/ScopedStorage.h"
#include "tinnet/includes/node/Node.h"
#include "tinnet/includes/node/Shape.h"
#include "tinnet/includes/node/Type.h"

#include <vector>

namespace tinnet::node {
	class StandardNode : public Node {
	private:
		memory::ScopedStorage sOutput;

	public:
		StandardNode(
			Type					eType,
			Shape &&				sShape,
			bool					bGradientEnabled,
			memory::ScopedStorage &&sOutput,
			std::vector<Node *> &&	sDeps,
			std::vector<GFunc> &&	sGFunction);
		virtual ~StandardNode() noexcept = default;
	};
}	 // namespace tinnet::node

#endif