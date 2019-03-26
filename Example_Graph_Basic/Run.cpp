
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

	registerStandardNodeType(graph.sNodeTypeManager);

	graph.createNode<Node::Input>("x");
	graph.createNode<Node::Input>("y");
	graph.createNode<Node::Parameter>("w", Core::Shape{1, 2});
	graph.createNode<Node::Parameter>("b", Core::Shape{1});
	graph.createNode<Node::MM>("xw");
	graph.createNode<Node::Add>("xw+b");
	graph.createNode<Node::Sigmoid>("output");
	graph.createNode<Node::SigmoidCrossEntropy>("loss");

	graph["xw"]["left"]->attach(&graph["x"]);
	graph["xw"]["right"]->attach(&graph["w"]);
	graph["xw+b"]["left"]->attach(&graph["xw"]);
	graph["xw+b"]["right"]->attach(&graph["b"]);
	graph["output"]["logit"]->attach(&graph["xw+b"]);
	graph["loss"]["label"]->attach(&graph["y"]);
	graph["loss"]["prob"]->attach(&graph["output"]);

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

	graph.node<Node::Parameter>("w")->initialize(Initializer::Xavier{2, 1});
	graph.node<Node::Parameter>("b")->initialize(Initializer::Constant{});

	Optimizer::SGD optimizer{graph.node<Node::Parameter>("w"), graph.node<Node::Parameter>("b")};

	for (;;)
	{
		graph.node<Node::Input>("x")->feed({x_data[0].begin(), x_data[0].end()}, {2, 1});
		graph.node<Node::Input>("y")->feed({y_data[0].begin(), y_data[0].end()}, {1});
		std::cout << "#1 Value : " << graph["output"].evalOutput().output()[0];
		std::cout << " [" << graph["loss"].evalOutput().output()[0] << "]" << std::endl;

		graph.node<Node::Input>("x")->feed({x_data[1].begin(), x_data[1].end()}, {2, 1});
		graph.node<Node::Input>("y")->feed({y_data[1].begin(), y_data[1].end()}, {1});
		std::cout << "#2 Value : " << graph["output"].evalOutput().output()[0];
		std::cout << " [" << graph["loss"].evalOutput().output()[0] << "]" << std::endl;

		graph.node<Node::Input>("x")->feed({x_data[2].begin(), x_data[2].end()}, {2, 1});
		graph.node<Node::Input>("y")->feed({y_data[2].begin(), y_data[2].end()}, {1});
		std::cout << "#3 Value : " << graph["output"].evalOutput().output()[0];
		std::cout << " [" << graph["loss"].evalOutput().output()[0] << "]" << std::endl;

		graph.node<Node::Input>("x")->feed({x_data[3].begin(), x_data[3].end()}, {2, 1});
		graph.node<Node::Input>("y")->feed({y_data[3].begin(), y_data[3].end()}, {1});
		std::cout << "#4 Value : " << graph["output"].evalOutput().output()[0];
		std::cout << " [" << graph["loss"].evalOutput().output()[0] << "]" << std::endl;

		std::cout << std::endl;

		system("pause");

		graph.node<Node::Input>("x")->feed({x_data[0].begin(), x_data[0].end()}, {2, 1});
		graph.node<Node::Input>("y")->feed({y_data[0].begin(), y_data[0].end()}, {1});
		optimizer.reduce(1.f, &graph["loss"]);

		graph.node<Node::Input>("x")->feed({x_data[1].begin(), x_data[1].end()}, {2, 1});
		graph.node<Node::Input>("y")->feed({y_data[1].begin(), y_data[1].end()}, {1});
		optimizer.reduce(1.f, &graph["loss"]);

		graph.node<Node::Input>("x")->feed({x_data[2].begin(), x_data[2].end()}, {2, 1});
		graph.node<Node::Input>("y")->feed({y_data[2].begin(), y_data[2].end()}, {1});
		optimizer.reduce(1.f, &graph["loss"]);

		graph.node<Node::Input>("x")->feed({x_data[3].begin(), x_data[3].end()}, {2, 1});
		graph.node<Node::Input>("y")->feed({y_data[3].begin(), y_data[3].end()}, {1});
		optimizer.reduce(1.f, &graph["loss"]);
	}

	return 0;
}