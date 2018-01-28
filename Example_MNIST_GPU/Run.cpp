
/*
	2018.01.19
	Created by AcrylicShrimp.
*/

#include "../TinNet/TinNet/TinNet.h"
#include "../TinNet_GPU/TinNet/TinNet_GPU.h"

#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>

int32_t main()
{
	using namespace TinNet;

	initTinNetGPU();

	NN_GPU sNetwork;

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

			//sNetwork.deserialize(sInput);

			std::cout << "Successfully loaded." << std::endl;
			std::cout << "Number of the layers : " << sNetwork.layer().size() << std::endl;
			std::cout << "For each layer :" << std::endl;

			std::size_t nCount{0};

			for (const auto &pLayer : sNetwork.layer())
			{
				std::cout << "\tSummary of the Layer No. " << ++nCount << " :" << std::endl;
				std::cout << "\tLayer type : " << pLayer->name() << std::endl;
				std::cout << "\tFan in : " << pLayer->fanIn() << std::endl;
				std::cout << "\tFan out : " << pLayer->fanOut() << std::endl;
				std::cout << std::endl << std::endl;
			}

			break;
		}
		else if (sCommand == "new")
		{
			sNetwork.addLayer<Layer::ConvLayer_GPU>(28, 28, 1, 30, 5, 5, 1, 1, 24, 24);
			sNetwork.addLayer<Layer::LReLULayer_GPU>(17280);
			sNetwork.addLayer<Layer::ConvLayer_GPU>(24, 24, 30, 60, 4, 4, 2, 2, 11, 11);
			sNetwork.addLayer<Layer::LReLULayer_GPU>(7260);
			sNetwork.addLayer<Layer::FullLayer_GPU>(7260, 100);
			sNetwork.addLayer<Layer::LReLULayer_GPU>(100);
			sNetwork.addLayer<Layer::FullLayer_GPU>(100, 10);
			//sNetwork.addLayer<Layer::SoftmaxLayer_GPU>(10);

			std::cout << "Successfully created." << std::endl;
			std::cout << "Number of the layers : " << sNetwork.layer().size() << std::endl;
			std::cout << "For each layer :" << std::endl;

			std::size_t nCount{0};

			for (const auto &pLayer : sNetwork.layer())
			{
				std::cout << "\tSummary of the Layer No. " << ++nCount << " :" << std::endl;
				std::cout << "\tLayer type : " << pLayer->name() << std::endl;
				std::cout << "\tFan in : " << pLayer->fanIn() << std::endl;
				std::cout << "\tFan out : " << pLayer->fanOut() << std::endl;
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
		std::ifstream sInput{L"D:/Develop/Dataset/MNIST/MNIST_train_in.dat", std::ifstream::binary | std::ifstream::in};
		for (auto &sInVec : sTrainInput)
		{
			sInVec.resize(784u);
			sInput.read(reinterpret_cast<char *>(sInVec.data()), sizeof(float) * 784u);
		}
	}

	{
		std::ifstream sInput{L"D:/Develop/Dataset/MNIST/MNIST_train_out.dat", std::ifstream::binary | std::ifstream::in};
		for (auto &sInVec : sTrainOutput)
		{
			sInVec.resize(10u);
			sInput.read(reinterpret_cast<char *>(sInVec.data()), sizeof(float) * 10u);
		}
	}

	std::vector<std::vector<float>> sTestInput(10000u);
	std::vector<std::vector<float>> sTestOutput(10000u);

	{
		std::ifstream sInput{L"D:/Develop/Dataset/MNIST/MNIST_test_in.dat", std::ifstream::binary | std::ifstream::in};
		for (auto &sInVec : sTestInput)
		{
			sInVec.resize(784u);
			sInput.read(reinterpret_cast<char *>(sInVec.data()), sizeof(float) * 784u);
		}
	}

	{
		std::ifstream sInput{L"D:/Develop/Dataset/MNIST/MNIST_test_out.dat", std::ifstream::binary | std::ifstream::in};
		for (auto &sInVec : sTestOutput)
		{
			sInVec.resize(10u);
			sInput.read(reinterpret_cast<char *>(sInVec.data()), sizeof(float) * 10u);
		}
	}

	Optimizer::Supervised::SGD_GPU sOptimizer{sNetwork, 32u, .001f};
	//Optimizer::Supervised::SGD sOptimizer{sNetwork, 32u, .1f};
	//Optimizer::Supervised::Momentum sOptimizer{sNetwork, 32, .9f, .005f};
	//Optimizer::Supervised::NAG sOptimizer{sNetwork, .9f, .001f};
	//Optimizer::Supervised::Adagrad sOptimizer{sNetwork, 32, .005f};
	//Optimizer::Supervised::RMSProp sOptimizer{sNetwork, 32, .9f, .001f};
	//Optimizer::Supervised::Adam sOptimizer{sNetwork, 32, .001f, .9f, .999f};

	sOptimizer.addTrainingSet(60000u, sTrainInput.data(), sTrainOutput.data());

	Visualizer::CSVLossExporter sExporter;

	//std::cout << "Serializing network...";
	//sNetwork.serialize(std::ofstream{"network.cn", std::ofstream::binary | std::ofstream::out});
	//std::cout << " saved." << std::endl;

	float vOutput[10];

	for (;;)
	{
		sNetwork.forward(sTestInput[0].data(), vOutput);

		printf("%.2lf %.2lf %.2lf %.2lf %.2lf %.2lf %.2lf %.2lf %.2lf %.2lf\n",
			   vOutput[0], vOutput[1], vOutput[2], vOutput[3], vOutput[4],
			   vOutput[5], vOutput[6], vOutput[7], vOutput[8], vOutput[9]);

		//float nLoss{sNetwork.classificationLoss(10000u, sTestInput.data(), sTestOutput.data())};
		//printf("Validation data classification accuracy : %0.2f%%\n", (1.f - nLoss) * 100.f);

		sExporter.accrueLoss(.0f);
		sExporter.exportCSV(std::ofstream{"losses.csv", std::ofstream::out});

		sOptimizer.train<Loss::MulticlassCE_GPU>(1);
		printf("trained!\n");

		//std::cout << "Serializing network...";
		//sNetwork.serialize(std::ofstream{"network.cn", std::ofstream::binary | std::ofstream::out});
		//std::cout << " saved." << std::endl;
	}

	system("pause");

	finTinNetGPU();

	return 0;
}