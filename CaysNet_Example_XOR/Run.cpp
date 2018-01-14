
/*
	2018.01.14
	Created by AcrylicShrimp.
*/

#include "../CaysNet/CaysNet/CaysNet.h"

#include <cstdio>
#include <cstdlib>
#include <memory>
#include <vector>

int main()
{
	CaysNet::NN sNetwork;

	sNetwork.addLayer<CaysNet::Layer::FullLayer>(2u, 2u);
	sNetwork.addLayer<CaysNet::Layer::TanhLayer>(2u);
	sNetwork.addLayer<CaysNet::Layer::FullLayer>(2u, 1u);
	sNetwork.addLayer<CaysNet::Layer::TanhLayer>(1u);

	sNetwork.initBias<CaysNet::Initializer::Constant>(.0f);
	sNetwork.initWeight<CaysNet::Initializer::Normal>();

	std::vector<std::vector<float>> sInput
	{
		std::vector<float>{.0f, .0f},
		std::vector<float>{1.f, .0f},
		std::vector<float>{.0f, 1.f},
		std::vector<float>{1.f, 1.f}
	};

	std::vector<std::vector<float>> sValidation
	{
		std::vector<float>{.0f, .0f},
		std::vector<float>{1.f, .0f},
		std::vector<float>{.0f, 1.f},
		std::vector<float>{1.f, 1.f}
	};

	sNetwork.forward(sValidation[0].data());
	printf("%lf\n", sNetwork.output().back()[0]);
	sNetwork.forward(sValidation[1].data());
	printf("%lf\n", sNetwork.output().back()[0]);
	sNetwork.forward(sValidation[2].data());
	printf("%lf\n", sNetwork.output().back()[0]);
	sNetwork.forward(sValidation[3].data());
	printf("%lf\n", sNetwork.output().back()[0]);

	CaysNet::Optimizer::Supervised::SGD sSGD{sNetwork, 4u, .001f};

	std::vector<std::vector<float>> sOutput
	{
		std::vector<float>{.0f},
		std::vector<float>{1.f},
		std::vector<float>{1.f},
		std::vector<float>{.0f}
	};

	for (;;)
	{
		sSGD.train<CaysNet::Loss::MSE>(10000u, 4u, sInput.data(), sOutput.data());

		sNetwork.forward(sValidation[0].data());
		printf("%lf\n", sNetwork.output().back()[0]);
		sNetwork.forward(sValidation[1].data());
		printf("%lf\n", sNetwork.output().back()[0]);
		sNetwork.forward(sValidation[2].data());
		printf("%lf\n", sNetwork.output().back()[0]);
		sNetwork.forward(sValidation[3].data());
		printf("%lf\n", sNetwork.output().back()[0]);

		system("pause");
	}

	return 0;
}