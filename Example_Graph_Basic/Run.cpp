
/*
	2018.05.27
	Created by AcrylicShrimp.
*/

#include <TinNet/TinNet.h>

#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

std::int32_t main()
{
	std::vector<float> train_x(60000 * 784);
	std::vector<float> train_y(60000 * 10);
	std::vector<float> test_x(10000 * 784);
	std::vector<float> test_y(10000 * 10);

	{
		std::ifstream sInput{L"training_input.dat", std::ifstream::binary | std::ifstream::in};
		sInput.read(reinterpret_cast<char *>(train_x.data()), sizeof(float) * train_x.size());
	}

	{
		std::ifstream sInput{L"training_label.dat", std::ifstream::binary | std::ifstream::in};
		sInput.read(reinterpret_cast<char *>(train_y.data()), sizeof(float) * train_y.size());
	}

	{
		std::ifstream sInput{L"testing_input.dat", std::ifstream::binary | std::ifstream::in};
		sInput.read(reinterpret_cast<char *>(test_x.data()), sizeof(float) * test_x.size());
	}

	{
		std::ifstream sInput{L"testing_label.dat", std::ifstream::binary | std::ifstream::in};
		sInput.read(reinterpret_cast<char *>(test_y.data()), sizeof(float) * test_y.size());
	}

	using namespace TinNet;

	Core::Graph graph;

	auto x = graph.builder().input("x");
	auto y = graph.builder().input("y");

	auto w1 = graph.builder().parameter("w1", Core::Shape{300, 764}, graph.builder().initXavier(764, 300));
	auto b1 = graph.builder().parameter("b1", Core::Shape{300}, graph.builder().initConstant());
	auto o1 = graph.builder().relu(graph.builder().dense(x, w1, b1));

	auto w2 = graph.builder().parameter("w2", Core::Shape{10, 300}, graph.builder().initXavier(10, 300));
	auto b2 = graph.builder().parameter("b2", Core::Shape{10}, graph.builder().initConstant());
	auto o2 = graph.builder().softmax(graph.builder().dense(o1, w2, b2), {false, true});

	auto loss = graph.builder().mean(-graph.builder().sum(y * graph.builder().log(o2), true, {false, true}), true);

	Optimizer::SGD optimizer
	{
		graph.node<Node::Parameter>("w1"),
		graph.node<Node::Parameter>("b1"),
		graph.node<Node::Parameter>("w2"),
		graph.node<Node::Parameter>("b2")
	};
	
	for (;;)
	{
		graph.feed({
			{"x", Core::Shape{2, 1}, x_span[0]},
			{"y", Core::Shape{1}, y_span[0]}
		});
		std::cout << "#1 Value : " << output.evalOutput().output()[0];
		std::cout << " [" << loss.evalOutput().output()[0] << "]" << std::endl;
	
		graph.feed({
			{"x", Core::Shape{2, 1}, x_span[1]},
			{"y", Core::Shape{1}, y_span[1]}
		});
		std::cout << "#2 Value : " << output.evalOutput().output()[0];
		std::cout << " [" << loss.evalOutput().output()[0] << "]" << std::endl;
	
		graph.feed({
			{"x", Core::Shape{2, 1}, x_span[2]},
			{"y", Core::Shape{1}, y_span[2]}
		});
		std::cout << "#3 Value : " << output.evalOutput().output()[0];
		std::cout << " [" << loss.evalOutput().output()[0] << "]" << std::endl;
	
		graph.feed({
			{"x", Core::Shape{2, 1}, x_span[3]},
			{"y", Core::Shape{1}, y_span[3]}
		});
		std::cout << "#4 Value : " << output.evalOutput().output()[0];
		std::cout << " [" << loss.evalOutput().output()[0] << "]" << std::endl;
	
		std::cout << std::endl;
	
		system("pause");
	
		graph.feed({
			{"x", Core::Shape{2, 1}, x_span[0]},
			{"y", Core::Shape{1}, y_span[0]}
		});
		optimizer.reduce(1.f, loss);
	
		graph.feed({
			{"x", Core::Shape{2, 1}, x_span[1]},
			{"y", Core::Shape{1}, y_span[1]}
		});
		optimizer.reduce(1.f, loss);
	
		graph.feed({
			{"x", Core::Shape{2, 1}, x_span[2]},
			{"y", Core::Shape{1}, y_span[2]}
		});
		optimizer.reduce(1.f, loss);
	
		graph.feed({
			{"x", Core::Shape{2, 1}, x_span[3]},
			{"y", Core::Shape{1}, y_span[3]}
		});
		optimizer.reduce(1.f, loss);
	}

	return 0;
}