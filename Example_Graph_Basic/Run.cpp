
/*
	2018.05.27
	Created by AcrylicShrimp.
*/

#include <TinNet/TinNet.h>

#include <algorithm>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <random>
#include <utility>
#include <vector>

std::int32_t main()
{
	std::vector<float> train_x(60000 * 784);
	std::vector<float> train_y(60000 * 10);
	std::vector<float> test_x(10000 * 784);
	std::vector<float> test_y(10000 * 10);

	{
		std::ifstream sInput{L"train_input.dat", std::ifstream::binary | std::ifstream::in};
		sInput.read(reinterpret_cast<char *>(train_x.data()), sizeof(float) * train_x.size());
	}

	{
		std::ifstream sInput{L"train_label.dat", std::ifstream::binary | std::ifstream::in};
		sInput.read(reinterpret_cast<char *>(train_y.data()), sizeof(float) * train_y.size());
	}

	{
		std::ifstream sInput{L"test_input.dat", std::ifstream::binary | std::ifstream::in};
		sInput.read(reinterpret_cast<char *>(test_x.data()), sizeof(float) * test_x.size());
	}

	{
		std::ifstream sInput{L"test_label.dat", std::ifstream::binary | std::ifstream::in};
		sInput.read(reinterpret_cast<char *>(test_y.data()), sizeof(float) * test_y.size());
	}

	using namespace TinNet;

	Core::Graph graph;

	auto x = graph.builder().input("x");
	auto y = graph.builder().input("y");

	auto w1 = graph.builder().parameter("w1", Core::Shape{300, 784}, graph.builder().initXavier(0, 784, 300));
	auto b1 = graph.builder().parameter("b1", Core::Shape{300}, graph.builder().initConstant());
	auto a1 = graph.builder().dense(x, w1, b1);
	auto o1 = graph.builder().relu(a1, .001f);

	auto w2 = graph.builder().parameter("w2", Core::Shape{10, 300}, graph.builder().initXavier(0, 300, 10));
	auto b2 = graph.builder().parameter("b2", Core::Shape{10}, graph.builder().initConstant());
	auto a2 = graph.builder().dense(o1, w2, b2);
	auto o2 = graph.builder().softmax(a2, {true, false});

	auto loss = graph.builder().softmaxCE(y, o2);

	Optimizer::Momentum optimizer
	//Optimizer::SGD optimizer
	{
		.9f,
		{
			graph.node<Node::Parameter>("w1"),
			graph.node<Node::Parameter>("b1"),
			graph.node<Node::Parameter>("w2"),
			graph.node<Node::Parameter>("b2")
		}
	};
	
	std::mt19937_64 sEngine{std::random_device{}()};
	std::vector<std::size_t> sShuffledIndexList;

	for (std::size_t nIndex{0}; nIndex < 60000; ++nIndex)
		sShuffledIndexList.emplace_back(nIndex);

	for (;;)
	{
		auto sBegin{std::chrono::system_clock::now()};

		graph.feed(
			{
				{"x", Core::Shape{784, 60000}, Core::Span<float>{train_x.begin(), train_x.end()}},
				{"y", Core::Shape{10, 60000}, Core::Span<float>{train_y.begin(), train_y.end()}}
			});

		std::cout << "Training Loss: " << loss.evalOutput().output()[0] << std::endl;

		graph.feed(
			{
				{"x", Core::Shape{784, 10000}, Core::Span<float>{test_x.begin(), test_x.end()}},
				{"y", Core::Shape{10, 10000}, Core::Span<float>{test_y.begin(), test_y.end()}}
			});
		
		std::cout << "Test Loss: " << loss.evalOutput().output()[0] << std::endl;

		for (std::size_t nIndex{1}; nIndex < 60000; ++nIndex)
			std::swap(sShuffledIndexList[nIndex - 1], sShuffledIndexList[std::uniform_int_distribution<std::size_t>{nIndex, 60000 - 1}(sEngine)]);

		for (std::size_t nIndex{0}; nIndex + 32 <= 60000; nIndex += 32)
		{
			std::size_t nActualBatchSize{std::min<std::size_t>(60000 - nIndex, 32)};

			graph.feed(
				{
					{"x", Core::Shape{784, nActualBatchSize}, Core::Span<float>{train_x.data() + nIndex * 784, nActualBatchSize * 784}},
					{"y", Core::Shape{10, nActualBatchSize}, Core::Span<float>{train_y.data() + nIndex * 10, nActualBatchSize * 10}}
				});

			auto g = o1.evalOutput().output();

			optimizer.reduce(.001f, loss);
		}

		auto sEnd{std::chrono::system_clock::now()};

		std::cout << "==== Time took : " << std::chrono::duration_cast<std::chrono::milliseconds>(sEnd - sBegin).count() << "ms ====" << std::endl << std::endl;
	}

	return 0;
}