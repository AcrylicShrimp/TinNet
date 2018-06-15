
/*
	2018.06.02
	Created by AcrylicShrimp.
*/

#include "MatMul.h"

namespace TinNet::Graph::Node
{
	MatMul::MatMul(const std::string &sName, Graph *pGraph) :
		FullCachedGraphNode(sName, pGraph),
		sShape{}
	{
		//Empty.
	}

	const Shape &MatMul::shape() const
	{
		return this->sShape;
	}

	std::size_t MatMul::maxBackwardNodeCount() const
	{
		return 2;
	}

	void MatMul::initNode()
	{
		const Shape &sLeft{this->sBackwardList.front()->shape()};
		const Shape &sRight{this->sBackwardList.back()->shape()};

		if (sLeft.rank() < 2)
			throw std::invalid_argument("need matrix or tensor, not scalar or vector");

		if (sRight.rank() < 2)
			throw std::invalid_argument("need matrix or tensor, not scalar or vector");

		if (sLeft.rank() != sRight.rank())
			throw std::invalid_argument("rank mismatch");

		if (sLeft[sLeft.rank() - 1] != sRight[sRight.rank() - 2])
			throw std::invalid_argument("cannot multiply matrix");

		for (std::size_t nAxis{2}, nRank{sLeft.rank()}; nAxis < nRank; ++nAxis)
			if (sLeft[nAxis] != sRight[nAxis])
				throw std::invalid_argument("dimension must be equal");

		this->sShape = sLeft;
		this->sShape.set(this->sShape.rank() - 2, sLeft[sLeft.rank() - 2]);
		this->sShape.set(this->sShape.rank() - 1, sRight[sRight.rank() - 1]);

		this->sIterator.init(this->sShape, Accessor{this->sShape}, Accessor{sLeft}, Accessor{sRight});
	}

	void MatMul::forwardPass(Cache sDestination)
	{
		GraphOp::matmul(
			this->sBackwardList.front()->shape(),
			this->sBackwardList.back()->shape(),
			this->sBackwardList.front()->forward(),
			this->sBackwardList.back()->forward(),
			sDestination,
			this->sIterator);
	}

	void MatMul::backwardPass(GraphNode *pBackward, Cache sDestination)
	{
		if (pBackward == this->sBackwardList.front())
			GraphOp::dMatmulLeft(
				this->sBackwardList.front()->shape(),
				this->sBackwardList.back()->shape(),
				this->backward(),
				this->sBackwardList.back()->forward(),
				sDestination,
				this->sIterator);
		else
			GraphOp::dMatmulRight(
				this->sBackwardList.front()->shape(),
				this->sBackwardList.back()->shape(),
				this->backward(),
				this->sBackwardList.front()->forward(),
				sDestination,
				this->sIterator);
	}
}