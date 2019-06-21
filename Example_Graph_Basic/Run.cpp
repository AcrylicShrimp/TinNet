
/*
	2018.05.27
	Created by AcrylicShrimp.
*/

#include <TinNet/TinNet.h>

#include <cstdlib>
#include <iostream>
#include <vector>

int32_t main()
{
	using namespace TinNet;

	Core::Graph graph;

	auto x = graph.builder().input("x");
	auto y = graph.builder().input("y");
	auto w = graph.builder().parameter("w", Core::Shape{1, 2}, graph.builder().initXavier(2, 1));
	auto b = graph.builder().parameter("b", Core::Shape{1}, graph.builder().initConstant());
	auto output = graph.builder().sigmoid("output", graph.builder().dense(x, w, b));
	auto loss = graph.builder().sigmoidCE("loss", y, output);

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

	std::vector<Core::Span<float>> x_span
	{
		Core::Span<float>{x_data[0].begin(), x_data[0].end()},
		Core::Span<float>{x_data[1].begin(), x_data[1].end()},
		Core::Span<float>{x_data[2].begin(), x_data[2].end()},
		Core::Span<float>{x_data[3].begin(), x_data[3].end()}
	};
	std::vector<Core::Span<float>> y_span
	{
		Core::Span<float>{y_data[0].begin(), y_data[0].end()},
		Core::Span<float>{y_data[1].begin(), y_data[1].end()},
		Core::Span<float>{y_data[2].begin(), y_data[2].end()},
		Core::Span<float>{y_data[3].begin(), y_data[3].end()}
	};
	
	Optimizer::SGD optimizer{graph.node<Node::Parameter>("w"), graph.node<Node::Parameter>("b")};
	
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