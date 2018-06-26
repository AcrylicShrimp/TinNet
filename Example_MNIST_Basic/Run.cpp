
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

	auto &x = bp.input({32, 784});

	auto &layer1 = bp.dense(x, 300);
	auto &output1 = bp.relu(layer1, .001f);

	auto &layer2 = bp.dense(output1, 10);
	auto &y_hat = bp.softmax(layer2, {false, true});
	auto &y = bp.input({32, 10});

	auto &loss = bp.reduceMean(-bp.reduceSum(y * bp.log(y_hat), {false, true}));

	graph.initialize();
	graph.enableBackward();

	Batch batch;
	Optimizer::Adam optimizer{graph, .9f, .999f};

	auto fAccuracyFunc = [&]()
	{
		std::size_t nIndex{0};
		std::size_t nCount{0};

		batch.shuffle(10000, 32);

		while (batch.hasNext())
		{
			graph.feed(batch,
			{
				{{batch.currentBatchSize(), 784}, test_x},
				{{batch.currentBatchSize(), 10}, test_y}
			});

			auto sYHat{y_hat.forward()};

			for (int i = 0; i < batch.currentBatchSize(); ++i, ++nIndex)
			{
				auto sY{batch.obtain(10, test_y, nIndex)};

				if (std::distance(sYHat.cbegin() + i * 10, std::max_element(sYHat.cbegin() + i * 10, sYHat.cbegin() + (i + 1) * 10)) ==
					std::distance(sY.cbegin(), std::max_element(sY.cbegin(), sY.cend())))
					++nCount;
			}

			batch.next();
		}

		std::cout << "Accuracy : " << nCount / 10000.f * 100.f << "%" << std::endl;
	};

	for (;;)
	{
		auto sBegin{std::chrono::system_clock::now()};

		fAccuracyFunc();

		batch.shuffle(60000, 32);

		while (batch.hasNext())
		{
			graph.feed(batch,
			{
				{{batch.currentBatchSize(), 784}, train_x},
				{{batch.currentBatchSize(), 10}, train_y}
			});

			batch.next();
			optimizer.reduce(loss, .001f);
		}

		auto sEnd{std::chrono::system_clock::now()};

		std::cout << "==== Time took : " << std::chrono::duration_cast<std::chrono::milliseconds>(sEnd - sBegin).count() << "ms ====" << std::endl << std::endl;
	}

	return 0;
}