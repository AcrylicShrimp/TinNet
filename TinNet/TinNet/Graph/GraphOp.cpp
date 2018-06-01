
/*
	2018.06.01
	Created by AcrylicShrimp.
*/

#include "GraphOp.h"

namespace TinNet::Graph
{
	void GraphOp::matmul(Cache &sLeft, Cache &sRight, Cache &sDestination, Shape &sLeftShape, Shape &sRightShape, Iterator<Accessor, Accessor, Accessor> &sIterator) noexcept
	{
		if (sLeftShape.rank() < 2)
			return;

		if (sRightShape.rank() < 2)
			return;

		if (sLeftShape.rank() != sRightShape.rank())
			return;

		for (std::size_t nAxis{2}, nRank{sLeftShape.rank()}; nAxis < nRank; ++nAxis)
			if (sLeft[nAxis] != sRight[nAxis])
				return;

		Shape sDestinationShape{sLeftShape};
		std::size_t nRow{sDestinationShape[sDestinationShape.rank() - 2] = sLeftShape[sLeftShape.rank() - 2]};
		std::size_t nColumn{sDestinationShape[sDestinationShape.rank() - 1] = sRightShape[sRightShape.rank() - 1]};

		for (sIterator.prepare(2); sIterator; ++sIterator)
		{
			std::size_t nIndex0 = sIterator.index<0>();
			std::size_t nIndex1 = sIterator.index<1>();
			std::size_t nIndex2 = sIterator.index<2>();

			for (std::size_t nR{0}; nR < nRow; ++nR)
				for (std::size_t nC{0}; nC < nColumn; ++nC, ++nIndex0, ++nIndex1)
				{

				}
		}
	}
}