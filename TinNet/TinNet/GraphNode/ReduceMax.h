
/*
	2018.06.19
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPHNODE_REDUCEMAX_H

#define _CLASS_TINNET_GRAPHNODE_REDUCEMAX_H

#include "../TinNetDLL.h"

#include "../Accessor.h"
#include "../Cache.h"
#include "../Graph.h"
#include "../Iterator.h"
#include "../Shape.h"
#include "FullNode.h"

#include <cstddef>
#include <limits>
#include <string>
#include <vector>

namespace TinNet::GraphNode
{
	class TINNET_DLL ReduceMax final : public FullNode
	{
	protected:
		std::vector<std::size_t> sIndex;
		Shape sShape;
		Shape sUnsqueezedShape;
		Iterator<Accessor, Accessor> sIterator;
		std::vector<bool> sAxis;
		bool bSqueeze;

	public:
		ReduceMax(Graph *pGraph, const std::string &sName, const std::vector<bool> &sAxis, bool bSqueeze);
		ReduceMax(const ReduceMax &sSrc) = delete;
		~ReduceMax() = default;

	public:
		ReduceMax &operator=(const ReduceMax &sSrc) = delete;

	public:
		virtual Shape shape() const override;
		virtual std::string type() const override;
		virtual void notifyShapeUpdated() override;
		inline static std::string typeName();

	protected:
		virtual void forwardPass(Cache sDestination) override;
		virtual void backwardPass(Cache sDestination, NodePtr pInput) override;
	};

	inline std::string ReduceMax::typeName()
	{
		return "reduceMax";
	}
}

#endif