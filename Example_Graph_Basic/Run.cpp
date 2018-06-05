
/*
	2018.05.27
	Created by AcrylicShrimp.
*/

#include "../TinNet/TinNet/TinNet.h"
#include "../TinNet/TinNet/Cache.h"
#include "../TinNet/TinNet/Shape.h"
#include "../TinNet/TinNet/Graph/Graph.h"
#include "../TinNet/TinNet/Graph/GraphBP.h"
#include "../TinNet/TinNet/Graph/Node/BPs.h"

#include <algorithm>
#include <iostream>
#include <vector>

int32_t main()
{
	using namespace TinNet;
	using namespace TinNet::Graph;
	using namespace TinNet::Graph::Node;

	GraphBP sBP;
	{
		auto x{sBP.node<InputBP>("x", Shape{4, 2})};
		auto y{sBP.node<InputBP>("y", Shape{4})};

		auto net{sBP.node<DenseBP>("net", x, 1)};
		auto output{sBP.node<TanhBP>("output", net)};

		auto output_squeeze{sBP.node<SqueezeBP>("output_squeeze", output)};
		auto diff{sBP.node<SubtractBP>("diff", y, output_squeeze)};
		auto diff_square{sBP.node<MultiplyBP>("diff_square", diff, diff)};
		auto loss{sBP.node<ReduceMeanBP>("loss", diff_square)};
	}

	TinNet::Graph::Graph sGraph{sBP};
	sGraph.enableBackward();

	auto &x{sGraph.input("x")};
	auto &y{sGraph.input("y")};

	std::vector<float> sX
	{
		.0f, .0f,
		1.f, .0f,
		.0f, 1.f,
		1.f, 1.f
	};
	std::vector<float> sY
	{
		.0f,
		1.f,
		1.f,
		1.f
	};
	
	x = sX;
	y = sY;

	auto dense{sGraph.node<Dense>("net")};
	dense->initialize();

	for (;;)
	{
		auto output{sGraph.forward("output")};
		std::cout << "output : " << (*output)[0] << ", " << (*output)[1] << ", " << (*output)[2] << ", " << (*output)[3] << std::endl;

		std::cout << "loss : " << (*sGraph.forward("loss"))[0] << std::endl;

		sGraph.backward();
		sGraph.applyGradient(.01f);
	}

	return 0;
}