
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
		Layer::layer<Activation::ReLU>(784, 30),
		Layer::layer<Activation::ReLU>(30, 30),
		Layer::layer<Activation::ReLU>(30, 30),
		Layer::layer<Activation::ReLU>(30, 30),
		Layer::layer<Activation::ReLU>(30, 30),
		Layer::layer<Activation::Softmax>(30, 10)
	};

	sNetwork.initWeight<Initializer::He>();
	sNetwork.initBias<Initializer::Constant>(.0f);

	std::vector<std::vector<float>> sTrainInput(600u);
	std::vector<std::vector<float>> sTrainOutput(600u);

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

	std::vector<float> sOutput1(10);
	sNetwork.calc(sTestInput[0].data(), sOutput1.data());

	auto nLoss1 = sNetwork.loss(sTestInput[0].data(), sTestOutput[0].data());

	Optimizer::SGD<Loss::MSE> sOptimizer{sNetwork, .01f};
	sOptimizer.train(sTrainInput, sTrainOutput, 64, 100);

	std::vector<float> sOutput2(10);
	sNetwork.calc(sTestInput[0].data(), sOutput2.data());

	auto nLoss2 = sNetwork.loss(sTestInput[0].data(), sTestOutput[0].data());

	std::cout << nLoss1 << std::endl << nLoss2 << std::endl;

	system("pause");

	return 0;
}