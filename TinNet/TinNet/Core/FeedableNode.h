
/*
	2018.10.22
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_CORE_FEEDABLENODE_H

#define _CLASS_TINNET_CORE_FEEDABLENODE_H

#include "Node.h"		//TinNet::Core::Node

#include <array>		//std::array
#include <cstddef>		//std::size_t

namespace TinNet::Core
{
	template<std::size_t In> class FeedableNode : public Node
	{
	protected:
		std::array<Node *, In> sIn;
		
	public:
		FeedableNode(const std::array<Node *, In> &sIn) noexcept;
		FeedableNode(const FeedableNode &sSrc) = delete;
		virtual ~FeedableNode() noexcept = default;
		
	public:
		FeedableNode &operator=(const FeedableNode &sSrc) = delete;
		
	public:
		inline const std::array<Node *, In> &in() const noexcept;
	};

	template<std::size_t In> inline const std::array<Node *, In> &FeedableNode<In>::in() const noexcept
	{
		return this->sIn;
	}
}

#include "FeedableNode.hpp"

#endif