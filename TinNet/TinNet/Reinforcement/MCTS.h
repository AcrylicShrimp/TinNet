
/*
	2018.03.18
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_D3MCS_UTILITY_MCTS_H

#define _CLASS_D3MCS_UTILITY_MCTS_H

#include "../TinNetDLL.h"

#include "Game.h"

#include <cmath>
#include <cstdint>
#include <limits>
#include <memory>
#include <random>
#include <tuple>
#include <vector>

namespace TinNet::Reinforcement
{
	enum class Player
	{
		First,
		Second
	};

	class TINNET_DLL Node final
	{
	private:
		uint16_t nLastAction;
		uint64_t nFirstPlayerWin;
		uint64_t nSecondPlayerWin;
		uint64_t nTotal;
		uint64_t nVisit;
		std::unique_ptr<State> pState;
		Node *pParent;
		std::vector<std::unique_ptr<Node>> sChildList;

	public:
		Node(uint16_t nLastAction, std::unique_ptr<State> &&pState, Node *pParent);
		Node(const Node &sSrc) = delete;
		Node(Node &&sSrc);
		~Node() = default;

	public:
		Node &operator=(const Node &sSrc) = delete;
		Node &operator=(Node &&sSrc);

	public:
		inline uint16_t lastAction() const;
		inline uint64_t firstPlayerWin() const;
		inline uint64_t secondPlayerWin() const;
		inline uint64_t draw() const;
		inline uint64_t total() const;
		inline State *state();
		inline const State *state() const;
		inline Node *parent();
		inline const Node *parent() const;
		inline std::vector<std::unique_ptr<Node>> &childList();
		inline const std::vector<std::unique_ptr<Node>> &childList() const;
		inline bool leafNode() const;
		inline float firstPlayerWinRate() const;
		inline float secondPlayerWinRate() const;
		inline float drawRate() const;
		float computeUCTValue(Player ePlayer);
		uint16_t computeBestAction(Player ePlayer);
		Node *selectMostChildNode(Player ePlayer);
		Node *selectChildNode(Player ePlayer);
		void expandChildNode();
		std::tuple<uint64_t, uint64_t, uint64_t> simulation(Player ePlayer);
		void backProp(uint64_t nFirstPlayerWinCount, uint64_t nSecondPlayerWinCount, uint64_t nTotalCount);
		void update(Player ePlayer);
	};

	inline uint16_t Node::lastAction() const
	{
		return this->nLastAction;
	}

	inline uint64_t Node::firstPlayerWin() const
	{
		return this->nFirstPlayerWin;
	}

	inline uint64_t Node::secondPlayerWin() const
	{
		return this->nSecondPlayerWin;
	}

	inline uint64_t Node::draw() const
	{
		return this->nTotal - this->nFirstPlayerWin - this->nSecondPlayerWin;
	}

	inline uint64_t Node::total() const
	{
		return this->nTotal;
	}

	inline State *Node::state()
	{
		return this->pState.get();
	}

	inline const State *Node::state() const
	{
		return this->pState.get();
	}

	inline Node *Node::parent()
	{
		return this->pParent;
	}

	inline const Node *Node::parent() const
	{
		return this->pParent;
	}

	inline std::vector<std::unique_ptr<Node>> &Node::childList()
	{
		return this->sChildList;
	}

	inline const std::vector<std::unique_ptr<Node>> &Node::childList() const
	{
		return this->sChildList;
	}

	inline bool Node::leafNode() const
	{
		return this->sChildList.empty();
	}

	inline float Node::firstPlayerWinRate() const
	{
		return this->nTotal ? static_cast<float>(this->nFirstPlayerWin) / this->nTotal : .0f;
	}

	inline float Node::secondPlayerWinRate() const
	{
		return this->nTotal ? static_cast<float>(this->nSecondPlayerWin) / this->nTotal : .0f;
	}

	inline float Node::drawRate() const
	{
		return this->nTotal ? static_cast<float>(this->draw()) / this->nTotal : .0f;
	}

	class TINNET_DLL MCTS final
	{
	private:
		Game *pGame;
		std::unique_ptr<Node> pRoot;
		Node *pCurrentNode;
		
	public:
		MCTS(Game *pGame);
		~MCTS() = default;
		
	public:
		inline Node *root();
		inline const Node *root() const;
		inline Node *current();
		inline const Node *current() const;
		void reset();
		void update(Player ePlayer);
		uint16_t computeBestAction(Player ePlayer);
		void takeAction(uint16_t nAction);
	};

	inline Node *MCTS::root()
	{
		return this->pRoot.get();
	}

	inline const Node *MCTS::root() const
	{
		return this->pRoot.get();
	}

	inline Node *MCTS::current()
	{
		return this->pCurrentNode;
	}

	inline const Node *MCTS::current() const
	{
		return this->pCurrentNode;
	}
}

#endif