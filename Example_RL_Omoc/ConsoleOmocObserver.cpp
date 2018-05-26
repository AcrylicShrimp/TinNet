
/*
	2018.03.22
	Created by AcrylicShrimp.
*/

#include "ConsoleOmocObserver.h"

namespace TinNet_Example
{
	ConsoleOmocObserver::ConsoleOmocObserver() :
		nGameCount{0ui64},
		nNondrawGameCount{0ui64},
		nBlackWinCount{0ui64},
		nWhiteWinCount{0ui64},
		nBlackErrorCount{0ui64},
		nWhiteErrorCount{0ui64}
	{
		//Empty.
	}

	void ConsoleOmocObserver::onGameBegin(const OmocBoard *pOmocBoard)
	{
		++this->nGameCount;
	}

	void ConsoleOmocObserver::onPlaced(uint32_t nPlacement, const OmocAgent *pOmocAgent, const OmocBoard *pOmocBoard)
	{

	}

	void ConsoleOmocObserver::onPlaceRejected(uint32_t nPlacement, const OmocAgent *pOmocAgent, const OmocBoard *pOmocBoard)
	{
		if (pOmocAgent->identifier() < 0)
			++this->nBlackErrorCount;
		else
			++this->nWhiteErrorCount;
	}

	void ConsoleOmocObserver::onGameEnd(const OmocGameResult *pOmocGameResult)
	{
		if (!pOmocGameResult->bDraw)
			if (pOmocGameResult->pWinner->identifier() < 0)
			{
				++this->nBlackWinCount;
				++this->nNondrawGameCount;
			}
			else
			{
				++this->nWhiteWinCount;
				++this->nNondrawGameCount;
			}

		if (this->nGameCount % 100)
			return;

		if (this->nNondrawGameCount == 0)
			printf("%llu°ÔÀÓ ³¡ - ¹«½ÂºÎ : %0.2lf%%(%llu)\n",
				this->nGameCount,
				static_cast<double>(this->nGameCount - this->nNondrawGameCount) / this->nGameCount * 100.,
				this->nGameCount - this->nNondrawGameCount);
		else
			printf("%llu°ÔÀÓ ³¡ - ¹«½ÂºÎ : %0.2lf%%(%llu), ½Â·ü(B vs W) : %0.2lf%%(%llu) vs %0.2lf%%(%llu)\n",
				this->nGameCount,
				static_cast<double>(this->nGameCount - this->nNondrawGameCount) / this->nGameCount * 100.,
				this->nGameCount - this->nNondrawGameCount,
				static_cast<double>(this->nBlackWinCount) / this->nNondrawGameCount * 100.,
				this->nBlackWinCount,
				static_cast<double>(this->nWhiteWinCount) / this->nNondrawGameCount * 100.,
				this->nWhiteWinCount);

		TinNet::Dot::Dot::display().push(static_cast<float>(this->nWhiteWinCount) / this->nNondrawGameCount * 100.f);
		printf("°ÔÀÓ´ç Æò±Õ ¿¡·¯ : %0.4llf¹ø vs %0.4llf¹ø\n", this->nBlackErrorCount / 100., this->nWhiteErrorCount / 100.);

		this->nBlackErrorCount = 0;
		this->nWhiteErrorCount = 0;

		//printf("±âº¸ :\n");
		//this->renderBoard(pOmocGameResult->nLastPlacement, pOmocGameResult->pBoard);
	}

	void ConsoleOmocObserver::renderBoard(uint32_t nLastPlacement, const OmocBoard *pOmocBoard) const
	{
		for (std::size_t nH{0}; nH < pOmocBoard->nHeight; ++nH)
		{
			printf("\t");

			for (std::size_t nW{0}; nW < pOmocBoard->nWidth; ++nW)
			{
				auto nIndex{nH * pOmocBoard->nWidth + nW};

				if (nIndex == nLastPlacement)
					printf("%c", pOmocBoard->sBoard[nIndex] == 0 ? '`' : pOmocBoard->sBoard[nIndex] < 0 ? 'X' : 'O');
				else
					printf("%c", pOmocBoard->sBoard[nIndex] == 0 ? '`' : pOmocBoard->sBoard[nIndex] < 0 ? 'b' : 'w');
			}

			printf("\n");
		}
	}
}