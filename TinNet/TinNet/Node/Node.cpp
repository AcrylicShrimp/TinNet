
/*
	2018.10.21
	Created by AcrylicShrimp.
*/

#include "Node.h"

#include "../Core/Graph.h"

namespace TinNet::Node
{
	Compute::Denormal Node::sDenormal;

	Node::Node(Core::Graph *pGraph, std::string_view sName) :
		pGraph{pGraph},
		sName{sName},
		bShapeDirty{true},
		bOutputDirty{true},
		pGradientDirty{nullptr}
	{
		assert(pGraph);
	}

	NodeInput *Node::operator[](const std::string &sInputName)
	{
		auto iIndex{this->sNodeInputMap.find(sInputName)};

		return iIndex == this->sNodeInputMap.cend() ? nullptr : iIndex->second;
	}

	const NodeInput *Node::operator[](const std::string &sInputName) const
	{
		auto iIndex{this->sNodeInputMap.find(sInputName)};

		return iIndex == this->sNodeInputMap.cend() ? nullptr : iIndex->second;
	}

	Node &Node::markDirty(bool bDirtyShape)
	{
		this->bShapeDirty = this->bShapeDirty || bDirtyShape;
		this->bOutputDirty = true;
		this->pGradientDirty = nullptr;

		for (auto *pNode : this->sRevDeps)
		{
			pNode->bShapeDirty = pNode->bShapeDirty || bDirtyShape;
			pNode->bOutputDirty = true;
			pNode->pGradientDirty = nullptr;
		}

		return *this;
	}

	Node &Node::evalShape()
	{
		if (!this->bShapeDirty)
			return *this;

		for (const auto sPair : this->sNodeInputMap)
			sPair.second->inputNode()->evalShape();

		this->__evaluateShape();
		this->bShapeDirty = false;

		return *this;
	}

	Node &Node::evalOutput()
	{
		if (!this->bOutputDirty)
			return *this;

		this->sOutput.resize(this->evalShape().sShape.size());

		this->__evaluateOutput();
		this->bOutputDirty = false;

		return *this;
	}

	Node &Node::evalGradient(const Node *pDy)
	{
		if (this->pGradientDirty == pDy)
			return *this;

		this->sGradient.resize(this->evalShape().sShape.size());

		if (pDy == this)
		{
			this->sGradient.span().fillOne();
			this->pGradientDirty = pDy;

			return *this;
		}

		this->sGradient.span().fillZero();

		for (const auto *pRevNodeInput : this->sRevNodeInputList)
			if (pRevNodeInput->pNode == pDy || pRevNodeInput->pNode->hasRevDeps(pDy))
				pRevNodeInput->fBackwardOp(pDy);

		this->pGradientDirty = pDy;

		return *this;
	}

	const NodeType *Node::type() const
	{
		return this->pGraph->sNodeTypeManager.type<Node>();
	}
}