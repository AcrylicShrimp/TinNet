
/*
	2019.01.19
	Created by AcrylicShrimp.
*/

#include "NodeInput.h"

#include "Node.h"

namespace TinNet::Node
{
	NodeInput::NodeInput(Node *pNode, std::string_view sName, const std::function<void (const Node *)> &fBackwardOp) :
		pNode{pNode},
		sName{sName},
		fBackwardOp{fBackwardOp},
		pInputNode{nullptr}
	{
		this->pNode->sNodeInputMap[this->sName] = this;
	}

	void NodeInput::attach(Node *pInputNode)
	{
		if (!pInputNode)
			return;

		if (this->pInputNode)
			return;

		/*
			Trace dependencies and merge into the owner node.
		*/
		this->sDepsSet.emplace(pInputNode);
		this->sDepsSet.insert(pInputNode->sDeps.cbegin(), pInputNode->sDeps.cend());
		this->pNode->sDeps.insert(this->sDepsSet.cbegin(), this->sDepsSet.cend());

		/*
			Trace reverse dependencies.
		*/
		pInputNode->sRevNodeInputList.emplace_back(this);

		for (auto *pDep : this->sDepsSet)
		{
			pDep->sRevDeps.emplace(this->pNode);
			pDep->sRevDeps.insert(this->pNode->sRevDeps.cbegin(), this->pNode->sRevDeps.cend());
		}
		
		this->pInputNode = pInputNode;
	}
}