
/*
	2018.06.01
	Created by AcrylicShrimp.
*/

#include "Dense.h"

namespace TinNet::Graph::Node
{
	Dense::Dense(const std::string &sName, Graph *pGraph, std::size_t nFanOut) :
		FullCachedGraphNode(sName, pGraph),
		nFanOut{nFanOut},
		sShape{}
	{
		//Empty.
	}

	const Shape &Dense::shape() const
	{
		return this->sShape;
	}

	std::size_t Dense::maxBackwardNodeCount() const
	{
		return 2;
	}

	void Dense::initNode()
	{
		this->sShape = Shape::broadcast(this->sBackwardList.front()->shape(), this->sBackwardList.back()->shape());
		this->sIterator.init(this->sShape, Accessor{this->sShape}, Accessor{this->sBackwardList.front()->shape()}, Accessor{this->sBackwardList.back()->shape()});
	}

	void Dense::forwardPass(Cache sDestination)
	{
		const auto &sLeft{this->sBackwardList.front()->forward()};


	}

	void Dense::backwardPass(GraphNode *pBackward, Cache sDestination)
	{

	}
}