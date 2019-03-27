
/*
	2018.05.27
	Created by AcrylicShrimp.
*/

#include "../TinNet/TinNet/TinNet.h"

#include <cstdlib>
#include <iostream>
#include <vector>

int32_t main()
{
	using namespace TinNet;

	Core::Graph graph;

	graph.builder().input("x");
	graph.builder().input("y");
	graph.builder().parameter("w", Core::Shape{1, 2}, graph.builder().initXavier(2, 1));
	graph.builder().parameter("b", Core::Shape{1}, graph.builder().initConstant());
	graph.builder().sigmoid("output", graph.builder().mm(graph["x"], graph["w"]) + graph["b"]);
	graph.builder().sigmoidCE("loss", graph["y"], graph["output"]);
	
	std::vector<std::vector<float>> x_data
	{
		{.0f, .0f},
		{1.f, .0f},
		{.0f, 1.f},
		{1.f, 1.f}
	};
	std::vector<std::vector<float>> y_data
	{
		{.0f},
		{1.f},
		{1.f},
		{1.f}
	};
	
	Optimizer::SGD optimizer{graph.node<Node::Parameter>("w"), graph.node<Node::Parameter>("b")};
	
	for (;;)
	{
		graph.node<Node::Input>("x")->feed({x_data[0].begin(), x_data[0].end()}, Core::Shape{2, 1});
		graph.node<Node::Input>("y")->feed({y_data[0].begin(), y_data[0].end()}, Core::Shape{1});
		std::cout << "#1 Value : " << graph["output"].evalOutput().output()[0];
		std::cout << " [" << graph["loss"].evalOutput().output()[0] << "]" << std::endl;
	
		graph.node<Node::Input>("x")->feed({x_data[1].begin(), x_data[1].end()}, Core::Shape{2, 1});
		graph.node<Node::Input>("y")->feed({y_data[1].begin(), y_data[1].end()}, Core::Shape{1});
		std::cout << "#2 Value : " << graph["output"].evalOutput().output()[0];
		std::cout << " [" << graph["loss"].evalOutput().output()[0] << "]" << std::endl;
	
		graph.node<Node::Input>("x")->feed({x_data[2].begin(), x_data[2].end()}, Core::Shape{2, 1});
		graph.node<Node::Input>("y")->feed({y_data[2].begin(), y_data[2].end()}, Core::Shape{1});
		std::cout << "#3 Value : " << graph["output"].evalOutput().output()[0];
		std::cout << " [" << graph["loss"].evalOutput().output()[0] << "]" << std::endl;
	
		graph.node<Node::Input>("x")->feed({x_data[3].begin(), x_data[3].end()}, Core::Shape{2, 1});
		graph.node<Node::Input>("y")->feed({y_data[3].begin(), y_data[3].end()}, Core::Shape{1});
		std::cout << "#4 Value : " << graph["output"].evalOutput().output()[0];
		std::cout << " [" << graph["loss"].evalOutput().output()[0] << "]" << std::endl;
	
		std::cout << std::endl;
	
		system("pause");
	
		graph.node<Node::Input>("x")->feed({x_data[0].begin(), x_data[0].end()}, Core::Shape{2, 1});
		graph.node<Node::Input>("y")->feed({y_data[0].begin(), y_data[0].end()}, Core::Shape{1});
		optimizer.reduce(1.f, graph["loss"]);
	
		graph.node<Node::Input>("x")->feed({x_data[1].begin(), x_data[1].end()}, Core::Shape{2, 1});
		graph.node<Node::Input>("y")->feed({y_data[1].begin(), y_data[1].end()}, Core::Shape{1});
		optimizer.reduce(1.f, graph["loss"]);
	
		graph.node<Node::Input>("x")->feed({x_data[2].begin(), x_data[2].end()}, Core::Shape{2, 1});
		graph.node<Node::Input>("y")->feed({y_data[2].begin(), y_data[2].end()}, Core::Shape{1});
		optimizer.reduce(1.f, graph["loss"]);
	
		graph.node<Node::Input>("x")->feed({x_data[3].begin(), x_data[3].end()}, Core::Shape{2, 1});
		graph.node<Node::Input>("y")->feed({y_data[3].begin(), y_data[3].end()}, Core::Shape{1});
		optimizer.reduce(1.f, graph["loss"]);
	}

	return 0;
}