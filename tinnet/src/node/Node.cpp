
#include "tinnet/includes/node/Node.h"

#include <algorithm>
#include <tuple>
#include <utility>

namespace tinnet::node {
	Node::Node(
		Type				  eType,
		Shape &&			  sShape,
		bool				  bGradientEnabled,
		std::uint8_t *const	  pOutput,
		std::vector<Node *> &&sDeps,
		std::vector<GFunc> && sGFunction) :
		eType{eType},
		sShape{std::move(sShape)},
		nElement{this->sShape.size()},
		bGradientEnabled{bGradientEnabled},
		pOutput{pOutput},
		sDeps{std::move(sDeps)},
		sGFunction{std::move(sGFunction)}
	{
		if (!this->bGradientEnabled)
			for (auto pDepsNode: this->sDeps)
				if ((this->bGradientEnabled = this->bGradientEnabled || pDepsNode->bGradientEnabled)) break;

		if (this->bGradientEnabled)
			this->pGradient = std::make_unique<std::uint8_t[]>(sizeof(float) * this->sShape.size());
		else
			this->pGradient = nullptr;
	}

	void Node::computeGradient()
	{
		if (!this->bGradientEnabled) return;

		// Fills the target gradient buffer with ones.
		std::fill(
			reinterpret_cast<float *>(this->pGradient.get()),
			reinterpret_cast<float *>(this->pGradient.get()) + this->nElement,
			1.f);

		// Builds a dependency list for only nodes that enabled gradient.
		std::vector<std::tuple<Node *, Node *, std::size_t>> sDepsChain;
		sDepsChain.reserve(this->sDeps.size());

		for (std::size_t nD{0}, nMaxD{this->sDeps.size()}; nD < nMaxD; ++nD)
			if (this->sDeps[nD]->bGradientEnabled) sDepsChain.emplace_back(this, this->sDeps[nD], nD);

		for (std::size_t nIndex{0}; nIndex != sDepsChain.size();)
			for (std::size_t nMaxIndex{sDepsChain.size()}; nIndex < nMaxIndex; ++nIndex) {
				auto *pNode{std::get<1>(sDepsChain[nIndex])};

				sDepsChain.reserve(sDepsChain.size() + pNode->sDeps.size());

				for (std::size_t nD{0}, nMaxD{pNode->sDeps.size()}; nD < nMaxD; ++nD)
					if (pNode->sDeps[nD]->bGradientEnabled) sDepsChain.emplace_back(this, pNode->sDeps[nD], nD);
			}

		// Fills with zeros for all nodes
		for (auto &sChainDeps: sDepsChain) {
			auto *pNode{std::get<1>(sChainDeps)};

			std::fill(
				reinterpret_cast<float *>(pNode->pGradient.get()),
				reinterpret_cast<float *>(pNode->pGradient.get()) + pNode->nElement,
				.0f);
		}

		// Calls all gradient computation kernels.
		for (auto &sChainDeps: sDepsChain) {
			auto  nD{std::get<2>(sChainDeps)};
			auto *pNode{std::get<0>(sChainDeps)};
			auto *pDepsNode{std::get<1>(sChainDeps)};

			pNode->sGFunction[nD](pNode->eType, pNode->sShape, pNode->pGradient.get(), pDepsNode->pGradient.get());
		}
	}
}	 // namespace tinnet::node