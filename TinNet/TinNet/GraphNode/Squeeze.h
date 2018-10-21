
/*
	2018.06.18
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPHNODE_SQUEEZE_H

#define _CLASS_TINNET_GRAPHNODE_SQUEEZE_H

#include "../TinNetDLL.h"

#include "../Cache.h"
#include "../Graph.h"
#include "../Shape.h"
#include "BackpropNode.h"

#include <cstddef>
#include <string>

namespace TinNet::GraphNode
{
	class TINNET_DLL Squeeze final : public BackpropNode
	{
	protected:
		Shape sShape;

	public:
		Squeeze(Graph *pGraph, const std::string &sName);
		Squeeze(const Squeeze &sSrc) = delete;
		~Squeeze() = default;

	public:
		Squeeze &operator=(const Squeeze &sSrc) = delete;

	public:
		virtual Shape shape() const override;
		virtual std::string type() const override;
		virtual void notifyShapeUpdated() override;
		virtual Cache forward() override;
		inline static std::string typeName();

	protected:
		virtual void forwardPass(Cache sDestination) override;
		virtual void backwardPass(Cache sDestination, NodePtr pInput) override;
	};

	inline std::string Squeeze::typeName()
	{
		return "squeeze";
	}
}

#endif