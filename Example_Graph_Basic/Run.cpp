
/*
	2018.05.27
	Created by AcrylicShrimp.
*/

#include "../TinNet/TinNet/Accessor.h"
#include "../TinNet/TinNet/Cache.h"
#include "../TinNet/TinNet/Iterator.h"
#include "../TinNet/TinNet/Shape.h"
#include "../TinNet/TinNet/Graph/Graph.h"
#include "../TinNet/TinNet/Graph/GraphBP.h"
#include "../TinNet/TinNet/Graph/Node/BPs.h"

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <vector>

int32_t main()
{
	using namespace TinNet;
	using namespace TinNet::Graph;
	using namespace TinNet::Graph::Node;

	std::vector<float> sTrainInput(60000u * 784u);
	std::vector<float> sTrainOutput(60000u * 10u);

	{
		std::ifstream sInput{L"D:/Develop/Dataset/MNIST/MNIST_train_in.dat", std::ifstream::binary | std::ifstream::in};
		sInput.read(reinterpret_cast<char *>(sTrainInput.data()), sizeof(float) * sTrainInput.size());
	}

	{
		std::ifstream sInput{L"D:/Develop/Dataset/MNIST/MNIST_train_out.dat", std::ifstream::binary | std::ifstream::in};
		sInput.read(reinterpret_cast<char *>(sTrainOutput.data()), sizeof(float) * sTrainOutput.size());
	}

	GraphBP sBP;
	{
		auto x{sBP.node<InputBP>("x", Shape{32, 784})};
		auto y{sBP.node<InputBP>("y", Shape{32, 10})};

		//Convolution
		auto reshape_x{sBP.node<ReshapeBP>("reshape_x", x, Shape{32, 1, 28, 28})};

		auto net1{sBP.node<ConvolutionBP>("net1", reshape_x, 3, 3, 28, 28, 32, 1, 1)};
		auto output1{sBP.node<ReLUBP>("output1", net1)};

		auto net2{sBP.node<ConvolutionBP>("net2", output1, 3, 3, 14, 14, 64, 2, 2)};
		auto output2{sBP.node<ReLUBP>("output2", net2)};

		auto reshape_output2{sBP.node<ReshapeBP>("reshape_output2", output2, Shape{32, 12544})};

		//Dense
		//auto net1{sBP.node<DenseBP>("net1", x, 300)};
		//auto output1{sBP.node<ReLUBP>("output1", net1)};
		//
		//auto net2{sBP.node<DenseBP>("net2", output1, 100)};
		//auto output2{sBP.node<ReLUBP>("output2", net2)};

		auto net3{sBP.node<DenseBP>("net3", reshape_output2, 10)};
		auto output3{sBP.node<SigmoidBP>("output3", net3)};

		auto output_squeeze{sBP.node<SqueezeBP>("output_squeeze", output3)};
		auto diff{sBP.node<SubtractBP>("diff", y, output_squeeze)};
		auto diff_square{sBP.node<MultiplyBP>("diff_square", diff, diff)};
		auto loss{sBP.node<ReduceMeanBP>("loss", diff_square)};
	}

	TinNet::Graph::Graph sGraph{sBP};
	sGraph.enableBackward();

	auto &x{sGraph.input("x")};
	auto &y{sGraph.input("y")};

	x = sTrainInput;
	y = sTrainOutput;

	auto net1{sGraph.node<Convolution>("net1")};
	auto net2{sGraph.node<Convolution>("net2")};
	auto net3{sGraph.node<Dense>("net3")};

	net1->initialize();
	net2->initialize();
	net3->initialize();

	for (;;)
	{
		auto sBegin{std::chrono::system_clock::now()};

		auto output{sGraph.forward("output3")};
		std::cout << "output : " << std::endl
			<< (*output)[0] << ", " << std::endl
			<< (*output)[1] << ", " << std::endl
			<< (*output)[2] << ", " << std::endl
			<< (*output)[3] << ", " << std::endl
			<< (*output)[4] << ", " << std::endl
			<< (*output)[5] << ", " << std::endl
			<< (*output)[6] << ", " << std::endl
			<< (*output)[7] << ", " << std::endl
			<< (*output)[8] << ", " << std::endl
			<< (*output)[9] << std::endl;

		std::cout << "loss : " << (*sGraph.forward("loss"))[0] << std::endl;

		for (int i = 0; i < 60000; i += 32)
		{
			sGraph.backward();
			sGraph.applyGradient(.001f);
		}

		auto sEnd{std::chrono::system_clock::now()};

		std::cout << "==== Time took : " << std::chrono::duration_cast<std::chrono::milliseconds>(sEnd - sBegin).count() << "ms ====" << std::endl << std::endl;
	}

	return 0;
}