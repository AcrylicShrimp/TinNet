
/*
	2018.06.17
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPHNODE_DIVIDE_H

#define _CLASS_TINNET_GRAPHNODE_DIVIDE_H

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
	class TINNET_DLL Divide final : public FullNode
	{
	protected:
		Shape sShape;
		Iterator<Accessor, Accessor, Accessor> sIterator;
		
	public:
		Divide(Graph *pGraph, const std::string &sName);
		Divide(const Divide &sSrc) = delete;
		~Divide() = default;
		
	public:
		Divide &operator=(const Divide &sSrc) = delete;
		
	public:
		virtual const Shape &shape() const override;
		virtual std::string type() const override;
		virtual void notifyShapeUpdated() override;
		inline static std::string typeName();

	protected:
		virtual void forwardPass(Cache sDestination) override;
		virtual void backwardPass(Cache sDestination, NodePtr pInput) override;
	};

	inline std::string Divide::typeName()
	{
		return "divide";
	}
}

#endif