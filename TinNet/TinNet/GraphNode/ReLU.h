
/*
	2018.06.19
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPHNODE_RELU_H

#define _CLASS_TINNET_GRAPHNODE_RELU_H

#include "../TinNetDLL.h"

#include "../Cache.h"
#include "../Graph.h"
#include "../Shape.h"
#include "FullNode.h"

#include <cstddef>
#include <immintrin.h>
#include <string>

namespace TinNet::GraphNode
{
	class TINNET_DLL ReLU final : public FullNode
	{
	protected:
		float nAlpha;

	public:
		ReLU(Graph *pGraph, const std::string &sName, float nAlpha);
		ReLU(const ReLU &sSrc) = delete;
		~ReLU() = default;
		
	public:
		ReLU &operator=(const ReLU &sSrc) = delete;
		
	public:
		virtual const Shape &shape() const override;
		virtual std::string type() const override;
		inline static std::string typeName();

	protected:
		virtual void forwardPass(Cache sDestination) override;
		virtual void backwardPass(Cache sDestination, NodePtr pInput) override;
	};

	inline std::string ReLU::typeName()
	{
		return "relu";
	}
}

#endif