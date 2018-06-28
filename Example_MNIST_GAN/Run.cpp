
/*
	2018.06.27
	Created by AcrylicShrimp.
*/

#include "../TinNet/TinNet/TinNet.h"

#include <algorithm>
#include <chrono>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void loadDataset(const std::string &sPath, std::vector<float> &sResult)
{
	std::ifstream{sPath, std::ifstream::binary | std::ifstream::in}.read(reinterpret_cast<char *>(sResult.data()), sizeof(float) * sResult.size());
}

void fillNoise(std::vector<float> &sDestination)
{
	std::mt19937_64 sEngine{std::random_device{}()};
	std::uniform_real_distribution<float> sDist{-1.f, 1.f};

	for (auto &nValue : sDestination)
		nValue = sDist(sEngine);
}

void saveOutput(const TinNet::Cache sImage)
{
	using namespace std::literals;

	static std::int64_t nCount{0};

	std::ofstream sOutput{"result"s + std::to_string(nCount++) + ".ppm"s, std::ofstream::out};

	sOutput << "P3\n";
	sOutput << "224 112\n";
	sOutput << "255\n";

	for (int ih = 0; ih < 4; ++ih)
		for (int h = 0; h < 28; ++h)
			for (int iw = 0; iw < 8; ++iw)
				for (int w = 0; w < 28; ++w)
				{
					auto nPixel{255 - static_cast<int>(sImage[ih * 8 * 28 * 28 + iw * 28 * 28 + h * 28 + w] * 255.f)};

					sOutput << nPixel << " ";
					sOutput << nPixel << " ";
					sOutput << nPixel << "\n";
				}
}

int32_t main()
{
	using namespace TinNet;

	std::vector<float> batch_z(32 * 100);
	std::vector<float> batch_x(32 * 784);
	std::vector<float> train_x(60000 * 784);

	loadDataset("D:/Develop/Dataset/MNIST/MNIST_train_in.dat", train_x);

	Graph graph;
	GraphBP bp{graph};

	auto &z = bp.input({32, 100});
	auto &x = bp.input({32, 784});

	auto &gen_hidden1 = bp.dense(z, 128);
	auto &gen_hidden2 = bp.relu(gen_hidden1, .01f);
	auto &gen_hidden3 = bp.dense(gen_hidden2, 784);
	auto &generator = bp.sigmoid(gen_hidden3);

	auto &real_dis_hidden1 = bp.dense(x, 128);
	auto &real_dis_hidden2 = bp.relu(real_dis_hidden1, .01f);
	auto &real_dis_hidden3 = bp.dense(real_dis_hidden2, 1);
	auto &real_discriminator = bp.sigmoid(real_dis_hidden3);

	auto &fake_dis_hidden1 = bp.dense(real_dis_hidden1, generator, 128);
	auto &fake_dis_hidden2 = bp.relu(fake_dis_hidden1, .01f);
	auto &fake_dis_hidden3 = bp.dense(real_dis_hidden3, fake_dis_hidden2, 1);
	auto &fake_discriminator = bp.sigmoid(fake_dis_hidden3);

	auto &loss_discriminator = -bp.reduceMean(bp.log(real_discriminator) + bp.log(1 - fake_discriminator));
	auto &loss_generator = -bp.reduceMean(bp.log(fake_discriminator));

	graph.initialize();
	graph.enableBackward();

	Batch batch;
	Optimizer::Adam generatorOpt{graph, .9f, .999f, {&gen_hidden1, &gen_hidden3}};
	Optimizer::Adam discriminatorOpt{graph, .9f, .999f, {&real_dis_hidden1, &real_dis_hidden3}};

	graph.feed(z, {{32, 100}, batch_z});
	graph.feed(x, {{32, 784}, batch_x});

	for (std::uint64_t nCount{0};;)
	{
		auto sBegin{std::chrono::system_clock::now()};

		for (batch.shuffle(60000, 32); batch.hasNext(); batch.next())
		{
			fillNoise(batch_z);
			batch.copy(784, train_x, batch_x);
			graph.endFeed();

			if (nCount++ == 500)
			{
				nCount = 0;

				std::cout << "Discriminator loss : " << loss_discriminator.forward().toString() << std::endl;
				std::cout << "Generator loss : " << loss_generator.forward().toString() << std::endl;
			}

			discriminatorOpt.reduce(loss_discriminator, .0005f);
			generatorOpt.reduce(loss_generator, .0005f);
		}

		fillNoise(batch_z);
		graph.endFeed();

		saveOutput(generator.forward());

		auto sEnd{std::chrono::system_clock::now()};

		std::cout << "==== Time took : " << std::chrono::duration_cast<std::chrono::milliseconds>(sEnd - sBegin).count() << "ms ====" << std::endl << std::endl;
	}

	return 0;
}