
/*
2018.06.24
Created by AcrylicShrimp.
*/

#include "../TinNet/TinNet/TinNet.h"

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

void loadDataset(const std::string &sPath, std::vector<float> &sResult)
{
	std::ifstream{sPath, std::ifstream::binary | std::ifstream::in}.read(reinterpret_cast<char *>(sResult.data()), sizeof(float) * sResult.size());
}

int32_t main()
{
	using namespace TinNet;

	std::vector<float> train_x(60000 * 784);
	std::vector<float> train_y(60000 * 10);
	std::vector<float> test_x(10000 * 784);
	std::vector<float> test_y(10000 * 10);

	loadDataset("D:/Develop/Dataset/MNIST/MNIST_train_in.dat", train_x);
	loadDataset("D:/Develop/Dataset/MNIST/MNIST_train_out.dat", train_y);
	loadDataset("D:/Develop/Dataset/MNIST/MNIST_test_in.dat", test_x);
	loadDataset("D:/Develop/Dataset/MNIST/MNIST_test_out.dat", test_y);

	Graph graph;
	GraphBP bp{graph};

	auto &x = bp.input(Shape{32, 784});
	auto &reshaped_x = bp.reshape(x, {32, 1, 28, 28});

	auto &layer1 = bp.convolution(reshaped_x, 3, 3, 28, 28, 32);
	auto &output1 = bp.relu(layer1, .001f);
	
	auto &layer2 = bp.convolution(output1, 3, 3, 14, 14, 64, 2, 2);
	auto &output2 = bp.relu(layer2, .001f);
	auto &reshaped_output2 = bp.reshape(output2, {32, 12544});
	
	auto &layer3 = bp.dense(reshaped_output2, 10);
	auto &y_hat = bp.softmax(layer3, {false, true});
	auto &y = bp.input(Shape{32, 10});

	auto &loss = bp.reduceMean(-bp.reduceSum(y * bp.log(y_hat), {false, true}));

	graph.initialize();
	graph.enableBackward();

	Optimizer::Adam optimizer{graph, .9f, .999f};

	auto fAccuracyFunc = [&]()
	{
		std::size_t nCount{0};

		for (std::size_t nIndex{0}; nIndex + 32 <= 10000; )
		{
			graph.feed(
			{
				{Shape{32, 784}, Cache{test_x.data() + nIndex * 784, 784 * 32}},
				{Shape{32, 10}, Cache{test_y.data() + nIndex * 10, 10 * 32}}
			});

			auto sYHat{y_hat.forward()};

			for (int i = 0; i < 32; ++i, ++nIndex)
				if (std::distance(sYHat.cbegin() + i * 10, std::max_element(sYHat.cbegin() + i * 10, sYHat.cbegin() + (i + 1) * 10)) ==
					std::distance(test_y.data() + nIndex * 10, std::max_element(test_y.data() + nIndex * 10, test_y.data() + (nIndex + 1) * 10)))
					++nCount;
		}

		std::cout << "Accuracy : " << nCount / 10000.f * 100.f << "%" << std::endl;
	};

	for (;;)
	{
		auto sBegin{std::chrono::system_clock::now()};

		fAccuracyFunc();

		for (std::size_t nIndex{0}; nIndex + 32 <= 60000; nIndex += 32)
		{
			graph.feed(
			{
				{Shape{32, 784}, Cache{train_x.data() + nIndex * 784, 784 * 32}},
				{Shape{32, 10}, Cache{train_y.data() + nIndex * 10, 10 * 32}}
			});

			optimizer.reduce(loss, .001f);
		}

		auto sEnd{std::chrono::system_clock::now()};

		std::cout << "==== Time took : " << std::chrono::duration_cast<std::chrono::milliseconds>(sEnd - sBegin).count() << "ms ====" << std::endl << std::endl;
	}

	return 0;
}