
/*
	2018.03.22
	Created by AcrylicShrimp.
*/

#include "Omoc.h"

namespace TinNet_Example
{
	Omoc::Omoc(uint32_t nWidth, uint32_t nHeight, uint32_t nMaxPlacement) :
		sBoard{nWidth, nHeight, nMaxPlacement},
		pBlack{nullptr},
		pWhite{nullptr},
		pObserver{nullptr}
	{
		this->sBoard.sBoard.resize(nWidth * nHeight, 0);
	}

	OmocGameResult Omoc::playNewGame()
	{
		if (!this->pBlack || !this->pWhite)
			return {true, nullptr, nullptr, &this->sBoard, nullptr, 0};

		std::fill(this->sBoard.sBoard.begin(), this->sBoard.sBoard.end(), 0);

		if (this->pObserver)
			this->pObserver->onGameBegin(&this->sBoard);

		this->pBlack->identifier() = -1;
		this->pWhite->identifier() = 1;

		OmocGameResult sGameResult;

		while (!this->nextStep(&sGameResult));

		this->pObserver->onGameEnd(&sGameResult);
		this->pBlack->onGameEnd(&sGameResult);
		this->pWhite->onGameEnd(&sGameResult);

		return sGameResult;
	}

	bool Omoc::nextStep(OmocGameResult *pGameResult)
	{
		if (this->proceedPhase(this->pBlack, pGameResult))
			return true;

		if (this->proceedPhase(this->pWhite, pGameResult))
			return true;

		return false;
	}

	bool Omoc::proceedPhase(OmocAgent *pAgent, OmocGameResult *pGameResult)
	{
		auto nPlacement{pAgent->place(&this->sBoard)};

		while (this->sBoard.sBoard[nPlacement])
		{
			if (this->pObserver)
				this->pObserver->onPlaceRejected(nPlacement, pAgent, &this->sBoard);

			pAgent->onPlaceRejected(nPlacement, &this->sBoard);
			nPlacement = pAgent->place(&this->sBoard);
		}

		if (this->pObserver)
			this->pObserver->onPlaced(nPlacement, pAgent, &this->sBoard);

		pAgent->onPlaced(nPlacement, &this->sBoard);
		this->sBoard.sBoard[nPlacement] = pAgent->identifier();

		if (this->checkGameWinner(nPlacement, pAgent->identifier()))
		{
			pGameResult->bDraw = false;
			pGameResult->pWinner = pAgent;
			pGameResult->pLoser = pAgent == this->pBlack ? this->pWhite : this->pBlack;
			pGameResult->pBoard = &this->sBoard;
			pGameResult->pLastAgent = pAgent;
			pGameResult->nLastPlacement = nPlacement;

			return true;
		}

		for (auto nStone : this->sBoard.sBoard)
			if (!nStone)
				return false;

		pGameResult->bDraw = true;
		pGameResult->pWinner = nullptr;
		pGameResult->pLoser = nullptr;
		pGameResult->pBoard = &this->sBoard;
		pGameResult->pLastAgent = pAgent;
		pGameResult->nLastPlacement = nPlacement;

		return true;
	}

	bool Omoc::checkGameWinner(uint32_t nPlacement, int32_t nIdentifier)
	{
		uint32_t nSum{1};
		uint32_t nX{nPlacement % this->sBoard.nWidth};
		uint32_t nY{nPlacement / this->sBoard.nWidth};

		for (int x = nX - 1; x >= 0 && this->sBoard.sBoard[nY * this->sBoard.nWidth + x] == nIdentifier; --x)
			++nSum;

		for (int x = nX + 1; x < this->sBoard.nWidth && this->sBoard.sBoard[nY * this->sBoard.nWidth + x] == nIdentifier; ++x)
			++nSum;

		if (nSum == this->sBoard.nMaxPlacement)
			return true;

		nSum = 1;

		for (int y = nY - 1; y >= 0 && this->sBoard.sBoard[y * this->sBoard.nWidth + nX] == nIdentifier; --y)
			++nSum;

		for (int y = nY + 1; y < this->sBoard.nHeight && this->sBoard.sBoard[y * this->sBoard.nWidth + nX] == nIdentifier; ++y)
			++nSum;

		if (nSum == this->sBoard.nMaxPlacement)
			return true;

		nSum = 1;

		for (int x = nX - 1, y = nY - 1; x >= 0 && y >= 0 && this->sBoard.sBoard[y * this->sBoard.nWidth + x] == nIdentifier; --x, --y)
			++nSum;

		for (int x = nX + 1, y = nY + 1; x < this->sBoard.nWidth && y < this->sBoard.nHeight && this->sBoard.sBoard[y * this->sBoard.nWidth + x] == nIdentifier; ++x, ++y)
			++nSum;

		if (nSum == this->sBoard.nMaxPlacement)
			return true;

		nSum = 1;

		for (int x = nX - 1, y = nY + 1; x >= 0 && y < this->sBoard.nHeight && this->sBoard.sBoard[y * this->sBoard.nWidth + x] == nIdentifier; --x, ++y)
			++nSum;

		for (int x = nX + 1, y = nY - 1; x < this->sBoard.nWidth && y >= 0 && this->sBoard.sBoard[y * this->sBoard.nWidth + x] == nIdentifier; ++x, --y)
			++nSum;

		if (nSum == this->sBoard.nMaxPlacement)
			return true;

		return false;
	}
}