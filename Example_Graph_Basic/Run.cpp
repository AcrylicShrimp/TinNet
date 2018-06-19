
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



	graph.initialize();
	graph.enableBackward();

	for (;;)
	{
		graph.feed(
		{
			{Shape{4, 2}, in_x},
			{Shape{4, 1}, in_y}
		});

		std::cout << "Output : " << y_hat.forward().toString() << std::endl;
		std::cout << "Loss : " << loss.forward().toString() << std::endl;

		graph.computeGradient();
		graph.applyGradient(-.001f);
	}

	return 0;
}