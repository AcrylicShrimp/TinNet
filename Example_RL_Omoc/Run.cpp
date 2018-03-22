
/*
	2018.03.22
	Created by AcrylicShrimp.
*/

#include "../TinNet/TinNet/TinNet.h"
#include "../TinNet_Dot/TinNet/TinNet_Dot.h"

#include "Omoc.h"
#include "ConsoleOmocObserver.h"
#include "AIOmocAgent.h"
#include "LearningAIOmocAgent.h"

#include <cstdlib>
#include <thread>

int main()
{
	using namespace TinNet_Example;

	TinNet::Dot::Dot::createWindow();

	TinNet::NN sBlack;
	sBlack.addLayer<TinNet::Layer::FullLayer>(81, 81);
	sBlack.addLayer<TinNet::Layer::SoftmaxLayer>(81);

	TinNet::NN sWhite;
	sWhite.addLayer<TinNet::Layer::FullLayer>(81, 81);
	sWhite.addLayer<TinNet::Layer::ReLULayer>(81);
	sWhite.addLayer<TinNet::Layer::FullLayer>(81, 81);
	sWhite.addLayer<TinNet::Layer::ReLULayer>(81);
	sWhite.addLayer<TinNet::Layer::FullLayer>(81, 81);
	sWhite.addLayer<TinNet::Layer::SoftmaxLayer>(81);

	sBlack.initBias<TinNet::Initializer::Constant>(.0f);
	sBlack.initWeight<TinNet::Initializer::He>();
	sWhite.initBias<TinNet::Initializer::Constant>(.0f);
	sWhite.initWeight<TinNet::Initializer::He>();

	//TinNet::Optimizer::SGD sOptimizer{sWhite, 2048, .001f};
	TinNet::Optimizer::Adam sOptimizer{sWhite, 2048, .001f, .9f, .999f};
	TinNet::Optimizer::MonteCarloPolicyGradient sMCPL{sOptimizer};

	Omoc sOmoc{9, 9};
	ConsoleOmocObserver sConsoleObserver;
	AIOmocAgent sAIBlack{&sBlack};
	LearningAIOmocAgent sAIWhite{&sWhite, sMCPL};

	sOmoc.registerObserver(&sConsoleObserver);
	sOmoc.registerAgent(&sAIBlack, &sAIWhite);

	for (int nTemp = 0;; ++nTemp)
		sOmoc.playNewGame();

	return 0;
}