
/*
	2018.06.18
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPHNODE_NEG_H

#define _CLASS_TINNET_GRAPHNODE_NEG_H

#include "../TinNetDLL.h"

#include "../Cache.h"
#include "../Graph.h"
#include "../Shape.h"
#include "FullNode.h"

#include <cstddef>
#include <string>

namespace TinNet::GraphNode
{
	class TINNET_DLL Neg final : public FullNode
	{
	public:
		Neg(Graph *pGraph, const std::string &sName);
		Neg(const Neg &sSrc) = delete;
		~Neg() = default;
		
	public:
		Neg &operator=(const Neg &sSrc) = delete;
		
	public:
		virtual Shape shape() const override;
		virtual std::string type() const override;
		inline static std::string typeName();

	protected:
		virtual void forwardPass(Cache sDestination) override;
		virtual void backwardPass(Cache sDestination, NodePtr pInput) override;
	};

	inline std::string Neg::typeName()
	{
		return "neg";
	}
}

#endif