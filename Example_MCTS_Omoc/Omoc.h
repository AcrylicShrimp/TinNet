
/*
	2018.03.19
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_EXAMPLE_OMOC_H

#define _CLASS_TINNET_EXAMPLE_OMOC_H

#include "../TinNet/TinNet/Reinforcement/Game.h"

#include <cstdint>
#include <cstdio>
#include <memory>
#include <tuple>
#include <utility>
#include <vector>

namespace TinNet_Example
{
	class OmocState final : public TinNet::Reinforcement::State
	{
	public:
		int8_t nNextPlayer;
		std::vector<int8_t> sBoard;
		TinNet::Reinforcement::Game *pGame;

	public:
		OmocState(int8_t nNextPlayer, TinNet::Reinforcement::Game *pGame);
		OmocState(const OmocState &sSrc);
		~OmocState() = default;

	public:
		OmocState &operator=(const OmocState &sSrc) = delete;

	public:
		virtual TinNet::Reinforcement::Game *game() override;
		virtual const TinNet::Reinforcement::Game *game() const override;
	};

	class Omoc final : public TinNet::Reinforcement::Game
	{
	public:
		Omoc() = default;
		Omoc(const Omoc &sSrc) = delete;
		~Omoc() = default;

	public:
		Omoc &operator=(const Omoc &sSrc) = delete;

	public:
		virtual uint64_t maxVisit() const override;
		virtual std::unique_ptr<TinNet::Reinforcement::State> initState() override;
		virtual std::vector<uint16_t> obtainValidActionList(const TinNet::Reinforcement::State *pState) const override;
		virtual std::unique_ptr<TinNet::Reinforcement::State> duplicateState(const TinNet::Reinforcement::State *pState) const override;
		virtual void applyAction(TinNet::Reinforcement::State *pState, uint16_t nAction) const override;
		virtual std::tuple<bool, int32_t, int32_t> obtainResult(const TinNet::Reinforcement::State *pState, uint16_t nAction) const override;
		bool checkWinner(std::vector<int8_t> sBoard, uint16_t nAction, int8_t nPlayer) const;
		bool checkDraw(std::vector<int8_t> sBoard) const;
		void renderState(const TinNet::Reinforcement::State *pState);
	};
}

#endif