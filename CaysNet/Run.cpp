
/*
	2017.08.05
	Created by AcrylicShrimp.
*/

#include "CaysNet.h"

#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>

int32_t main()
{
	using namespace CaysNet;

	NN<Loss::MSE> sNetwork
	{
		Layer::layer<Activation::Linear>(784, 10),
		Layer::layer<Activation::Linear>(10, 10),
		Layer::layer<Activation::Linear>(10, 10)
	};

	sNetwork.initWeight<Initializer::He>();
	sNetwork.initBias<Initializer::Constant>(.0f);

	std::vector<std::vector<float>> sTrainInput(60000u);
	std::vector<std::vector<float>> sTrainOutput(60000u);

	{
		std::ifstream sInput{L"D:/Develop/MNIST/MNIST_train_in.dat", std::ifstream::binary | std::ifstream::in};
		for (auto &sInVec : sTrainInput)
		{
			sInVec.resize(784u);
			sInput.read(reinterpret_cast<char *>(sInVec.data()), sizeof(float) * 784u);
		}
	}

	{
		std::ifstream sInput{L"D:/Develop/MNIST/MNIST_train_out.dat", std::ifstream::binary | std::ifstream::in};
		for (auto &sInVec : sTrainOutput)
		{
			sInVec.resize(10u);
			sInput.read(reinterpret_cast<char *>(sInVec.data()), sizeof(float) * 10u);
		}
	}

	std::vector<std::vector<float>> sTestInput(10000u);
	std::vector<std::vector<float>> sTestOutput(10000u);

	{
		std::ifstream sInput{L"D:/Develop/MNIST/MNIST_test_in.dat", std::ifstream::binary | std::ifstream::in};
		for (auto &sInVec : sTestInput)
		{
			sInVec.resize(784u);
			sInput.read(reinterpret_cast<char *>(sInVec.data()), sizeof(float) * 784u);
		}
	}

	{
		std::ifstream sInput{L"D:/Develop/MNIST/MNIST_test_out.dat", std::ifstream::binary | std::ifstream::in};
		for (auto &sInVec : sTestOutput)
		{
			sInVec.resize(10u);
			sInput.read(reinterpret_cast<char *>(sInVec.data()), sizeof(float) * 10u);
		}
	}

	std::vector<float> sOutput(10, .0f);
	Optimizer::SGD<Loss::MSE> sOptimizer{sNetwork, .0001f};

	auto sPair{sOptimizer.calcNumericalGradient(sTestInput[0], sTestOutput[0], 2, 0, 0)};
	printf("Check gradients : %f	vs	%f\n", sPair.first, sPair.second);
	sPair = sOptimizer.calcNumericalGradient(sTestInput[0], sTestOutput[0], 2, 1, 0);
	printf("Check gradients : %f	vs	%f\n", sPair.first, sPair.second);
	sPair = sOptimizer.calcNumericalGradient(sTestInput[0], sTestOutput[0], 2, 2, 0);
	printf("Check gradients : %f	vs	%f\n", sPair.first, sPair.second);
	sPair = sOptimizer.calcNumericalGradient(sTestInput[0], sTestOutput[0], 2, 3, 0);
	printf("Check gradients : %f	vs	%f\n", sPair.first, sPair.second);
	sPair = sOptimizer.calcNumericalGradient(sTestInput[0], sTestOutput[0], 2, 4, 0);
	printf("Check gradients : %f	vs	%f\n", sPair.first, sPair.second);
	sPair = sOptimizer.calcNumericalGradient(sTestInput[0], sTestOutput[0], 2, 5, 0);
	printf("Check gradients : %f	vs	%f\n", sPair.first, sPair.second);
	sPair = sOptimizer.calcNumericalGradient(sTestInput[0], sTestOutput[0], 2, 6, 0);
	printf("Check gradients : %f	vs	%f\n", sPair.first, sPair.second);
	sPair = sOptimizer.calcNumericalGradient(sTestInput[0], sTestOutput[0], 2, 7, 0);
	printf("Check gradients : %f	vs	%f\n", sPair.first, sPair.second);
	sPair = sOptimizer.calcNumericalGradient(sTestInput[0], sTestOutput[0], 2, 8, 0);
	printf("Check gradients : %f	vs	%f\n", sPair.first, sPair.second);
	sPair = sOptimizer.calcNumericalGradient(sTestInput[0], sTestOutput[0], 2, 9, 0);
	printf("Check gradients : %f	vs	%f\n", sPair.first, sPair.second);
	sPair = sOptimizer.calcNumericalGradient(sTestInput[0], sTestOutput[0], 0, 243, 0);
	printf("Check gradients : %f	vs	%f\n", sPair.first, sPair.second);

	/*for (;;)
	{
		printf("Training data loss : %f\n", sNetwork.loss(sTrainInput, sTrainOutput));
		printf("Validation data loss : %f\n", sNetwork.loss(sTestInput, sTestOutput));

		for (std::size_t nIndex{0}; nIndex < 10; ++nIndex)
		{
			sNetwork.calc(sTestInput[nIndex].data(), sOutput.data());
			
			printf("%0.2lf, %0.2lf, %0.2lf, %0.2lf, %0.2lf, %0.2lf, %0.2lf, %0.2lf, %0.2lf, %0.2lf\n",
				sOutput[0], sOutput[1], sOutput[2], sOutput[3], sOutput[4],
				sOutput[5], sOutput[6], sOutput[7], sOutput[8], sOutput[9]);

			printf("%0.2lf, %0.2lf, %0.2lf, %0.2lf, %0.2lf, %0.2lf, %0.2lf, %0.2lf, %0.2lf, %0.2lf\n\n",
				sTestOutput[nIndex][0], sTestOutput[nIndex][1], sTestOutput[nIndex][2], sTestOutput[nIndex][3], sTestOutput[nIndex][4],
				sTestOutput[nIndex][5], sTestOutput[nIndex][6], sTestOutput[nIndex][7], sTestOutput[nIndex][8], sTestOutput[nIndex][9]);
		}

		sOptimizer.train(sTrainInput, sTrainOutput, 32, 10);
	}*/

	system("pause");

	return 0;
}