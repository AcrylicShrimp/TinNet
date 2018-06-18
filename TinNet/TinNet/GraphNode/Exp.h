
/*
	2018.06.18
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPHNODE_EXP_H

#define _CLASS_TINNET_GRAPHNODE_EXP_H

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
	class TINNET_DLL Exp final : public FullNode
	{
	public:
		Exp(Graph *pGraph, const std::string &sName);
		Exp(const Exp &sSrc) = delete;
		~Exp() = default;
		
	public:
		virtual const Shape &shape() const override;
		virtual std::string type() const override;
		inline static std::string typeName();

	protected:
		virtual void forwardPass(Cache sDestination) override;
		virtual void backwardPass(Cache sDestination, NodePtr pInput) override;
	};

	inline std::string Exp::typeName()
	{
		return "exp";
	}
}

#endif