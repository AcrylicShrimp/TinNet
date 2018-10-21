
/*
	2018.06.18
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPHNODE_CONSTANT_H

#define _CLASS_TINNET_GRAPHNODE_CONSTANT_H

#include "../TinNetDLL.h"

#include "../Cache.h"
#include "../Graph.h"
#include "../Shape.h"
#include "../ShapedCache.h"
#include "BackpropNode.h"

#include <cstddef>
#include <string>

namespace TinNet::GraphNode
{
	class TINNET_DLL Constant final : public BackpropNode
	{
	protected:
		ShapedCache sShapedCache;
		std::vector<float> sValue;
		
	public:
		Constant(Graph *pGraph, const std::string &sName, const Shape &sShape, const std::vector<float> &sValue);
		Constant(const Constant &sSrc) = delete;
		~Constant() = default;
		
	public:
		Constant &operator=(const Constant &sSrc) = delete;
		
	public:
		virtual Shape shape() const override;
		virtual std::string type() const override;
		virtual Cache forward() override;
		inline static std::string typeName();

	protected:
		virtual void forwardPass(Cache sDestination) override;
		virtual void backwardPass(Cache sDestination, NodePtr pInput) override;
	};

	inline std::string Constant::typeName()
	{
		return "constant";
	}
}

#endif