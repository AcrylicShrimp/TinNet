
/*
	2018.05.27
	Created by AcrylicShrimp.
*/

#include "../TinNet/TinNet/TinNet.h"
#include "../TinNet/TinNet/Accessor.h"
#include "../TinNet/TinNet/Cache.h"
#include "../TinNet/TinNet/Shape.h"
#include "../TinNet/TinNet/Graph/Graph.h"
#include "../TinNet/TinNet/Graph/GraphBP.h"
#include "../TinNet/TinNet/Graph/Node/BPs.h"

#include <iostream>
#include <vector>

int32_t main()
{
	using namespace TinNet;
	using namespace TinNet::Graph;
	using namespace TinNet::Graph::Node;

	GraphBP sBP;
	{
		auto pLeft{sBP.node<InputBP>("input_left", Shape{3})};
		auto pRight{sBP.node<InputBP>("input_right", Shape{3, 1})};
		auto pAdd{sBP.node<AddBP>("add", pLeft, pRight)};
		auto pSubtract{sBP.node<SubtractBP>("sub", pLeft, pRight)};
	}
	
	TinNet::Graph::Graph sGraph{sBP};
	sGraph.enableBackward();
	
	auto &sLeftInput{sGraph.input("input_left")};
	auto &sRightInput{sGraph.input("input_right")};
	
	std::vector<float> sLeft{1.0f, 2.0f, 3.0f};
	std::vector<float> sRight{10.f, 20.f, 30.f};
	
	sLeftInput = sLeft;
	sRightInput = sRight;
	
	auto sResult1{sGraph.forward("add")};
	auto sResult2{sGraph.forward("sub")};
	auto sResult3{sGraph.backward("input_left")};
	auto sResult4{sGraph.backward("input_right")};

	system("pause");

	return 0;
}