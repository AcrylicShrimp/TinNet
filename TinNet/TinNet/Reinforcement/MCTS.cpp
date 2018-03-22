
/*
	2018.03.18
	Created by AcrylicShrimp.
*/

#include "MCTS.h"

namespace TinNet::Reinforcement
{
	Node::Node(uint16_t nLastAction, std::unique_ptr<State> &&pState, Node *pParent) :
		nLastAction{nLastAction},
		nFirstPlayerWin{0},
		nSecondPlayerWin{0},
		nTotal{0},
		nVisit{0},
		pState{std::move(pState)},
		pParent{pParent}
	{
		//Empty.
	}

	Node::Node(Node &&sSrc) :
		nLastAction{sSrc.nLastAction},
		nFirstPlayerWin{sSrc.nFirstPlayerWin},
		nSecondPlayerWin{sSrc.nSecondPlayerWin},
		nTotal{sSrc.nTotal},
		nVisit{sSrc.nVisit},
		pState{std::move(sSrc.pState)},
		pParent{sSrc.pParent},
		sChildList{std::move(sSrc.sChildList)}
	{
		//Empty.
	}

	Node &Node::operator=(Node &&sSrc)
	{
		if (&sSrc == this)
			return *this;

		this->nLastAction = sSrc.nLastAction;
		this->nFirstPlayerWin = sSrc.nFirstPlayerWin;
		this->nSecondPlayerWin = sSrc.nSecondPlayerWin;
		this->nTotal = sSrc.nTotal;
		this->nVisit = sSrc.nVisit;
		this->pState = std::move(sSrc.pState);
		this->pParent = sSrc.pParent;
		this->sChildList = std::move(sSrc.sChildList);

		return *this;
	}

	float Node::computeUCTValue(Player ePlayer)
	{
		if (!this->pParent)
			return .0f;

		if (!this->nTotal)
			return std::numeric_limits<float>::max();

		return static_cast<float>(ePlayer == Player::First ? this->nFirstPlayerWin : this->nSecondPlayerWin) / this->nTotal + std::sqrt(2.f * std::logf(static_cast<float>(this->pParent->nTotal)) / this->nTotal);
	}

	uint16_t Node::computeBestAction(Player ePlayer)
	{
		if (this->leafNode())
			return this->nLastAction;

		auto nAverageWin{.0f};

		for (auto &pNode : this->sChildList)
			nAverageWin += ePlayer == Player::First ? pNode->nFirstPlayerWin : pNode->nSecondPlayerWin;

		nAverageWin /= this->sChildList.size();

		std::vector<Node *> sNodeList;
		sNodeList.reserve(this->sChildList.size());

		for (auto &pNode : this->sChildList)
			if (nAverageWin <= (ePlayer == Player::First ? pNode->nFirstPlayerWin : pNode->nSecondPlayerWin))
				sNodeList.emplace_back(pNode.get());

		std::size_t nCount{1};
		Node *pMaxWinRateNode{sNodeList.front()};
		auto nMaxWinRate{ePlayer == Player::First ? sNodeList.front()->firstPlayerWinRate() : sNodeList.front()->secondPlayerWinRate()};

		for (std::size_t nIndex{1}, nSize{sNodeList.size()}; nIndex < nSize; ++nIndex)
		{
			auto nWinRate{ePlayer == Player::First ? sNodeList[nIndex]->firstPlayerWinRate() : sNodeList[nIndex]->secondPlayerWinRate()};

			if (nMaxWinRate < nWinRate)
			{
				nCount = 1;
				nMaxWinRate = nWinRate;
				pMaxWinRateNode = sNodeList[nIndex];
			}
			else if (nMaxWinRate - nWinRate < .025f)
				++nCount;
		}

		std::vector<Node *> sCandidateNodeList;
		sCandidateNodeList.reserve(nCount);

		for (auto &pNode : sNodeList)
		{
			auto nWinRate{ePlayer == Player::First ? pNode->firstPlayerWinRate() : pNode->secondPlayerWinRate()};

			if (nMaxWinRate - nWinRate < .025f)
				sCandidateNodeList.emplace_back(pNode);
		}

		static std::random_device sDevice;
		static std::mt19937 sEngine{sDevice()};

		return sCandidateNodeList[std::uniform_int_distribution<std::size_t>{0, sCandidateNodeList.size() - 1}(sEngine)]->nLastAction;
	}

