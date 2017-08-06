
/*
	2017.08.05
	Created by AcrylicShrimp.
*/

#include "CaysNet.h"

#include <cstdint>
#include <fstream>
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

	std::vector<float> sOutput(10);
	sNetwork.calc(sTrainInput[0].data(), sOutput.data());

	auto nLoss = sNetwork.loss(sTestInput[0].data(), sTestOutput[0].data());

	Optimizer::SGD<Loss::MSE> sOptimizer{sNetwork, .01f};
	sOptimizer.train(sTrainInput, sTrainOutput, 64, 1);

	nLoss = sNetwork.loss(sTestInput[0].data(), sTestOutput[0].data());

	return 0;
}