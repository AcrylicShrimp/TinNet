
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
		CaysNet::Layer::FullLayer::make<CaysNet::Activation::Softmax>(25, 25)
	};

	CaysNet::NN sWhite
	{
		CaysNet::Layer::FullLayer::make<CaysNet::Activation::LReLU>(25, 50),
		CaysNet::Layer::FullLayer::make<CaysNet::Activation::LReLU>(50, 45),
		CaysNet::Layer::FullLayer::make<CaysNet::Activation::LReLU>(45, 40),
		CaysNet::Layer::FullLayer::make<CaysNet::Activation::LReLU>(40, 35),
		CaysNet::Layer::FullLayer::make<CaysNet::Activation::LReLU>(35, 30),
		CaysNet::Layer::FullLayer::make<CaysNet::Activation::Softmax>(30, 25)
	};

	sBlack.initBias<CaysNet::Initializer::Constant>(.0f);
	sBlack.initWeight<CaysNet::Initializer::He>();
	sWhite.initBias<CaysNet::Initializer::Constant>(.0f);
	sWhite.initWeight<CaysNet::Initializer::He>();

	Omoc sOmoc{5, 5};
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