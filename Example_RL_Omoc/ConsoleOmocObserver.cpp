
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
		//printf("게임 시작됨\n");
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
			printf("%llu게임 끝 - 무승부 : %0.2lf%%(%llu)\n",
				   this->nGameCount,
				   static_cast<double>(this->nGameCount - this->nNondrawGameCount) / this->nGameCount * 100.,
				   this->nGameCount - this->nNondrawGameCount);
		else
			printf("%llu게임 끝 - 무승부 : %0.2lf%%(%llu), 승률(B vs W) : %0.2lf%%(%llu) vs %0.2lf%%(%llu)\n",
				   this->nGameCount,
				   static_cast<double>(this->nGameCount - this->nNondrawGameCount) / this->nGameCount * 100.,
				   this->nGameCount - this->nNondrawGameCount,
				   static_cast<double>(this->nBlackWinCount) / this->nNondrawGameCount * 100.,
				   this->nBlackWinCount,
				   static_cast<double>(this->nWhiteWinCount) / this->nNondrawGameCount * 100.,
				   this->nWhiteWinCount);

		TinNet::Dot::Dot::display().push(static_cast<float>(this->nWhiteWinCount) / this->nNondrawGameCount * 100.f);

		printf("게임당 평균 에러 : %0.4llf번 vs %0.4llf번\n", this->nBlackErrorCount / 100., this->nWhiteErrorCount / 100.);
		//printf("게임당 에러 : %llu번 vs %llu번\n", this->nBlackErrorCount, this->nWhiteErrorCount);

		this->nBlackErrorCount = 0;
		this->nWhiteErrorCount = 0;

		//printf("기보 :\n");
		//
		//for (int h = 0; h < 3; ++h)
		//{
		//	printf("\t");
		//
		//	for (int w = 0; w < 3; ++w)
		//	{
		//		if (h * 3 + w == nFinalPlace)
		//			printf("%c", pPlace[h * 3 + w] == 0 ? '`' : pPlace[h * 3 + w] < 0 ? 'X' : 'O');
		//		else
		//			printf("%c", pPlace[h * 3 + w] == 0 ? '`' : pPlace[h * 3 + w] < 0 ? 'b' : 'w');
		//	}
		//
		//	printf("\n");
		//}
	}
}