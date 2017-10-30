
/*
	2017.10.26
	Created by AcrylicShrimp.
*/

#include "../CaysNet/CaysNet/CaysNet.h"

#include "Omoc.h"
#include "ConsoleOmocObserver.h"
#include "AIOmocAgent.h"
#include "LearningAIOmocAgent.h"

#include <cstdlib>

int main()
{
	CaysNet::NN sBlack
	{
		CaysNet::Layer::layer<CaysNet::Activation::Softmax>(100, 100)
	};

	CaysNet::NN sWhite
	{
		CaysNet::Layer::layer<CaysNet::Activation::Softmax>(101, 100)
	};

	sBlack.initBias<CaysNet::Initializer::He>();
	sBlack.initWeight<CaysNet::Initializer::He>();
	sWhite.initBias<CaysNet::Initializer::He>();
	sWhite.initWeight<CaysNet::Initializer::He>();

	Omoc sOmoc{10, 10};
	ConsoleOmocObserver sConsoleObserver;
	AIOmocAgent sAIBlack{&sBlack};
	LearningAIOmocAgent sAIWhite{&sWhite};

	sOmoc.registerObserver(&sConsoleObserver);
	sOmoc.registerAgent(&sAIBlack, &sAIWhite);

	for (int nTemp = 0;; ++nTemp)
	{
		sOmoc.playNewGame();

		if (nTemp == 5000)
		{
			nTemp = 0;
			sWhite.serialize(std::ofstream{"5moc.cn", std::ofstream::binary | std::ofstream::out});
		}
	}

	return 0;
}