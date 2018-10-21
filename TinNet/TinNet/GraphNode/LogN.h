
/*
	2018.06.18
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPHNODE_LOGN_H

#define _CLASS_TINNET_GRAPHNODE_LOGN_H

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
	class TINNET_DLL LogN final : public FullNode
	{
	protected:
		float nLogBase;

	public:
		LogN(Graph *pGraph, const std::string &sName, float nBase);
		LogN(const LogN &sSrc) = delete;
		~LogN() = default;

	public:
		LogN &operator=(const LogN &sSrc) = delete;

	public:
		virtual Shape shape() const override;
		virtual std::string type() const override;
		inline static std::string typeName();

	protected:
		virtual void forwardPass(Cache sDestination) override;
		virtual void backwardPass(Cache sDestination, NodePtr pInput) override;
	};

	inline std::string LogN::typeName()
	{
		return "logn";
	}
}

#endif