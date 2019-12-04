
#ifndef _TINNET_NODE_STANDARDNODE_H

#define _TINNET_NODE_STANDARDNODE_H

#include "tinnet/includes/node/Node.h"
#include "tinnet/includes/node/Shape.h"
#include "tinnet/includes/node/Type.h"

#include <cstdint>
#include <functional>
#include <memory>
#include <vector>

namespace tinnet::node {
	class StandardNode : public Node {
	private:
		std::unique_ptr<std::uint8_t[]> pOutputBuffer;

	public:
		StandardNode(
			Type							  eType,
			Shape &&						  sShape,
			bool							  bGradientEnabled,
			std::unique_ptr<std::uint8_t[]> &&pOutputBuffer,
			std::vector<Node *> &&			  sDeps,
			std::vector<GFunc> &&			  sGFunction);
		virtual ~StandardNode() noexcept = default;
	};
}	 // namespace tinnet::node

#endif