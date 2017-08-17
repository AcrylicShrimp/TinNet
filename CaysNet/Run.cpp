
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

	NN<Loss::MulticlassCE> sNetwork;

	for (std::string sCommand;;)
	{
		std::cout << "command : ";
		std::cin >> sCommand;

		if (sCommand == "read")
		{
			std::ifstream sInput{"network.cn", std::ifstream::binary | std::ifstream::in};

			if (!sInput.is_open())
			{
				std::cout << "Cannot open." << std::endl << std::endl;

				continue;
			}

			sNetwork.deserialize(sInput);

			std::cout << "Successfully loaded." << std::endl;
			std::cout << "Number of the layers : " << sNetwork.layer().size() << std::endl;
			std::cout << "For each layer :" << std::endl;

			std::size_t nCount{0};

			for (const auto &sLayer : sNetwork.layer())
			{
				std::cout << "\tSummary of the Layer No. " << ++nCount << " :" << std::endl;
				std::cout << "\tFan in : " << sLayer.fanIn() << std::endl;
				std::cout << "\tFan out : " << sLayer.fanOut() << std::endl;
				std::cout << "\tActivation : ";
				std::wcout << sLayer.activation()->name();
				std::cout << std::endl << std::endl;
			}

			break;
		}
		else if (sCommand == "new")
		{
			sNetwork.addLayer(Layer::layer<Activation::LReLU>(784, 300));
			sNetwork.addLayer(Layer::layer<Activation::LReLU>(300, 100));
			sNetwork.addLayer(Layer::layer<Activation::LReLU>(100, 50));
			sNetwork.addLayer(Layer::layer<Activation::LReLU>(50, 45));
			sNetwork.addLayer(Layer::layer<Activation::LReLU>(45, 30));
			sNetwork.addLayer(Layer::layer<Activation::LReLU>(30, 20));
			sNetwork.addLayer(Layer::layer<Activation::LReLU>(20, 10));
			sNetwork.addLayer(Layer::layer<Activation::Softmax>(10, 10));

			std::cout << "Successfully created." << std::endl;
			std::cout << "Number of the layers : " << sNetwork.layer().size() << std::endl;
			std::cout << "For each layer :" << std::endl;

			std::size_t nCount{0};

			for (const auto &sLayer : sNetwork.layer())
			{
				std::cout << "\tSummary of the Layer No. " << ++nCount << " :" << std::endl;
				std::cout << "\tFan in : " << sLayer.fanIn() << std::endl;
				std::cout << "\tFan out : " << sLayer.fanOut() << std::endl;
				std::cout << "\tActivation : ";
				std::wcout << sLayer.activation()->name();
				std::cout << std::endl << std::endl;
			}

			sNetwork.initWeight<Initializer::He>();
			sNetwork.initBias<Initializer::Constant>(.0f);

			std::cout << "Network initialized." << std::endl;

			break;
		}
		else if (sCommand == "exit")
		{
			std::cout << "Bye" << std::endl;

			return 0;
		}
		else
			std::cout << "Wrong command." << std::endl << std::endl;
	}

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
	Optimizer::SGD<Loss::MulticlassCE> sOptimizer{sNetwork, .001f};

	for (;;)
	{
		printf("Validation data classification loss : %f\n", sNetwork.classificationLoss(sTestInput, sTestOutput));

		std::cout << "Serializing network...";
		sNetwork.serialize(std::ofstream{"network.cn", std::ofstream::binary | std::ofstream::out});
		std::cout << " saved." << std::endl;

		//printf("Training data loss : %f\n", sNetwork.loss(sTrainInput, sTrainOutput));
		//printf("Validation data loss : %f\n", sNetwork.loss(sTestInput, sTestOutput));
		//printf("Training data classification loss : %f\n", sNetwork.classificationLoss(sTrainInput, sTrainOutput));

		//sNetwork.calc(sTestInput[0].data(), sOutput.data());

		//CaysNet::Visualizer::ConsoleVisualizer::clear();
		//CaysNet::Visualizer::ConsoleVisualizer::visualize(sOutput.data());

		/*for (std::size_t nIndex{0}; nIndex < 10; ++nIndex)
		{
			sNetwork.calc(sTestInput[nIndex].data(), sOutput.data());

			printf("%0.2lf, %0.2lf, %0.2lf, %0.2lf, %0.2lf, %0.2lf, %0.2lf, %0.2lf, %0.2lf, %0.2lf\n",
				sOutput[0], sOutput[1], sOutput[2], sOutput[3], sOutput[4],
				sOutput[5], sOutput[6], sOutput[7], sOutput[8], sOutput[9]);

			printf("%0.2lf, %0.2lf, %0.2lf, %0.2lf, %0.2lf, %0.2lf, %0.2lf, %0.2lf, %0.2lf, %0.2lf\n\n",
				sTestOutput[nIndex][0], sTestOutput[nIndex][1], sTestOutput[nIndex][2], sTestOutput[nIndex][3], sTestOutput[nIndex][4],
				sTestOutput[nIndex][5], sTestOutput[nIndex][6], sTestOutput[nIndex][7], sTestOutput[nIndex][8], sTestOutput[nIndex][9]);
		}*/

		sOptimizer.train(sTrainInput, sTrainOutput, 32, 1);
	}

	system("pause");

	return 0;
}