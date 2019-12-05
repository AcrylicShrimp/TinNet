
#include "tinnet/includes/node/Builder.h"

#include "tinnet/includes/node/StandardNode.h"

#include <cstdint>
#include <utility>
#include <vector>

namespace tinnet::node {
	// std::unique_ptr<Node> Builder::wrap(Type eType, Shape &&sShape, bool bGradientEnabled, std::uint8_t *pOutput)
	// {
	// 	return std::make_unique<Node>(
	// 		eType,
	// 		std::move(sShape),
	// 		bGradientEnabled,
	// 		pOutput,
	// 		std::vector<Node *>{},
	// 		std::vector<Node::GFunc>{});
	// }

	std::unique_ptr<Node> Builder::wrap(Shape &&sShape, float *pSource, bool bGradientEnabled)
	{
		return std::make_unique<Node>(
			Type::F32,
			std::move(sShape),
			bGradientEnabled,
			reinterpret_cast<std::uint8_t *>(pSource),
			std::vector<Node *>{},
			std::vector<Node::GFunc>{});
	}

	std::unique_ptr<StandardNode> variable(Shape &&sShape, memory::ScopedStorage &&sInitial, bool bGradientEnabled)
	{
		return std::make_unique<StandardNode>(
			Type::F32,
			std::move(sShape),
			bGradientEnabled,
			std::move(sInitial),
			std::vector<Node *>{},
			std::vector<Node::GFunc>{});
	}
}	 // namespace tinnet::node