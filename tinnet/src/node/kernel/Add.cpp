
#include "tinnet/includes/node/kernel/Add.h"

#include <algorithm>
#include <functional>
#include <stdexcept>

namespace tinnet::node::kernel {
	memory::ScopedStorage __kernel__add(Node *pLeft, Node *pRight)
	{
		if (!pLeft || !pRight) throw std::runtime_error{"invalid node"};
		if (pLeft->eType != pRight->eType) throw std::runtime_error{"type mismatch"};

		const auto sLeftShape  = pLeft->sShape.squeeze();
		const auto sRightShape = pRight->sShape.squeeze();

		if (sLeftShape != sRightShape) throw std::runtime_error{"shape mismatch"};

		auto				  nSize{sLeftShape.size()};	   // == sRightShape.size()
		memory::ScopedStorage sResult{sizeof(float) * nSize};

		const auto *__restrict pL{pLeft->output().aligned<float>()};
		const auto *__restrict pR{pRight->output().aligned<float>()};

		std::transform(pL, pL + nSize, pR, sResult.aligned<float>(), std::plus<float>{});

		return sResult;
	}

	void __kernel__addGradient(Node *pNode, Node *pDeps)
	{
		auto nSize{pNode->sShape.size()};
		const auto *__restrict pL{pNode->gradient().aligned<float>()};
		auto *__restrict pR{pDeps->gradient().aligned<float>()};

		std::transform(pL, pL + nSize, pR, pR, std::plus<float>());
	}
}	 // namespace tinnet::node::kernel