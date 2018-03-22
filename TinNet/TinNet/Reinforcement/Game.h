
/*
	2018.03.19
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_REINFORCEMENT_GAME_H

#define _CLASS_TINNET_REINFORCEMENT_GAME_H

#include "../TinNetDLL.h"

#include <cstdint>
#include <memory>
#include <tuple>
#include <vector>

namespace TinNet::Reinforcement
{
	class Game;

	class TINNET_DLL State
	{
	public:
		State() = default;
		State(const State &sSrc) = default;
		virtual ~State() = default;

	public:
		State &operator=(const State &sSrc) = default;

	public:
		virtual Game *game() = 0;
		virtual const Game *game() const = 0;
	};

	class TINNET_DLL Game
	{
	public:
		Game() = default;
		Game(const Game &sSrc) = default;
		virtual ~Game() = default;
		
	public:
		Game &operator=(const Game &sSrc) = default;
		
	public:
		virtual uint64_t maxVisit() const = 0;
		virtual std::unique_ptr<State> initState() = 0;
		virtual std::vector<uint16_t> obtainValidActionList(const State *pState) const = 0;
		virtual std::unique_ptr<State> duplicateState(const State *pState) const = 0;
		virtual void applyAction(State *pState, uint16_t nAction) const = 0;
		virtual std::tuple<bool, int32_t, int32_t> obtainResult(const State *pState, uint16_t nAction) const = 0;
	};
}

#endif