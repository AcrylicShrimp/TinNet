
/*
	2018.06.18
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPHNODE_REDUCESUM_H

#define _CLASS_TINNET_GRAPHNODE_REDUCESUM_H

#include "../TinNetDLL.h"

#include "../Accessor.h"
#include "../Cache.h"
#include "../Graph.h"
#include "../Iterator.h"
#include "../Shape.h"
#include "FullNode.h"

#include <cstddef>
#include <string>
#include <vector>

namespace TinNet::GraphNode
{
	class TINNET_DLL ReduceSum final : public FullNode
	{
	protected:
		Shape sShape;
		Shape sUnsqueezedShape;
		Iterator<Accessor, Accessor> sIterator;
		std::vector<bool> sAxis;
		bool bSqueeze;
		
	public:
		ReduceSum(Graph *pGraph, const std::string &sName, const std::vector<bool> &sAxis, bool bSqueeze);
		ReduceSum(const ReduceSum &sSrc) = delete;
		~ReduceSum() = default;
		
	public:
		ReduceSum &operator=(const ReduceSum &sSrc) = delete;
		
	public:
		virtual Shape shape() const override;
		virtual std::string type() const override;
		virtual void notifyShapeUpdated() override;
		inline static std::string typeName();

	protected:
		virtual void forwardPass(Cache sDestination) override;
		virtual void backwardPass(Cache sDestination, NodePtr pInput) override;
	};

	inline std::string ReduceSum::typeName()
	{
		return "reduceSum";
	}
}

#endif