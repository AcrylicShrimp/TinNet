
/*
	2018.05.27
	Created by AcrylicShrimp.
*/

#include "../TinNet/TinNet/TinNet.h"
#include "../TinNet/TinNet/Optimizer/SGD.h"
#include "../TinNet/TinNet/Optimizer/Momentum.h"
#include "../TinNet/TinNet/Optimizer/Adam.h"

#include "../TinNet/TinNet/GraphNode/GraphOp.h"

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

#include <Windows.h>

int32_t main()
{
	using namespace TinNet;

	//std::vector<float> train_x(60000 * 784);
	//std::vector<float> train_y(60000 * 10);
	//std::vector<float> test_x(10000 * 784);
	//std::vector<float> test_y(10000 * 10);
	//
	//{
	//	std::ifstream sInput{L"D:/Develop/Dataset/MNIST/MNIST_train_in.dat", std::ifstream::binary | std::ifstream::in};
	//	sInput.read(reinterpret_cast<char *>(train_x.data()), sizeof(float) * train_x.size());
	//}
	//
	//{
	//	std::ifstream sInput{L"D:/Develop/Dataset/MNIST/MNIST_train_out.dat", std::ifstream::binary | std::ifstream::in};
	//	sInput.read(reinterpret_cast<char *>(train_y.data()), sizeof(float) * train_y.size());
	//}
	//
	//{
	//	std::ifstream sInput{L"D:/Develop/Dataset/MNIST/MNIST_test_in.dat", std::ifstream::binary | std::ifstream::in};
	//	sInput.read(reinterpret_cast<char *>(test_x.data()), sizeof(float) * test_x.size());
	//}
	//
	//{
	//	std::ifstream sInput{L"D:/Develop/Dataset/MNIST/MNIST_test_out.dat", std::ifstream::binary | std::ifstream::in};
	//	sInput.read(reinterpret_cast<char *>(test_y.data()), sizeof(float) * test_y.size());
	//}

	std::vector<float> train_x(128);
	std::vector<float> train_y(4 * 100 * 100);

	{
		std::mt19937_64 sEngine{std::random_device{}()};
		std::normal_distribution<float> sDist;

		for (auto &x : train_x)
			x = sDist(sEngine);
	}

	{
		std::ifstream sInput{L"D:/Develop/Dataset/TestImage/john_delete.dat", std::ifstream::binary | std::ifstream::in};
		sInput.read(reinterpret_cast<char *>(train_y.data()), sizeof(float) * train_y.size());
	}

	Graph graph;
	GraphBP bp{graph};

	auto &x = bp.input(Shape{1, 128, 1, 1});

	auto &layer1 = bp.transposedConvolution(x, 5, 5, 5, 5, 1024, 5, 5);
	auto &output1 = bp.relu(layer1, .01f);

	auto &layer2 = bp.transposedConvolution(output1, 5, 5, 25, 25, 512, 5, 5);
	auto &output2 = bp.relu(layer2, .01f);

	auto &layer3 = bp.transposedConvolution(output2, 5, 5, 100, 100, 4, 5, 5);
	auto &output3 = bp.sigmoid(layer3);

	auto &y = bp.input(Shape{1, 4, 100, 100});

	auto &loss = bp.reduceMean(bp.square(y - output3));

	//auto &x = bp.input(Shape{32, 784}, train_x);
	//auto &reshaped_x = bp.reshape(x, {32, 1, 28, 28});
	//auto &layer1 = bp.convolution(reshaped_x, 3, 3, 28, 28, 32);
	//auto &output1 = bp.relu(layer1, .001f);
	//
	//auto &layer2 = bp.convolution(output1, 3, 3, 14, 14, 64, 2, 2);
	//auto &output2 = bp.relu(layer2, .001f);
	//auto &reshaped_output2 = bp.reshape(output2, {32, 12544});
	//
	//auto &layer3 = bp.dense(reshaped_output2, 10);
	//auto &y_hat = bp.softmax(layer3, {false, true});
	//auto &y = bp.input(Shape{32, 10}, train_y);

	//auto &layer1 = bp.dense(x, 300);
	//auto &output1 = bp.relu(layer1, .001f);
	//
	//auto &layer2 = bp.dense(output1, 10);
	//auto &output2 = bp.relu(layer2, .001f);
	//auto &y_hat = bp.softmax(output2, {false, true});
	//auto &y = bp.input(Shape{32, 10}, train_y);
	//auto &loss = bp.reduceMean(-bp.reduceSum(y * bp.log(y_hat), {false, true}));

	graph.initialize();
	graph.enableBackward();

	//Optimizer::SGD optimizer{graph};
	//Optimizer::Momentum optimizer{graph, .9f};
	Optimizer::Adam optimizer{graph, .9f, .999f};

	//auto fAccuracyFunc = [&]()
	//{
	//	std::size_t nCount{0};
	//
	//	for (std::size_t nIndex{0}; nIndex + 32 <= 10000; )
	//	{
	//		graph.feed(
	//		{
	//			{Shape{32, 784}, Cache{test_x.data() + nIndex * 784, 784 * 32}},
	//			{Shape{32, 10}, Cache{test_y.data() + nIndex * 10, 10 * 32}}
	//		});
	//
	//		auto sYHat{y_hat.forward()};
	//
	//		for (int i = 0; i < 32; ++i, ++nIndex)
	//			if (std::distance(sYHat.cbegin() + i * 10, std::max_element(sYHat.cbegin() + i * 10, sYHat.cbegin() + (i + 1) * 10)) ==
	//				std::distance(test_y.data() + nIndex * 10, std::max_element(test_y.data() + nIndex * 10, test_y.data() + (nIndex + 1) * 10)))
	//				++nCount;
	//	}
	//
	//	std::cout << "Accuracy : " << nCount / 10000.f * 100.f << "%" << std::endl;
	//};

	std::int64_t count{0};

	auto fSaveResult = [&]()
	{
		std::ofstream sOutput{"out" + std::to_string(count++) + ".ppm", std::ofstream::out};

		sOutput << "P3\n";
		sOutput << "100 100\n";
		sOutput << "255\n";

		auto sImage{output3.forward()};

		for (int h = 0; h < 100; ++h)
			for (int w = 0; w < 100; ++w)
			{
				sOutput << static_cast<int>(sImage[h * 100 + w + 00000] * 255.f) << " ";
				sOutput << static_cast<int>(sImage[h * 100 + w + 10000] * 255.f) << " ";
				sOutput << static_cast<int>(sImage[h * 100 + w + 20000] * 255.f) << "\n";
			}
	};

	Batch batch;

	for (;;)
	{
		auto sBegin{std::chrono::system_clock::now()};

		batch.sequential(1, 1);

		graph.feed(
			batch,
			{
				{Shape{1, 128, 1, 1}, train_x},
				{Shape{1, 4, 100, 100}, train_y}
			});

		fSaveResult();
		std::cout << "Saved." << std::endl;
		std::cout << "Loss : " << loss.forward().toString() << std::endl;

		optimizer.reduce(loss, .001f);

		//fAccuracyFunc();
		//for (std::size_t nIndex{0}; nIndex + 32 <= 60000; nIndex += 32)
		//{
		//	graph.feed(
		//	{
		//		{Shape{32, 784}, Cache{train_x.data() + nIndex * 784, 784 * 32}},
		//		{Shape{32, 10}, Cache{train_y.data() + nIndex * 10, 10 * 32}}
		//	});
		//
		//	optimizer.optimize(.001f);
		//}

		auto sEnd{std::chrono::system_clock::now()};

		std::cout << "==== Time took : " << std::chrono::duration_cast<std::chrono::milliseconds>(sEnd - sBegin).count() << "ms ====" << std::endl << std::endl;
	}

	return 0;
}