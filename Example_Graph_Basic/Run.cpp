
/*
	2018.05.27
	Created by AcrylicShrimp.
*/

#include "../TinNet/TinNet/Cache.h"
#include "../TinNet/TinNet/Shape.h"
#include "../TinNet/TinNet/ShapedCache.h"
#include "../TinNet/TinNet/Graph.h"
#include "../TinNet/TinNet/GraphBP.h"
#include "../TinNet/TinNet/GraphBPOp.h"

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

	auto &op = bp.constant(Shape{2}, {2.f, 4.f}) ^ bp.constant(Shape{2}, {4.f, 2.f});

	graph.initialize();
	graph.enableBackward();

	auto forward = op.forward();

	return 0;
}