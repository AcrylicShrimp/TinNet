
/*
	2018.06.17
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPHNODE_SUBTRACT_H

#define _CLASS_TINNET_GRAPHNODE_SUBTRACT_H

#include "../TinNetDLL.h"

#include "../Accessor.h"
#include "../Cache.h"
#include "../Graph.h"
#include "../Iterator.h"
#include "../Shape.h"
#include "FullNode.h"

#include <cstddef>
#include <string>

namespace TinNet::GraphNode
{
	class TINNET_DLL Subtract final : public FullNode
	{
	protected:
		Shape sShape;
		Iterator<Accessor, Accessor, Accessor> sIterator;
		
	public:
		Subtract(Graph *pGraph, const std::string &sName);
		Subtract(const Subtract &sSrc) = delete;
		~Subtract() = default;
		
	public:
		Subtract &operator=(const Subtract &sSrc) = delete;
		
	public:
		virtual const Shape &shape() const override;
		virtual std::string type() const override;
		virtual void notifyShapeUpdated() override;
		inline static std::string typeName();

	protected:
		virtual void forwardPass(Cache sDestination) override;
		virtual void backwardPass(Cache sDestination, NodePtr pInput) override;
	};

	inline std::string Subtract::typeName()
	{
		return "subtract";
	}
}

#endif