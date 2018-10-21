
/*
	2018.06.19
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPHNODE_REDUCEMEAN_H

#define _CLASS_TINNET_GRAPHNODE_REDUCEMEAN_H

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
	class TINNET_DLL ReduceMean final : public FullNode
	{
	protected:
		float nFactor;
		Shape sShape;
		Shape sUnsqueezedShape;
		Iterator<Accessor, Accessor> sIterator;
		std::vector<bool> sAxis;
		bool bSqueeze;
		
	public:
		ReduceMean(Graph *pGraph, const std::string &sName, const std::vector<bool> &sAxis, bool bSqueeze);
		ReduceMean(const ReduceMean &sSrc) = delete;
		~ReduceMean() = default;
		
	public:
		ReduceMean &operator=(const ReduceMean &sSrc) = delete;
		
	public:
		virtual Shape shape() const override;
		virtual std::string type() const override;
		virtual void notifyShapeUpdated() override;
		inline static std::string typeName();

	protected:
		virtual void forwardPass(Cache sDestination) override;
		virtual void backwardPass(Cache sDestination, NodePtr pInput) override;
	};

	inline std::string ReduceMean::typeName()
	{
		return "reduceMean";
	}
}

#endif