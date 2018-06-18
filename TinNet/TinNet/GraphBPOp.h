
/*
	2018.06.17
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPHBPOP_H

#define _CLASS_TINNET_GRAPHBPOP_H

#include "TinNetDLL.h"

#include "Graph.h"
#include "Node.h"
#include "Shape.h"
#include "GraphNode/GraphNode.h"

#include <vector>

TINNET_DLL TinNet::Node &operator+(TinNet::Node &sLeft);
TINNET_DLL TinNet::Node &operator-(TinNet::Node &sLeft);
TINNET_DLL TinNet::Node &operator+(TinNet::Node &sLeft, float nRight);
TINNET_DLL TinNet::Node &operator+(float nLeft, TinNet::Node &sRight);
TINNET_DLL TinNet::Node &operator+(TinNet::Node &sLeft, TinNet::Node &sRight);
TINNET_DLL TinNet::Node &operator-(TinNet::Node &sLeft, float nRight);
TINNET_DLL TinNet::Node &operator-(float nLeft, TinNet::Node &sRight);
TINNET_DLL TinNet::Node &operator-(TinNet::Node &sLeft, TinNet::Node &sRight);
TINNET_DLL TinNet::Node &operator*(TinNet::Node &sLeft, float nRight);
TINNET_DLL TinNet::Node &operator*(float nLeft, TinNet::Node &sRight);
TINNET_DLL TinNet::Node &operator*(TinNet::Node &sLeft, TinNet::Node &sRight);
TINNET_DLL TinNet::Node &operator/(TinNet::Node &sLeft, float nRight);
TINNET_DLL TinNet::Node &operator/(float nLeft, TinNet::Node &sRight);
TINNET_DLL TinNet::Node &operator/(TinNet::Node &sLeft, TinNet::Node &sRight);
TINNET_DLL TinNet::Node &operator^(TinNet::Node &sLeft, float nRight);
TINNET_DLL TinNet::Node &operator^(float nLeft, TinNet::Node &sRight);
TINNET_DLL TinNet::Node &operator^(TinNet::Node &sLeft, TinNet::Node &sRight);

#endif