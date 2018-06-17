
/*
	2018.06.17
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPHNODE_ADD_H

#define _CLASS_TINNET_GRAPHNODE_ADD_H

#include "../TinNetDLL.h"

#include "../Accessor.h"
#include "../Cache.h"
#include "../Graph.h"
#include "../Iterator.h"
#include "../Shape.h"
#include "FullNode.h"

#include <cstddef>
#include <string>

namespace TinNet::GraphNode
{
	class TINNET_DLL Add final : public FullNode
	{
	private:
		Shape sShape;
		Iterator<Accessor, Accessor, Accessor> sIterator;
		
	public:
		Add(Graph *pGraph, const std::string &sName);
		Add(const Add &sSrc) = delete;
		~Add() = default;
		
	public:
		Add &operator=(const Add &sSrc) = delete;
		
	public:
		virtual const Shape &shape() const override;
		virtual const std::string &type() const override;
		virtual void notifyShapeUpdated() override;

	protected:
		virtual void forwardPass(Cache sDestination) override;
		virtual void backwardPass(Cache sDestination, NodePtr pInput) override;
	};
}

#endif