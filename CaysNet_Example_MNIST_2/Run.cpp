
/*
	2017.08.23
	Created by AcrylicShrimp.
*/

#include "../CaysNet/CaysNet/CaysNet.h"

#include <cstdio>
#include <cstdlib>
#include <vector>

int main()
{
	using namespace CaysNet;

	NN sNetwork
	{
		Layer::FullLayer::make<Activation::TanH>(2, 2)
	};

	sNetwork.initBias<Initializer::Constant>(.0f);
	sNetwork.initWeight<Initializer::Uniform>(-.5f, .5f);

	float vInput[2]
	{
		.0f, .0f
	};

	float vOutput[2]{};

	vInput[0] = 0, vInput[1] = 0;
	sNetwork.calc(vInput, vOutput);
	printf("%.2f, %.2f\n", vOutput[0], vOutput[1]);
	vInput[0] = 1, vInput[1] = 0;
	sNetwork.calc(vInput, vOutput);
	printf("%.2f, %.2f\n", vOutput[0], vOutput[1]);
	vInput[0] = 0, vInput[1] = 1;
	sNetwork.calc(vInput, vOutput);
	printf("%.2f, %.2f\n", vOutput[0], vOutput[1]);
	vInput[0] = 1, vInput[1] = 1;
	sNetwork.calc(vInput, vOutput);
	printf("%.2f, %.2f\n", vOutput[0], vOutput[1]);

	Optimizer::Supervised::Momentum sOptimizer{sNetwork, .9f, .1f};

	std::vector<std::vector<float>> sTrainInput
	{
		{.0f, .0f},
		{1.f, .0f},
		{.0f, 1.f},
		{1.f, 1.f}
	};

	std::vector<std::vector<float>> sTrainOutput
	{
		{.0f, .0f},
		{1.f, .0f},
		{1.f, .0f},
		{1.f, 1.f}
	};

	sOptimizer.train<Loss::MSE>(sTrainInput, sTrainOutput, 4, 1000);

	vInput[0] = 0, vInput[1] = 0;
	sNetwork.calc(vInput, vOutput);
	printf("%.2f, %.2f\n", vOutput[0], vOutput[1]);
	vInput[0] = 1, vInput[1] = 0;
	sNetwork.calc(vInput, vOutput);
	printf("%.2f, %.2f\n", vOutput[0], vOutput[1]);
	vInput[0] = 0, vInput[1] = 1;
	sNetwork.calc(vInput, vOutput);
	printf("%.2f, %.2f\n", vOutput[0], vOutput[1]);
	vInput[0] = 1, vInput[1] = 1;
	sNetwork.calc(vInput, vOutput);
	printf("%.2f, %.2f\n", vOutput[0], vOutput[1]);

	system("pause");
	
	return 0;
}