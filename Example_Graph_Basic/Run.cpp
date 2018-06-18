
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
	using namespace TinNet::GraphNode;

	Graph graph;
	GraphBP bp{graph};

	auto &op = bp.softPlus(bp.constant(Shape{10, 1}, {-1.f, 2.f, -3.f, 4.f, -5.f, 6.f, -7.f, 8.f, -9.f, 10.f}));

	graph.initialize();
	graph.enableBackward();

	auto forward = op.forward();
	auto backward = graph.node("constant0")->backward();

	return 0;
}