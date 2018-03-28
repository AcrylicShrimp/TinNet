
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

	void ConsoleOmocObserver::handleGameStart()
	{
		//printf("°ÔÀÓ ½ÃÀÛµÊ\n");
	}

	void ConsoleOmocObserver::handleGameEnd(const float *pPlace, int nWinner, int nFinalPlace, int nErrorBlack, int nErrorWhite)
	{
		++this->nGameCount;
		this->nBlackErrorCount += nErrorBlack;
		this->nWhiteErrorCount += nErrorWhite;

		if (nWinner < 0)
		{
			++this->nBlackWinCount;
			++this->nNondrawGameCount;
		}
		else if (nWinner > 0)
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

		printf("±âº¸ :\n");
		
		for (int h = 0; h < 9; ++h)
		{
			printf("\t");
		
			for (int w = 0; w < 9; ++w)
			{
				if (h * 9 + w == nFinalPlace)
					printf("%c", pPlace[h * 9 + w] == 0 ? '`' : pPlace[h * 9 + w] < 0 ? 'X' : 'O');
				else
					printf("%c", pPlace[h * 9 + w] == 0 ? '`' : pPlace[h * 9 + w] < 0 ? 'b' : 'w');
			}
		
			printf("\n");
		}
	}
}