	Node *Node::selectMostChildNode(Player ePlayer)
	{
		static std::random_device sDevice;
		static std::mt19937 sEngine{sDevice()};

		if (this->leafNode())
			return nullptr;

		std::size_t nCount{1};
		auto nUCTValue{this->sChildList.front()->computeUCTValue(ePlayer)};

		for (std::size_t nIndex{1}, nSize{this->sChildList.size()}; nIndex < nSize; ++nIndex)
		{
			auto nNewUCTValue{this->sChildList[nIndex]->computeUCTValue(ePlayer)};

			if (nUCTValue < nNewUCTValue)
			{
				nCount = 1;
				nUCTValue = nNewUCTValue;
			}
			else if (nUCTValue - nNewUCTValue < .001f)
				++nCount;
		}

		std::vector<Node *> sNodeList;
		sNodeList.reserve(nCount);

		for (auto &pNode : this->sChildList)
		{
			auto nValue{pNode->computeUCTValue(ePlayer)};

			if (nUCTValue - nValue < .001f)
				sNodeList.emplace_back(pNode.get());
		}

		return sNodeList[std::uniform_int_distribution<std::size_t>{0, sNodeList.size() - 1}(sEngine)];
	}

	Node *Node::selectChildNode(Player ePlayer)
	{
		auto pNode{this};

		while (!pNode->leafNode())
			pNode = pNode->selectMostChildNode(ePlayer);

		return pNode;
	}

	void Node::expandChildNode()
	{
		if (this->nVisit < this->pState->game()->maxVisit())
		{
			++this->nVisit;
			return;
		}

		auto sActionList{this->pState->game()->obtainValidActionList(this->pState.get())};

		for (auto nAction : sActionList)
		{
			auto pState{this->pState->game()->duplicateState(this->pState.get())};
			this->pState->game()->applyAction(pState.get(), nAction);
			this->sChildList.emplace_back(std::make_unique<Node>(nAction, std::move(pState), this));
		}
	}

	std::tuple<uint64_t, uint64_t, uint64_t> Node::simulation(Player ePlayer)
	{
		static std::random_device sDevice;
		static std::mt19937 sEngine{sDevice()};

		auto pState{this->pState->game()->duplicateState(this->pState.get())};
		auto nLastAction{this->nLastAction};

		for (;;)
		{
			auto sResult{this->pState->game()->obtainResult(pState.get(), nLastAction)};

			if (std::get<0>(sResult))
				return std::make_tuple(std::get<1>(sResult), std::get<2>(sResult), 1ui64);

			auto sActionList{this->pState->game()->obtainValidActionList(pState.get())};
			std::uniform_int_distribution<std::size_t> sDist{0, sActionList.size() - 1};

			this->pState->game()->applyAction(pState.get(), nLastAction = sActionList[sDist(sEngine)]);
		}
	}

	void Node::backProp(uint64_t nFirstPlayerWinCount, uint64_t nSecondPlayerWinCount, uint64_t nTotalCount)
	{
		for (auto pNode{this}; pNode; pNode = pNode->pParent)
		{
			pNode->nFirstPlayerWin += nFirstPlayerWinCount;
			pNode->nSecondPlayerWin += nSecondPlayerWinCount;
			pNode->nTotal += nTotalCount;
		}
	}

	void Node::update(Player ePlayer)
	{
		auto pNode{this->selectChildNode(ePlayer)};
		auto sResult{this->pState->game()->obtainResult(pNode->pState.get(), pNode->nLastAction)};
		
		if (std::get<0>(sResult))
		{
			pNode->backProp(std::get<1>(sResult), std::get<2>(sResult), 1);
			return;
		}

		pNode->expandChildNode();

		auto sSimulationResult{(pNode->leafNode() ? pNode : (pNode = pNode->selectMostChildNode(ePlayer)))->simulation(ePlayer)};
		pNode->backProp(std::get<0>(sSimulationResult), std::get<1>(sSimulationResult), std::get<2>(sSimulationResult));
	}

	MCTS::MCTS(Game *pGame) :
		pGame{pGame}
	{
		this->pRoot = std::make_unique<Node>(0, this->pGame->initState(), nullptr);
		this->pCurrentNode = this->pRoot.get();
	}

	void MCTS::reset()
	{
		this->pCurrentNode = this->pRoot.get();
	}

	void MCTS::update(Player ePlayer)
	{
		this->pCurrentNode->update(ePlayer);
	}

	uint16_t MCTS::computeBestAction(Player ePlayer)
	{
		return this->pCurrentNode->computeBestAction(ePlayer);
	}

	void MCTS::takeAction(uint16_t nAction)
	{
		for (auto &pNode : this->pCurrentNode->childList())
			if (pNode->lastAction() == nAction)
			{
				this->pCurrentNode = pNode.get();
				break;
			}
	}
}