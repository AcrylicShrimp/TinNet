
/*
	2018.06.17
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPHNODE_INPUT_H

#define _CLASS_TINNET_GRAPHNODE_INPUT_H

#include "../TinNetDLL.h"

#include "../Cache.h"
#include "../Graph.h"
#include "../Feedable.h"
#include "../Shape.h"
#include "BackpropNode.h"

#include <cstddef>
#include <string>

namespace TinNet::GraphNode
{
	class TINNET_DLL Input final : public BackpropNode, public Feedable
	{
	protected:
		ShapedCache sShapedCache;
		
	public:
		Input(Graph *pGraph, const std::string &sName, const Shape &sShape);
		Input(const Input &sSrc) = delete;
		~Input() = default;
		
	public:
		Input &operator=(const Input &sSrc) = delete;
		
	public:
		virtual const Shape &shape() const override;
		virtual const std::string &type() const override;
		virtual Cache forward() override;
		virtual void feed(ShapedCache sShapedCache) override;

	protected:
		virtual void forwardPass(Cache sDestination) override;
		virtual void backwardPass(Cache sDestination, NodePtr pInput) override;
	};
}

#endif