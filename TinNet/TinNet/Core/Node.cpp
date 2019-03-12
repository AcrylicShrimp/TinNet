
/*
	2018.10.21
	Created by AcrylicShrimp.
*/

#include "Node.h"

namespace TinNet::Core
{
	//Node::Node(Graph *pGraph, std::string_view sName) :
	//	pGraph{pGraph},
	//	sName{sName},
	//	sShape{0}
	//{
	//	//Empty.
	//}

	Node::Node(std::string_view sName) :
		sName{sName},
		bShapeDirty{true},
		sShape{0}
	{
		//Empty.
	}

	NodeInput *Node::operator[](std::string_view sNodeInputName)
	{
		auto iIndex{this->sNodeInputMap.find(std::string{sNodeInputName})};

		return iIndex == this->sNodeInputMap.cend() ? nullptr : iIndex->second;
	}

	const NodeInput *Node::operator[](std::string_view sNodeInputName) const
	{
		auto iIndex{this->sNodeInputMap.find(std::string{sNodeInputName})};

		return iIndex == this->sNodeInputMap.cend() ? nullptr : iIndex->second;
	}

	Node &Node::update()
	{
		if (!this->bShapeDirty)
			return *this;

		for (const auto sPair : this->sNodeInputMap)
			sPair.second->pNode->update();

		this->updateShape();
		this->bShapeDirty = false;

		return *this;
	}

	Node &Node::markDirty()
	{
		this->bShapeDirty = true;

		for (auto *pNode : this->sRevDeps)
			pNode->bShapeDirty = true;

		return *this;
	}

	Node &Node::evalOutput()
	{
		this->sOutput.resize(this->update().sShape.size());

		this->evaluate();

		return *this;
	}

	Node &Node::evalGradient(const Node *pDy)
	{
		this->sGradient.resize(this->update().sShape.size());

		if (pDy == this)
		{
			this->sGradient.span().fillOne();
			return *this;
		}

		this->sGradient.span().fillZero();

		for (const auto *pRevNodeInput : this->sRevNodeInputList)
			if (pRevNodeInput->pNode->hasRevDeps(pDy))
				this->sGradient.span().accumulateFrom(pRevNodeInput->fBackwardOp(pDy));

		return *this;
	}
}