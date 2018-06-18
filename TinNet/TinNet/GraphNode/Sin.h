
/*
	2018.06.18
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPHNODE_SIN_H

#define _CLASS_TINNET_GRAPHNODE_SIN_H

#include "../TinNetDLL.h"

#include "../Cache.h"
#include "../Graph.h"
#include "../Shape.h"
#include "FullNode.h"

#include <cmath>
#include <cstddef>
#include <string>

namespace TinNet::GraphNode
{
	class TINNET_DLL Sin final : public FullNode
	{
	public:
		Sin(Graph *pGraph, const std::string &sName);
		Sin(const Sin &sSrc) = delete;
		~Sin() = default;

	public:
		virtual const Shape &shape() const override;
		virtual std::string type() const override;
		inline static std::string typeName();

	protected:
		virtual void forwardPass(Cache sDestination) override;
		virtual void backwardPass(Cache sDestination, NodePtr pInput) override;
	};

	inline std::string Sin::typeName()
	{
		return "sin";
	}
}

#endif