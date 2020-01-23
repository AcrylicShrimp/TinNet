
#include "tinnet/includes/node/Builder.h"

#include "tinnet/includes/node/kernel/BasicArithmetic.h"
#include "tinnet/includes/node/kernel/MathFunction.h"

#include <algorithm>
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

	std::unique_ptr<Node> Builder::memory(Shape &&sShape, const float *pSource, bool bGradientEnabled)
	{
		memory::ScopedStorage sOutput{sizeof(float) * sShape.size()};
		std::copy(pSource, pSource + sShape.size(), sOutput.aligned<float>());

		return std::make_unique<Node>(
			Type::F32,
			std::move(sShape),
			bGradientEnabled,
			std::move(sOutput),
			std::vector<Node *>{},
			std::vector<Node::GFunc>{});
	}

	std::unique_ptr<Node>
		Builder::add(const std::unique_ptr<Node> &sLeft, const std::unique_ptr<Node> &sRight, bool bGradientEnabled)
	{
		return std::make_unique<Node>(
			Type::F32,
			Shape{sLeft->sShape},
			bGradientEnabled,
			kernel::__kernel__add(sLeft.get(), sRight.get()),
			std::vector<Node *>{sLeft.get(), sRight.get()},
			std::vector<Node::GFunc>{&kernel::__kernel__addGradient, &kernel::__kernel__addGradient});
	}

	std::unique_ptr<Node>
		Builder::sub(const std::unique_ptr<Node> &sLeft, const std::unique_ptr<Node> &sRight, bool bGradientEnabled)
	{
		return std::make_unique<Node>(
			Type::F32,
			Shape{sLeft->sShape},
			bGradientEnabled,
			kernel::__kernel__sub(sLeft.get(), sRight.get()),
			std::vector<Node *>{sLeft.get(), sRight.get()},
			std::vector<Node::GFunc>{&kernel::__kernel__subLGradient, &kernel::__kernel__subRGradient});
	}

	std::unique_ptr<Node>
		Builder::mul(const std::unique_ptr<Node> &sLeft, const std::unique_ptr<Node> &sRight, bool bGradientEnabled)
	{
		return std::make_unique<Node>(
			Type::F32,
			Shape{sLeft->sShape},
			bGradientEnabled,
			kernel::__kernel__mul(sLeft.get(), sRight.get()),
			std::vector<Node *>{sLeft.get(), sRight.get()},
			std::vector<Node::GFunc>{&kernel::__kernel__mulLGradient, &kernel::__kernel__mulRGradient});
	}

	std::unique_ptr<Node>
		Builder::div(const std::unique_ptr<Node> &sLeft, const std::unique_ptr<Node> &sRight, bool bGradientEnabled)
	{
		return std::make_unique<Node>(
			Type::F32,
			Shape{sLeft->sShape},
			bGradientEnabled,
			kernel::__kernel__div(sLeft.get(), sRight.get()),
			std::vector<Node *>{sLeft.get(), sRight.get()},
			std::vector<Node::GFunc>{&kernel::__kernel__divLGradient, &kernel::__kernel__divRGradient});
	}

	std::unique_ptr<Node> Builder::log(const std::unique_ptr<Node> &sLeft, bool bGradientEnabled)
	{
		return std::make_unique<Node>(
			Type::F32,
			Shape{sLeft->sShape},
			bGradientEnabled,
			kernel::__kernel__log(sLeft.get()),
			std::vector<Node *>{sLeft.get()},
			std::vector<Node::GFunc>{&kernel::__kernel__logGradient});
	}
}	 // namespace tinnet::node