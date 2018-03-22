
/*
	2018.03.19
	Created by AcrylicShrimp.
*/

#include "Omoc.h"

namespace TinNet_Example
{
	OmocState::OmocState(int8_t nNextPlayer, TinNet::Reinforcement::Game *pGame) :
		nNextPlayer{nNextPlayer},
		sBoard(9 * 9, 0),
		pGame{pGame}
	{
		//Empty.
	}

	OmocState::OmocState(const OmocState &sSrc) :
		nNextPlayer{sSrc.nNextPlayer},
		sBoard{sSrc.sBoard},
		pGame{sSrc.pGame}
	{
		//Empty.
	}

	TinNet::Reinforcement::Game *OmocState::game()
	{
		return this->pGame;
	}

	const TinNet::Reinforcement::Game *OmocState::game() const
	{
		return this->pGame;
	}

	uint64_t Omoc::maxVisit() const
	{
		return 40;
	}

	std::unique_ptr<TinNet::Reinforcement::State> Omoc::initState()
	{
		return std::unique_ptr<TinNet::Reinforcement::State>(new OmocState(1, this));
	}

	std::vector<uint16_t> Omoc::obtainValidActionList(const TinNet::Reinforcement::State *pState) const
	{
		auto pOmocState{static_cast<const OmocState *>(pState)};
		std::vector<uint16_t> sActionList;
		sActionList.reserve(9 * 9);

		for (uint16_t nIndex{0}, nSize{9 * 9}; nIndex < nSize; ++nIndex)
			if (!pOmocState->sBoard[nIndex])
				sActionList.emplace_back(nIndex);

		return sActionList;
	}

	std::unique_ptr<TinNet::Reinforcement::State> Omoc::duplicateState(const TinNet::Reinforcement::State *pState) const
	{
		return std::unique_ptr<TinNet::Reinforcement::State>(new OmocState(*static_cast<const OmocState *>(pState)));
	}

	void Omoc::applyAction(TinNet::Reinforcement::State *pState, uint16_t nAction) const
	{
		auto pOmocState{static_cast<OmocState *>(pState)};
		pOmocState->sBoard[nAction] = pOmocState->nNextPlayer;
		pOmocState->nNextPlayer = -pOmocState->nNextPlayer;
	}

	std::tuple<bool, int32_t, int32_t> Omoc::obtainResult(const TinNet::Reinforcement::State *pState, uint16_t nAction) const
	{
		auto pOmocState{static_cast<const OmocState *>(pState)};

		if (this->checkWinner(pOmocState->sBoard, nAction, 1))
			return std::make_tuple(true, 1, 0);
		else if (this->checkWinner(pOmocState->sBoard, nAction, -1))
			return std::make_tuple(true, 0, 1);
		else if (this->checkDraw(pOmocState->sBoard))
			return std::make_tuple(true, 0, 0);

		return std::make_tuple(false, 0, 0);
	}

	bool Omoc::checkWinner(std::vector<int8_t> sBoard, uint16_t nAction, int8_t nPlayer) const
	{
		int nSum{1};
		int nX{nAction % 9};
		int nY{nAction / 9};

		for (int x = nX - 1; x >= 0 && sBoard[nY * 9 + x] == nPlayer; --x)
			++nSum;

		for (int x = nX + 1; x < 9 && sBoard[nY * 9 + x] == nPlayer; ++x)
			++nSum;

		if (nSum == 5)
			return true;

		nSum = 1;

		for (int y = nY - 1; y >= 0 && sBoard[y * 9 + nX] == nPlayer; --y)
			++nSum;

		for (int y = nY + 1; y < 9 && sBoard[y * 9 + nX] == nPlayer; ++y)
			++nSum;

		if (nSum == 5)
			return true;

		nSum = 1;

		for (int x = nX - 1, y = nY - 1; x >= 0 && y >= 0 && sBoard[y * 9 + x] == nPlayer; --x, --y)
			++nSum;

		for (int x = nX + 1, y = nY + 1; x < 9 && y < 9 && sBoard[y * 9 + x] == nPlayer; ++x, ++y)
			++nSum;

		if (nSum == 5)
			return true;

		nSum = 1;

		for (int x = nX - 1, y = nY + 1; x >= 0 && y < 9 && sBoard[y * 9 + x] == nPlayer; --x, ++y)
			++nSum;

		for (int x = nX + 1, y = nY - 1; x < 9 && y >= 0 && sBoard[y * 9 + x] == nPlayer; ++x, --y)
			++nSum;

		if (nSum == 5)
			return true;

		return false;
	}

	bool Omoc::checkDraw(std::vector<int8_t> sBoard) const
	{
		for (auto nStone : sBoard)
			if (!nStone)
				return false;

		return true;
	}

	void Omoc::renderState(const TinNet::Reinforcement::State *pState)
	{
		auto pOmocState{static_cast<const OmocState *>(pState)};

		system("cls");

		for (auto nY{0}; nY < 9; ++nY)
		{
			for (auto nX{0}; nX < 9; ++nX)
				if (pOmocState->sBoard[nY * 9 + nX] < 0)
					printf("¡Ü");
				else if (pOmocState->sBoard[nY * 9 + nX] > 0)
					printf("¡Û");
				else
					printf("¡¡");

			puts("");
		}
	}
}