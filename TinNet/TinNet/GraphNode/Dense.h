
/*
	2018.06.19
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPHNODE_DENSE_H

#define _CLASS_TINNET_GRAPHNODE_DENSE_H

#include "../TinNetDLL.h"

#include "../Accessor.h"
#include "../Cache.h"
#include "../Graph.h"
#include "../Iterator.h"
#include "../Shape.h"
#include "GraphOp.h"
#include "VariableNode.h"

#include <cstddef>
#include <functional>
#include <string>

namespace TinNet::GraphNode
{
	class TINNET_DLL Dense final : public VariableNode
	{
	protected:
		std::size_t nFanOut;
		Shape sInputShape;
		Shape sOutputShape;
		Shape sWeightShape;
		Iterator<Accessor, Accessor> sBiasIterator;
		Iterator<Accessor, Accessor, Accessor> sWeightIterator;

	public:
		Dense(Graph *pGraph, const std::string &sName, std::size_t nFanOut);
		Dense(const Dense &sSrc) = delete;
		~Dense() = default;

	public:
		Dense &operator=(const Dense &sSrc) = delete;

	public:
		virtual const Shape &shape() const override;
		virtual std::string type() const override;
		virtual void notifyShapeUpdated() override;
		virtual std::size_t fanIn() const override;
		virtual std::size_t fanOut() const override;
		virtual void initialize(std::function<float()> fInitializer) override;
		virtual void variablePass() override;
		virtual void applyGradient(float nFactor) override;
		inline static std::string typeName();

	protected:
		virtual void forwardPass(Cache sDestination) override;
		virtual void backwardPass(Cache sDestination, NodePtr pInput) override;
	};

	inline std::string Dense::typeName()
	{
		return "dense";
	}
}

#endif