
#include "tinnet/includes/node/kernel/BasicArithmetic.h"

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

		auto *__restrict pD{sResult.aligned<float>()};
		const auto *__restrict pL{pLeft->output().aligned<float>()};
		const auto *__restrict pR{pRight->output().aligned<float>()};

		for (std::size_t nIndex{0}; nIndex < nSize; ++nIndex) pD[nIndex] = pL[nIndex] + pR[nIndex];

		return sResult;
	}

	memory::ScopedStorage __kernel__sub(Node *pLeft, Node *pRight)
	{
		if (!pLeft || !pRight) throw std::runtime_error{"invalid node"};
		if (pLeft->eType != pRight->eType) throw std::runtime_error{"type mismatch"};

		const auto sLeftShape  = pLeft->sShape.squeeze();
		const auto sRightShape = pRight->sShape.squeeze();

		if (sLeftShape != sRightShape) throw std::runtime_error{"shape mismatch"};

		auto				  nSize{sLeftShape.size()};	   // == sRightShape.size()
		memory::ScopedStorage sResult{sizeof(float) * nSize};

		auto *__restrict pD{sResult.aligned<float>()};
		const auto *__restrict pL{pLeft->output().aligned<float>()};
		const auto *__restrict pR{pRight->output().aligned<float>()};

		for (std::size_t nIndex{0}; nIndex < nSize; ++nIndex) pD[nIndex] = pL[nIndex] - pR[nIndex];

		return sResult;
	}

	memory::ScopedStorage __kernel__mul(Node *pLeft, Node *pRight)
	{
		if (!pLeft || !pRight) throw std::runtime_error{"invalid node"};
		if (pLeft->eType != pRight->eType) throw std::runtime_error{"type mismatch"};

		const auto sLeftShape  = pLeft->sShape.squeeze();
		const auto sRightShape = pRight->sShape.squeeze();

		if (sLeftShape != sRightShape) throw std::runtime_error{"shape mismatch"};

		auto				  nSize{sLeftShape.size()};	   // == sRightShape.size()
		memory::ScopedStorage sResult{sizeof(float) * nSize};

		auto *__restrict pD{sResult.aligned<float>()};
		const auto *__restrict pL{pLeft->output().aligned<float>()};
		const auto *__restrict pR{pRight->output().aligned<float>()};

		for (std::size_t nIndex{0}; nIndex < nSize; ++nIndex) pD[nIndex] = pL[nIndex] * pR[nIndex];

		return sResult;
	}

	memory::ScopedStorage __kernel__div(Node *pLeft, Node *pRight)
	{
		if (!pLeft || !pRight) throw std::runtime_error{"invalid node"};
		if (pLeft->eType != pRight->eType) throw std::runtime_error{"type mismatch"};

		const auto sLeftShape  = pLeft->sShape.squeeze();
		const auto sRightShape = pRight->sShape.squeeze();

		if (sLeftShape != sRightShape) throw std::runtime_error{"shape mismatch"};

		auto				  nSize{sLeftShape.size()};	   // == sRightShape.size()
		memory::ScopedStorage sResult{sizeof(float) * nSize};

		auto *__restrict pD{sResult.aligned<float>()};
		const auto *__restrict pL{pLeft->output().aligned<float>()};
		const auto *__restrict pR{pRight->output().aligned<float>()};

		for (std::size_t nIndex{0}; nIndex < nSize; ++nIndex) pD[nIndex] = pL[nIndex] / (pR[nIndex] + 1e-5f);

		return sResult;
	}

	void __kernel__addGradient(Node *pNode, Node *pDeps)
	{
		auto nSize{pNode->sShape.size()};
		auto *__restrict pD{pDeps->gradient().aligned<float>()};
		const auto *__restrict pG{pNode->gradient().aligned<float>()};

		for (std::size_t nIndex{0}; nIndex < nSize; ++nIndex) pD[nIndex] += pG[nIndex];
	}

	void __kernel__subLGradient(Node *pNode, Node *pDeps)
	{
		auto nSize{pNode->sShape.size()};
		auto *__restrict pD{pDeps->gradient().aligned<float>()};
		const auto *__restrict pG{pNode->gradient().aligned<float>()};

		for (std::size_t nIndex{0}; nIndex < nSize; ++nIndex) pD[nIndex] += pG[nIndex];
	}

	void __kernel__subRGradient(Node *pNode, Node *pDeps)
	{
		auto nSize{pNode->sShape.size()};
		auto *__restrict pD{pDeps->gradient().aligned<float>()};
		const auto *__restrict pG{pNode->gradient().aligned<float>()};

		for (std::size_t nIndex{0}; nIndex < nSize; ++nIndex) pD[nIndex] -= pG[nIndex];
	}

	void __kernel__mulLGradient(Node *pNode, Node *pDeps)
	{
		auto nSize{pNode->sShape.size()};
		auto *__restrict pD{pDeps->gradient().aligned<float>()};
		const auto *__restrict pG{pNode->gradient().aligned<float>()};
		const auto *__restrict pR{pNode->deps()[1]->output().aligned<float>()};

		for (std::size_t nIndex{0}; nIndex < nSize; ++nIndex) pD[nIndex] += pG[nIndex] * pR[nIndex];
	}

	void __kernel__mulRGradient(Node *pNode, Node *pDeps)
	{
		auto nSize{pNode->sShape.size()};
		auto *__restrict pD{pDeps->gradient().aligned<float>()};
		const auto *__restrict pG{pNode->gradient().aligned<float>()};
		const auto *__restrict pL{pNode->deps()[0]->output().aligned<float>()};

		for (std::size_t nIndex{0}; nIndex < nSize; ++nIndex) pD[nIndex] += pG[nIndex] * pL[nIndex];
	}

	void __kernel__divLGradient(Node *pNode, Node *pDeps)
	{
		auto nSize{pNode->sShape.size()};
		auto *__restrict pD{pDeps->gradient().aligned<float>()};
		const auto *__restrict pG{pNode->gradient().aligned<float>()};
		const auto *__restrict pR{pNode->deps()[1]->output().aligned<float>()};

		for (std::size_t nIndex{0}; nIndex < nSize; ++nIndex) pD[nIndex] += pG[nIndex] / (pR[nIndex] + 1e-5f);
	}

	void __kernel__divRGradient(Node *pNode, Node *pDeps)
	{
		auto nSize{pNode->sShape.size()};
		auto *__restrict pD{pDeps->gradient().aligned<float>()};
		const auto *__restrict pG{pNode->gradient().aligned<float>()};
		const auto *__restrict pL{pNode->deps()[0]->output().aligned<float>()};
		const auto *__restrict pR{pNode->deps()[1]->output().aligned<float>()};

		for (std::size_t nIndex{0}; nIndex < nSize; ++nIndex)
			pD[nIndex] += pG[nIndex] * pL[nIndex] / (pR[nIndex] * pR[nIndex] + 1e-5f);
	}
}	 // namespace tinnet::node::kernel