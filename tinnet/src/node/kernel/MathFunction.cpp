
#include "tinnet/includes/node/kernel/MathFunction.h"

#include <cmath>
#include <stdexcept>

namespace tinnet::node::kernel {
	memory::ScopedStorage __kernel__log(Node *pNode)
	{
		if (!pNode) throw std::runtime_error{"invalid node"};

		auto				  nSize{pNode->sShape.size()};
		memory::ScopedStorage sResult{sizeof(float) * nSize};

		auto *__restrict pD{sResult.aligned<float>()};
		const auto *__restrict pL{pNode->output().aligned<float>()};

		for (std::size_t nIndex{0}; nIndex < nSize; ++nIndex) pD[nIndex] = std::log(pL[nIndex] + 1e-5f);

		return sResult;
	}

	void __kernel__logGradient(Node *pNode, Node *pDeps)
	{
		auto nSize{pNode->sShape.size()};
		auto *__restrict pD{pDeps->gradient().aligned<float>()};
		const auto *__restrict pG{pNode->gradient().aligned<float>()};
		const auto *__restrict pL{pNode->deps()[0]->output().aligned<float>()};

		for (std::size_t nIndex{0}; nIndex < nSize; ++nIndex) pD[nIndex] += pG[nIndex] / (pL[nIndex] + 1e-5f);
	}
}	 // namespace tinnet::node::kernel