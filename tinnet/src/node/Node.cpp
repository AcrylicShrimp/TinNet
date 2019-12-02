
#include "tinnet/includes/node/Node.h"

#include <utility>

namespace tinnet::node {
	Node::Node(Type eType, Shape &&eShape, const std::uint8_t *const pOutput, std::vector<Node *> &&sDeps) noexcept :
		eType{eType},
		sShape{std::move(sShape)},
		pOutput{pOutput},
		sDeps{std::move(sDeps)}
	{
	}
}	 // namespace tinnet::node