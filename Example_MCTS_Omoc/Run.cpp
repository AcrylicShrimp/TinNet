
/*
	2018.03.19
	Created by AcrylicShrimp.
*/

#include "../TinNet/TinNet/Reinforcement/Game.h"
#include "../TinNet/TinNet/Reinforcement/MCTS.h"
#include "Omoc.h"

#include <cstdio>
#include <random>

int main()
{
	using namespace TinNet::Reinforcement;
	using namespace TinNet_Example;

	Omoc sOmoc;
	MCTS sMCTS{&sOmoc};

	sMCTS.reset();

	int16_t nLastAction;

	for (;;)
	{
		for (auto nIndex{0}; nIndex < 25000; ++nIndex)
			sMCTS.update(Player::First);

		sMCTS.takeAction(nLastAction = sMCTS.computeBestAction(Player::First));
		sOmoc.renderState(sMCTS.current()->state());

		if (sOmoc.checkWinner(static_cast<const OmocState *>(sMCTS.current()->state())->sBoard, nLastAction, 1))
		{
			printf("MCTS 1 Win.\n");
			printf("X : %d / Y : %d", nLastAction % 9, nLastAction / 9);
			sMCTS.reset();


			system("timeout -t 1");
			continue;
		}
		else if (sOmoc.checkDraw(static_cast<const OmocState *>(sMCTS.current()->state())->sBoard))
		{
			printf("Draw.\n");
			printf("X : %d / Y : %d", nLastAction % 9, nLastAction / 9);
			sMCTS.reset();

			system("timeout -t 1");
			continue;
		}

		for (auto nIndex{0}; nIndex < 25000; ++nIndex)
			sMCTS.update(Player::Second);

		sMCTS.takeAction(nLastAction = sMCTS.computeBestAction(Player::Second));
		sOmoc.renderState(sMCTS.current()->state());

		if (sOmoc.checkWinner(static_cast<const OmocState *>(sMCTS.current()->state())->sBoard, nLastAction, -1))
		{
			printf("MCTS 2 Win.\n");
			printf("X : %d / Y : %d", nLastAction % 9, nLastAction / 9);
			sMCTS.reset();

			system("timeout -t 1");
			continue;
		}
		else if (sOmoc.checkDraw(static_cast<const OmocState *>(sMCTS.current()->state())->sBoard))
		{
			printf("Draw.\n");
			printf("X : %d / Y : %d", nLastAction % 9, nLastAction / 9);
			sMCTS.reset();

			system("timeout -t 1");
			continue;
		}
	}

	return 0;
}