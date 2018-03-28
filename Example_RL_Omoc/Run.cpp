
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
#include <cfloat>
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

	TinNet::NN sWhiteValue;
	sWhiteValue.addLayer<TinNet::Layer::FullLayer>(81, 81);
	sWhiteValue.addLayer<TinNet::Layer::ReLULayer>(81);
	sWhiteValue.addLayer<TinNet::Layer::FullLayer>(81, 81);
	sWhiteValue.addLayer<TinNet::Layer::ReLULayer>(81);
	sWhiteValue.addLayer<TinNet::Layer::FullLayer>(81, 1);

	sBlack.initBias<TinNet::Initializer::Constant>(.0f);
	sBlack.initWeight<TinNet::Initializer::He>();
	sWhite.initBias<TinNet::Initializer::Constant>(.0f);
	sWhite.initWeight<TinNet::Initializer::He>();
	sWhiteValue.initBias<TinNet::Initializer::Constant>(.0f);
	sWhiteValue.initWeight<TinNet::Initializer::He>();

	TinNet::Optimizer::Adam sPolicyOptimizer{sWhite, 2048, .001f, .9f, .999f};
	TinNet::Optimizer::Adam sValueOptimizer{sWhiteValue, 2048, .001f, .9f, .999f};
	TinNet::Optimizer::PGBaseline sBaseline{sValueOptimizer, sPolicyOptimizer};

	Omoc sOmoc{9, 9};
	ConsoleOmocObserver sConsoleObserver;
	AIOmocAgent sAIBlack{&sBlack};
	LearningAIOmocAgent sAIWhite{&sWhite, sBaseline};

	sOmoc.registerObserver(&sConsoleObserver);
	sOmoc.registerAgent(&sAIBlack, &sAIWhite);

	unsigned int current;
	_controlfp_s(&current, ~(_EM_DENORMAL | _EM_ZERODIVIDE | _EM_INVALID) & (_EM_INEXACT | _EM_UNDERFLOW | _EM_OVERFLOW), _MCW_EM);

	for (int nTemp = 0;; ++nTemp)
		sOmoc.playNewGame();

	return 0;
}