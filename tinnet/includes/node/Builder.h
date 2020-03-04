
#ifndef _TINNET_NODE_BUILDER_H

#define _TINNET_NODE_BUILDER_H

#include "tinnet/includes/memory/ScopedStorage.h"
#include "tinnet/includes/node/Node.h"
#include "tinnet/includes/node/Shape.h"
#include "tinnet/includes/node/Type.h"

#include <memory>

namespace tinnet::node {
	class Builder final {
	public:
		Builder()  = delete;
		~Builder() = delete;

	public:
		// TODO: Support multiple types here.
		// static std::unique_ptr<Node> memory(Type eType, Shape &&sShape, bool bGradientEnabled, std::uint8_t
		// *pOutput);
		static std::unique_ptr<Node> memory(Shape &&sShape, const float *pSource, bool bGradientEnabled = false);
		static std::unique_ptr<Node> neg(const std::unique_ptr<Node> &sLeft, bool bGradientEnabled = false);
		static std::unique_ptr<Node>
			add(const std::unique_ptr<Node> &sLeft, const std::unique_ptr<Node> &sRight, bool bGradientEnabled = false);
		static std::unique_ptr<Node>
			sub(const std::unique_ptr<Node> &sLeft, const std::unique_ptr<Node> &sRight, bool bGradientEnabled = false);
		static std::unique_ptr<Node>
			mul(const std::unique_ptr<Node> &sLeft, const std::unique_ptr<Node> &sRight, bool bGradientEnabled = false);
		static std::unique_ptr<Node>
			div(const std::unique_ptr<Node> &sLeft, const std::unique_ptr<Node> &sRight, bool bGradientEnabled = false);

		static std::unique_ptr<Node> log(const std::unique_ptr<Node> &sLeft, bool bGradientEnabled = false);

		static std::unique_ptr<Node>
			relu(const std::unique_ptr<Node> &sLeft, float nA = .1f, bool bGradientEnabled = false);
	};

}	 // namespace tinnet::node

inline std::unique_ptr<tinnet::node::Node> operator-(std::unique_ptr<tinnet::node::Node> &sNode)
{
	return tinnet::node::Builder::neg(sNode, false);
}

inline std::unique_ptr<tinnet::node::Node>
	operator+(std::unique_ptr<tinnet::node::Node> &sLeft, std::unique_ptr<tinnet::node::Node> &sRight)
{
	return tinnet::node::Builder::add(sLeft, sRight, false);
}

inline std::unique_ptr<tinnet::node::Node>
	operator-(std::unique_ptr<tinnet::node::Node> &sLeft, std::unique_ptr<tinnet::node::Node> &sRight)
{
	return tinnet::node::Builder::sub(sLeft, sRight, false);
}

inline std::unique_ptr<tinnet::node::Node>
	operator*(std::unique_ptr<tinnet::node::Node> &sLeft, std::unique_ptr<tinnet::node::Node> &sRight)
{
	return tinnet::node::Builder::mul(sLeft, sRight, false);
}

inline std::unique_ptr<tinnet::node::Node>
	operator/(std::unique_ptr<tinnet::node::Node> &sLeft, std::unique_ptr<tinnet::node::Node> &sRight)
{
	return tinnet::node::Builder::div(sLeft, sRight, false);
}

#endif