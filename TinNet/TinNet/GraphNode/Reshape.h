
/*
	2018.06.18
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPHNODE_RESHAPE_H

#define _CLASS_TINNET_GRAPHNODE_RESHAPE_H

#include "../TinNetDLL.h"

#include "../Cache.h"
#include "../Graph.h"
#include "../Shape.h"
#include "BackpropNode.h"

#include <cstddef>
#include <string>

namespace TinNet::GraphNode
{
	class TINNET_DLL Reshape final : public BackpropNode
	{
	protected:
		Shape sShape;
		
	public:
		Reshape(Graph *pGraph, const std::string &sName, const Shape &sShape);
		Reshape(const Reshape &sSrc) = delete;
		~Reshape() = default;
		
	public:
		Reshape &operator=(const Reshape &sSrc) = delete;
		
	public:
		virtual const Shape &shape() const override;
		virtual std::string type() const override;
		virtual Cache forward() override;
		inline static std::string typeName();

	protected:
		virtual void forwardPass(Cache sDestination) override;
		virtual void backwardPass(Cache sDestination, NodePtr pInput) override;
	};

	inline std::string Reshape::typeName()
	{
		return "reshape";
	}
}

#endif