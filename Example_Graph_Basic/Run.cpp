
/*
	2018.05.27
	Created by AcrylicShrimp.
*/

#include "../TinNet/TinNet/TinNet.h"

#include <cstdlib>
#include <iostream>
#include <random>
#include <vector>

int32_t main()
{
	using namespace TinNet;

	Node::Input x{"x"};
	Node::Input y{"y"};
	Node::Input w{"w"};
	Node::Input b{"b"};
	Node::MM xw{"xw"};
	Node::Add xw_b{"xw+b"};
	Node::Sigmoid output{"output"};
	Node::SigmoidCrossEntropy loss{"loss"};

	xw["left"]->attach(&x);
	xw["right"]->attach(&w);
	xw_b["left"]->attach(&xw);
	xw_b["right"]->attach(&b);
	output["logit"]->attach(&xw_b);
	loss["label"]->attach(&y);
	loss["prob"]->attach(&output);

	std::mt19937_64 sEngine{std::random_device{}()};
	std::normal_distribution<float> sDist{.0f, .01f};

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
	std::vector<float> w_data
	{
		sDist(sEngine),
		sDist(sEngine)
	};
	std::vector<float> b_data
	{
		0
	};

	for (;;)
	{
		w.feed({w_data.begin(), w_data.end()}, {1, 2});
		b.feed({b_data.begin(), b_data.end()}, {1});

		x.feed({x_data[0].begin(), x_data[0].end()}, {2, 1});
		y.feed({y_data[0].begin(), y_data[0].end()}, {1});
		std::cout << "#1 Value : " << output.evalOutput().output()[0];
		std::cout << " [" << loss.evalOutput().output()[0] << "]" << std::endl;

		x.feed({x_data[1].begin(), x_data[1].end()}, {2, 1});
		y.feed({y_data[1].begin(), y_data[1].end()}, {1});
		std::cout << "#2 Value : " << output.evalOutput().output()[0];
		std::cout << " [" << loss.evalOutput().output()[0] << "]" << std::endl;

		x.feed({x_data[2].begin(), x_data[2].end()}, {2, 1});
		y.feed({y_data[2].begin(), y_data[2].end()}, {1});
		std::cout << "#3 Value : " << output.evalOutput().output()[0];
		std::cout << " [" << loss.evalOutput().output()[0] << "]" << std::endl;

		x.feed({x_data[3].begin(), x_data[3].end()}, {2, 1});
		y.feed({y_data[3].begin(), y_data[3].end()}, {1});
		std::cout << "#4 Value : " << output.evalOutput().output()[0];
		std::cout << " [" << loss.evalOutput().output()[0] << "]" << std::endl;

		std::cout << std::endl;

		system("pause");

		x.feed({x_data[0].begin(), x_data[0].end()}, {2, 1});
		y.feed({y_data[0].begin(), y_data[0].end()}, {1});
		Core::Span{w_data.begin(), w_data.end()}.accumulateFrom(-.01f, w.evalGradient(&loss).gradient());
		Core::Span{b_data.begin(), b_data.end()}.accumulateFrom(-.01f, b.evalGradient(&loss).gradient());

		x.feed({x_data[1].begin(), x_data[1].end()}, {2, 1});
		y.feed({y_data[1].begin(), y_data[1].end()}, {1});
		Core::Span{w_data.begin(), w_data.end()}.accumulateFrom(-.01f, w.evalGradient(&loss).gradient());
		Core::Span{b_data.begin(), b_data.end()}.accumulateFrom(-.01f, b.evalGradient(&loss).gradient());

		x.feed({x_data[2].begin(), x_data[2].end()}, {2, 1});
		y.feed({y_data[2].begin(), y_data[2].end()}, {1});
		Core::Span{w_data.begin(), w_data.end()}.accumulateFrom(-.01f, w.evalGradient(&loss).gradient());
		Core::Span{b_data.begin(), b_data.end()}.accumulateFrom(-.01f, b.evalGradient(&loss).gradient());

		x.feed({x_data[3].begin(), x_data[3].end()}, {2, 1});
		y.feed({y_data[3].begin(), y_data[3].end()}, {1});
		Core::Span{w_data.begin(), w_data.end()}.accumulateFrom(-.01f, w.evalGradient(&loss).gradient());
		Core::Span{b_data.begin(), b_data.end()}.accumulateFrom(-.01f, b.evalGradient(&loss).gradient());
	}

	return 0;
}