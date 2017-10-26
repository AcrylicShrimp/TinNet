
/*
	2017.10.26
	Created by AcrylicShrimp.
*/

#include "ConsoleOmocObserver.h"

ConsoleOmocObserver::ConsoleOmocObserver() :
	nGameCount{0ui64},
	nNondrawGameCount{0ui64},
	nBlackWinCount{0ui64},
	nWhiteWinCount{0ui64}
{
	//Empty.
}

void ConsoleOmocObserver::handleGameStart()
{
	printf("°ÔÀÓ ½ÃÀÛµÊ\n");
}

void ConsoleOmocObserver::handleGameEnd(const float *pPlace, int nWinner, int nFinalPlace)
{
	++this->nGameCount;

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

	printf("±âº¸ :\n");

	for (int h = 0; h < 10; ++h)
	{
		printf("\t");

		for (int w = 0; w < 10; ++w)
		{
			if (h * 10 + w == nFinalPlace)
				printf("%c", pPlace[h * 10 + w] == 0 ? '`' : pPlace[h * 10 + w] < 0 ? 'X' : 'O');
			else
				printf("%c", pPlace[h * 10 + w] == 0 ? '`' : pPlace[h * 10 + w] < 0 ? 'b' : 'w');
		}

		printf("\n");
	}
}