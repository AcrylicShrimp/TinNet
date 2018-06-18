
/*
	2018.06.19
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPHNODE_SINH_H

#define _CLASS_TINNET_GRAPHNODE_SINH_H

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
	class TINNET_DLL Sinh final : public FullNode
	{
	public:
		Sinh(Graph *pGraph, const std::string &sName);
		Sinh(const Sinh &sSrc) = delete;
		~Sinh() = default;
		
	public:
		Sinh &operator=(const Sinh &sSrc) = delete;
		
	public:
		virtual const Shape &shape() const override;
		virtual std::string type() const override;
		inline static std::string typeName();

	protected:
		virtual void forwardPass(Cache sDestination) override;
		virtual void backwardPass(Cache sDestination, NodePtr pInput) override;
	};

	inline std::string Sinh::typeName()
	{
		return "sinh";
	}
}

#endif