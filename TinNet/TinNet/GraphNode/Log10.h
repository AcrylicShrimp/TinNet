
/*
	2018.06.18
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPHNODE_LOG10_H

#define _CLASS_TINNET_GRAPHNODE_LOG10_H

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
	class TINNET_DLL Log10 final : public FullNode
	{
	public:
		Log10(Graph *pGraph, const std::string &sName);
		Log10(const Log10 &sSrc) = delete;
		~Log10() = default;

	public:
		Log10 &operator=(const Log10 &sSrc) = delete;

	public:
		virtual Shape shape() const override;
		virtual std::string type() const override;
		inline static std::string typeName();

	protected:
		virtual void forwardPass(Cache sDestination) override;
		virtual void backwardPass(Cache sDestination, NodePtr pInput) override;
	};

	inline std::string Log10::typeName()
	{
		return "log10";
	}
}

#endif