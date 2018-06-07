
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
#include <immintrin.h>

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
		static void matmul(const Shape &sLeftShape, const Shape &sRightShape, const Cache sLeft, const Cache sRight, Cache sDestination, Iterator<Accessor, Accessor, Accessor> &sIterator) noexcept;
		static void matmulAccumulate(const Shape &sLeftShape, const Shape &sRightShape, const Cache sLeft, const Cache sRight, Cache sDestination, Iterator<Accessor, Accessor, Accessor> &sIterator) noexcept;
		static void dMatmulLeft(const Shape &sLeftShape, const Shape &sRightShape, const Cache sBackward, const Cache sRight, Cache sDestination, Iterator<Accessor, Accessor, Accessor> &sIterator) noexcept;
		static void dMatmulRight(const Shape &sLeftShape, const Shape &sRightShape, const Cache sBackward, const Cache sLeft, Cache sDestination, Iterator<Accessor, Accessor, Accessor> &sIterator) noexcept;
		static void matmulTransposed(const Shape &sLeftShape, const Shape &sRightShape, const Cache sLeft, const Cache sRight, Cache sDestination, Iterator<Accessor, Accessor, Accessor> &sIterator) noexcept;
		static void matmulAccumulateTransposed(const Shape &sLeftShape, const Shape &sRightShape, const Cache sLeft, const Cache sRight, Cache sDestination, Iterator<Accessor, Accessor, Accessor> &sIterator) noexcept;
		static void dMatmulLeftTransposed(const Shape &sLeftShape, const Shape &sRightShape, const Cache sBackward, const Cache sRight, Cache sDestination, Iterator<Accessor, Accessor, Accessor> &sIterator) noexcept;
		static void dMatmulRightTransposed(const Shape &sLeftShape, const Shape &sRightShape, const Cache sBackward, const Cache sLeft, Cache sDestination, Iterator<Accessor, Accessor, Accessor> &sIterator) noexcept;
		static void matmulTransposedSIMD(const Shape &sLeftShape, const Shape &sRightShape, const Cache sLeft, const Cache sRight, Cache sDestination, Iterator<Accessor, Accessor, Accessor> &sIterator) noexcept;
		static void matmulAccumulateTransposedSIMD(const Shape &sLeftShape, const Shape &sRightShape, const Cache sLeft, const Cache sRight, Cache sDestination, Iterator<Accessor, Accessor, Accessor> &sIterator) noexcept;
		static void dMatmulLeftTransposedSIMD(const Shape &sLeftShape, const Shape &sRightShape, const Cache sBackward, const Cache sRight, Cache sDestination, Iterator<Accessor, Accessor, Accessor> &sIterator) noexcept;
		static void dMatmulRightTransposedSIMD(const Shape &sLeftShape, const Shape &sRightShape, const Cache sBackward, const Cache sLeft, Cache sDestination, Iterator<Accessor, Accessor, Accessor> &sIterator) noexcept;
	};
}

#endif