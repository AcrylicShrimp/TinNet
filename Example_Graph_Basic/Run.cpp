
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

	std::vector<float> sTrainInput(32u * 784u);
	std::vector<float> sTrainOutput(32u * 10u);
	
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
	
		auto net1{sBP.node<DenseBP>("net1", x, 1000)};
		auto output1{sBP.node<ReLUBP>("output1", net1)};
	
		auto net2{sBP.node<DenseBP>("net2", output1, 500)};
		auto output2{sBP.node<ReLUBP>("output2", net2)};
	
		auto net3{sBP.node<DenseBP>("net3", output2, 300)};
		auto output3{sBP.node<ReLUBP>("output3", net3)};
	
		auto net4{sBP.node<DenseBP>("net4", output3, 250)};
		auto output4{sBP.node<ReLUBP>("output4", net4)};
	
		auto net5{sBP.node<DenseBP>("net5", output4, 100)};
		auto output5{sBP.node<ReLUBP>("output5", net5)};
	
		auto net6{sBP.node<DenseBP>("net6", output5, 50)};
		auto output6{sBP.node<ReLUBP>("output6", net6)};
	
		auto net7{sBP.node<DenseBP>("net7", output6, 10)};
		auto output7{sBP.node<SigmoidBP>("output7", net7)};
	
		auto output_squeeze{sBP.node<SqueezeBP>("output_squeeze", output7)};
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
	
	auto dense1{sGraph.node<Dense>("net1")};
	auto dense2{sGraph.node<Dense>("net2")};
	auto dense3{sGraph.node<Dense>("net3")};
	auto dense4{sGraph.node<Dense>("net4")};
	auto dense5{sGraph.node<Dense>("net5")};
	auto dense6{sGraph.node<Dense>("net6")};
	auto dense7{sGraph.node<Dense>("net7")};
	
	dense1->initialize();
	dense2->initialize();
	dense3->initialize();
	dense4->initialize();
	dense5->initialize();
	dense6->initialize();
	dense7->initialize();
	
	for (;;)
	{
		auto sBegin{std::chrono::system_clock::now()};
	
		auto output{sGraph.forward("output7")};
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
	
	//Shape shapeA{1000, 1000};
	//Shape shapeB{1000, 1000};
	//Shape shapeR{shapeA[0], shapeB[1]};
	//
	//std::vector<float> sA(shapeA.element(), .0f);
	//std::vector<float> sB(shapeB.element(), .0f);
	//std::vector<float> sR(shapeR.element(), .0f);
	//
	//Iterator<Accessor, Accessor, Accessor> iterator;
	//iterator.init(shapeR, Accessor{shapeR}, Accessor{shapeA}, Accessor{shapeB});
	//
	//auto sBegin{std::chrono::system_clock::now()};
	//
	//for (int i = 0; i < 10; ++i)
	//	GraphOp::matmulTransposedAVX(shapeA, shapeB, Cache{sA}, Cache{sB}, Cache{sR}, iterator);
	//
	//auto sEnd{std::chrono::system_clock::now()};
	//std::cout << "Time took : " << std::chrono::duration_cast<std::chrono::milliseconds>(sEnd - sBegin).count() << "ms" << std::endl;
	//
	//system("pause");
	
	return 0;
}