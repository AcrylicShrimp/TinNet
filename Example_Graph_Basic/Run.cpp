
/*
	2018.05.27
	Created by AcrylicShrimp.
*/

#include "../TinNet/TinNet/TinNet.h"

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <vector>

int32_t main()
{
	using namespace TinNet;

	std::vector<float> train_x(60000 * 784);
	std::vector<float> train_y(60000 * 10);
	std::vector<float> test_x(10000 * 784);
	std::vector<float> test_y(10000 * 10);

	{
		std::ifstream sInput{L"D:/Develop/Dataset/MNIST/MNIST_train_in.dat", std::ifstream::binary | std::ifstream::in};
		sInput.read(reinterpret_cast<char *>(train_x.data()), sizeof(float) * train_x.size());
	}

	{
		std::ifstream sInput{L"D:/Develop/Dataset/MNIST/MNIST_train_out.dat", std::ifstream::binary | std::ifstream::in};
		sInput.read(reinterpret_cast<char *>(train_y.data()), sizeof(float) * train_y.size());
	}

	{
		std::ifstream sInput{L"D:/Develop/Dataset/MNIST/MNIST_test_in.dat", std::ifstream::binary | std::ifstream::in};
		sInput.read(reinterpret_cast<char *>(test_x.data()), sizeof(float) * test_x.size());
	}

	{
		std::ifstream sInput{L"D:/Develop/Dataset/MNIST/MNIST_test_out.dat", std::ifstream::binary | std::ifstream::in};
		sInput.read(reinterpret_cast<char *>(test_y.data()), sizeof(float) * test_y.size());
	}

	Graph graph;
	GraphBP bp{graph};

	auto &x = bp.input(Shape{32, 1, 28, 28}, train_x);

	auto &layer1 = bp.convolution(x, 3, 3, 28, 28, 32);
	auto &output1 = bp.relu(layer1, .001f);
	
	auto &layer2 = bp.convolution(output1, 3, 3, 14, 14, 64, 2, 2);
	auto &output2 = bp.relu(layer2, .001f);
	auto &reshaped_output2 = bp.reshape(output2, {32, 12544});
	
	auto &layer3 = bp.dense(reshaped_output2, 10);
	auto &y_hat = bp.softmax(layer3, {false, true});
	auto &y = bp.input(Shape{32, 10}, train_y);

	//auto &layer1 = bp.dense(x, 300);
	//auto &output1 = bp.relu(layer1, .001f);
	//
	//auto &layer2 = bp.dense(output1, 100);
	//auto &output2 = bp.relu(layer2, .001f);
	//
	//auto &layer3 = bp.dense(output2, 10);
	//auto &y_hat = bp.softmax(layer3, {false, true});
	//auto &y = bp.input(Shape{32, 10}, train_y);

	auto &loss = bp.reduceMean(-bp.reduceSum(y * bp.log(y_hat), {false, true}));

	graph.initialize();
	graph.enableBackward();

	auto fAccuracyFunc = [&]()
	{
		std::size_t nCount{0};

		for (std::size_t nIndex{0}; nIndex + 32 <= 10000; )
		{
			graph.feed(
			{
				{Shape{32, 1, 28, 28}, Cache{test_x.data() + nIndex * 784, 784 * 32}},
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

		for (std::size_t nIndex{0}; nIndex + 32 <= 60000; nIndex += 32)
		{
			fAccuracyFunc();

			graph.feed(
			{
				{Shape{32, 1, 28, 28}, Cache{train_x.data() + nIndex * 784, 784 * 32}},
				{Shape{32, 10}, Cache{train_y.data() + nIndex * 10, 10 * 32}}
			});

			graph.computeGradient();
			graph.applyGradient(-.001f);
		}

		auto sEnd{std::chrono::system_clock::now()};

		std::cout << "==== Time took : " << std::chrono::duration_cast<std::chrono::milliseconds>(sEnd - sBegin).count() << "ms ====" << std::endl << std::endl;
	}

	return 0;
}