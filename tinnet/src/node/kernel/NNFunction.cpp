
#include "tinnet/includes/node/kernel/NNFunction.h"

#include <stdexcept>

namespace tinnet::node::kernel {
	memory::ScopedStorage __kernel__relu(Node *pNode, float nA)
	{
		if (!pNode) throw std::runtime_error{"invalid node"};

		auto				  nSize{pNode->sShape.size()};
		memory::ScopedStorage sResult{sizeof(float) * nSize};

		auto *__restrict pD{sResult.aligned<float>()};
		const auto *__restrict pL{pNode->output().aligned<float>()};

		auto fRectify{[](float nV, float nA) {
			return nV < .0f ? nA * nV : nV;
		}};

		for (std::size_t nIndex{0}; nIndex < nSize; ++nIndex) pD[nIndex] = fRectify(pL[nIndex], nA);

		return sResult;
	}

	void __kernel__reluGradient(Node *pNode, Node *pDeps, float nA)
	{
		auto nSize{pNode->sShape.size()};
		auto *__restrict pD{pDeps->gradient().aligned<float>()};
		const auto *__restrict pG{pNode->gradient().aligned<float>()};
		const auto *__restrict pL{pNode->deps()[0]->output().aligned<float>()};

		auto fRectify{[](float nV, float nA, float nG) {
			return nV < .0f ? nA * nG : nG;
		}};

		for (std::size_t nIndex{0}; nIndex < nSize; ++nIndex) pD[nIndex] += fRectify(pL[nIndex], nA, pG[nIndex]);
	}
}	 // namespace tinnet::node::kernel