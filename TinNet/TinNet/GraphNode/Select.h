
/*
	2018.06.27
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPHNODE_SELECT_H

#define _CLASS_TINNET_GRAPHNODE_SELECT_H

#include "../TinNetDLL.h"

#include "../Cache.h"
#include "../Graph.h"
#include "../Feedable.h"
#include "../Shape.h"
#include "../ShapedCache.h"
#include "BackpropNode.h"

#include <cstddef>
#include <string>
#include <vector>

namespace TinNet::GraphNode
{
	class TINNET_DLL Select final : public BackpropNode, public Feedable
	{
	protected:
		bool bCondition;

	public:
		Select(Graph *pGraph, const std::string &sName);
		Select(const Select &sSrc) = delete;
		~Select() = default;

	public:
		Select &operator=(const Select &sSrc) = delete;

	public:
		virtual Shape shape() const override;
		virtual std::string type() const override;
		virtual Cache forward() override;
		virtual void feed(const ShapedCache &sShapedCache) override;
		inline static std::string typeName();

	protected:
		virtual void forwardPass(Cache sDestination) override;
		virtual void backwardPass(Cache sDestination, NodePtr pInput) override;
	};

	inline std::string Select::typeName()
	{
		return "select";
	}
}

#endif