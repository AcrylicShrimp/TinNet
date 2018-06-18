
/*
	2018.06.18
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPHNODE_LOG2_H

#define _CLASS_TINNET_GRAPHNODE_LOG2_H

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
	class TINNET_DLL Log2 final : public FullNode
	{
	public:
		Log2(Graph *pGraph, const std::string &sName);
		Log2(const Log2 &sSrc) = delete;
		~Log2() = default;

	public:
		Log2 &operator=(const Log2 &sSrc) = delete;

	public:
		virtual const Shape &shape() const override;
		virtual std::string type() const override;
		inline static std::string typeName();

	protected:
		virtual void forwardPass(Cache sDestination) override;
		virtual void backwardPass(Cache sDestination, NodePtr pInput) override;
	};

	inline std::string Log2::typeName()
	{
		return "log2";
	}
}

#endif