
/*
	2018.06.01
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPH_GRAPHOP_H

#define _CLASS_TINNET_GRAPH_GRAPHOP_H

#include "../TinNetDLL.h"

#include "../Accessor.h"
#include "../Cache.h"
#include "../Iterator.h"
#include "../Shape.h"

#include <cstddef>

namespace TinNet::Graph
{
	class TINNET_DLL GraphOp final
	{
	public:
		GraphOp() = delete;
		GraphOp(const GraphOp &sSrc) = delete;
		~GraphOp() = delete;
		
	public:
		GraphOp &operator=(const GraphOp &sSrc) = delete;
		
	public:
		static void matmul(Cache &sLeft, Cache &sRight, Cache &sDestination, Shape &sLeftShape, Shape &sRightShape, Iterator<Accessor, Accessor, Accessor> &sIterator) noexcept;
	};
}

#endif