
/*
	2018.06.19
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPHNODE_SOFTMAX_H

#define _CLASS_TINNET_GRAPHNODE_SOFTMAX_H

#include "../TinNetDLL.h"

#include "../Accessor.h"
#include "../Cache.h"
#include "../Graph.h"
#include "../Iterator.h"
#include "../Shape.h"
#include "FullNode.h"

#include <cmath>
#include <cstddef>
#include <string>
#include <vector>

namespace TinNet::GraphNode
{
	class TINNET_DLL Softmax final : public FullNode
	{
	protected:
		Iterator<Accessor, Accessor> sIterator;
		std::vector<bool> sAxis;
		std::vector<float> sSum;
		std::vector<float> sSumBackward;
		Cache sSumCache;
		Cache sSumBackwardCache;
		
	public:
		Softmax(Graph *pGraph, const std::string &sName, const std::vector<bool> &sAxis);
		Softmax(const Softmax &sSrc) = delete;
		~Softmax() = default;
		
	public:
		Softmax &operator=(const Softmax &sSrc) = delete;
		
	public:
		virtual const Shape &shape() const override;
		virtual std::string type() const override;
		virtual void notifyShapeUpdated() override;
		inline static std::string typeName();

	protected:
		virtual void forwardPass(Cache sDestination) override;
		virtual void backwardPass(Cache sDestination, NodePtr pInput) override;
	};

	inline std::string Softmax::typeName()
	{
		return "softmax";
	}
}

#endif