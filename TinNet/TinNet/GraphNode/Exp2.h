
/*
	2018.06.18
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPHNODE_EXP2_H

#define _CLASS_TINNET_GRAPHNODE_EXP2_H

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
	class TINNET_DLL Exp2 final : public FullNode
	{
	public:
		Exp2(Graph *pGraph, const std::string &sName);
		Exp2(const Exp2 &sSrc) = delete;
		~Exp2() = default;
		
	public:
		Exp2 &operator=(const Exp2 &sSrc) = delete;
		
	public:
		virtual Shape shape() const override;
		virtual std::string type() const override;
		inline static std::string typeName();

	protected:
		virtual void forwardPass(Cache sDestination) override;
		virtual void backwardPass(Cache sDestination, NodePtr pInput) override;
	};

	inline std::string Exp2::typeName()
	{
		return "exp2";
	}
}

#endif