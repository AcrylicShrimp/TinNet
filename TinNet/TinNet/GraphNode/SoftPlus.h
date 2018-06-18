
/*
	2018.06.19
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPHNODE_SOFTPLUS_H

#define _CLASS_TINNET_GRAPHNODE_SOFTPLUS_H

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
	class TINNET_DLL SoftPlus final : public FullNode
	{
	public:
		SoftPlus(Graph *pGraph, const std::string &sName);
		SoftPlus(const SoftPlus &sSrc) = delete;
		~SoftPlus() = default;
		
	public:
		SoftPlus &operator=(const SoftPlus &sSrc) = delete;
		
	public:
		virtual const Shape &shape() const override;
		virtual std::string type() const override;
		inline static std::string typeName();

	protected:
		virtual void forwardPass(Cache sDestination) override;
		virtual void backwardPass(Cache sDestination, NodePtr pInput) override;
	};

	inline std::string SoftPlus::typeName()
	{
		return "softplus";
	}
}

#endif