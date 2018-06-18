
/*
	2018.06.19
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPHNODE_COSH_H

#define _CLASS_TINNET_GRAPHNODE_COSH_H

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
	class TINNET_DLL Cosh final : public FullNode
	{
	public:
		Cosh(Graph *pGraph, const std::string &sName);
		Cosh(const Cosh &sSrc) = delete;
		~Cosh() = default;
		
	public:
		Cosh &operator=(const Cosh &sSrc) = delete;
		
	public:
		virtual const Shape &shape() const override;
		virtual std::string type() const override;
		inline static std::string typeName();

	protected:
		virtual void forwardPass(Cache sDestination) override;
		virtual void backwardPass(Cache sDestination, NodePtr pInput) override;
	};

	inline std::string Cosh::typeName()
	{
		return "cosh";
	}
}

#endif