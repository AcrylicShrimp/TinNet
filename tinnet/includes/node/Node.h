
#ifndef _TINNET_NODE_NODE_H

#define _TINNET_NODE_NODE_H

#include "tinnet/includes/memory/ScopedStorage.h"
#include "tinnet/includes/node/Shape.h"
#include "tinnet/includes/node/Type.h"

#include <cstdint>
#include <functional>
#include <vector>

namespace tinnet::node {
	class Node {
	public:
		using GFunc = std::function<void(Node *, Node *)>;

	public:
		const Type		  eType;
		const Shape		  sShape;
		const std::size_t nElement;

	private:
		bool				  bGradientEnabled;
		std::uint8_t *const	  pOutput;
		memory::ScopedStorage sGradient;
		std::vector<Node *>	  sDeps;	// Nodes that this instance depends on.
		std::vector<GFunc>	  sGFunction;

	public:
		Node(
			Type				  eType,
			Shape &&			  sShape,
			bool				  bGradientEnabled,
			std::uint8_t *const	  pOutput,
			std::vector<Node *> &&sDeps,
			std::vector<GFunc> && sGFunction);
		virtual ~Node() noexcept = default;

	public:
		void computeGradient();

	public:
		bool gradientEnabled() const noexcept
		{
			return this->bGradientEnabled;
		}
		std::uint8_t *output() noexcept
		{
			return this->pOutput;
		}
		const std::uint8_t *output() const noexcept
		{
			return this->pOutput;
		}
		std::uint8_t *gradient() noexcept
		{
			return this->sGradient.aligned<std::uint8_t>();
		}
		const std::uint8_t *gradient() const noexcept
		{
			return this->sGradient.aligned<std::uint8_t>();
		}
		const std::vector<Node *> &deps() const noexcept
		{
			return this->sDeps;
		}
	};
}	 // namespace tinnet::node

#endif