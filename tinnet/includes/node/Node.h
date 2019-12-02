
#ifndef _TINNET_NODE_NODE_H

#define _TINNET_NODE_NODE_H

#include "tinnet/includes/node/Shape.h"
#include "tinnet/includes/node/Type.h"

#include <cstdint>
#include <vector>

namespace tinnet::node {
	class Node {
	public:
		const Type				  eType;
		const Shape				  sShape;
		const std::uint8_t *const pOutput;

	private:
		std::vector<Node *> sDeps;		 // Nodes that this instance depends on.
		std::vector<Node *> sRevDeps;	 // Nodes that depends on this instance.

	public:
		Node(Type eType, Shape &&eShape, const std::uint8_t *const pOutput, ) noexcept;
		virtual ~Node() noexcept = default;

	public:
		// TODO: Add here some gradient-related compute methods.
	};
}	 // namespace tinnet::node

#endif