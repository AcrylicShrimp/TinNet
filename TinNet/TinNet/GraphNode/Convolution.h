
/*
	2018.06.19
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPHNODE_CONVOLUTION_H

#define _CLASS_TINNET_GRAPHNODE_CONVOLUTION_H

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
	class TINNET_DLL Convolution final : public VariableNode
	{
	protected:
		Cache sInputCache;
		std::vector<float> sInput;
		std::vector<std::size_t> sInputIndexList;
		Shape sInputShape;
		Shape sInputInternalShape;
		Shape sOutputShape;
		Shape sKernelShape;
		Accessor sInputAccessor;
		Accessor sResultAccessor;
		Iterator<Accessor, Accessor, Accessor> sIterator;
		std::size_t nKernelWidth;
		std::size_t nKernelHeight;
		std::size_t nHStride;
		std::size_t nVStride;
		std::size_t nHPaddingN;
		std::size_t nHPaddingP;
		std::size_t nVPaddingN;
		std::size_t nVPaddingP;
		
	public:
		Convolution(Graph *pGraph, const std::string &sName,
			std::size_t nKernelWidth,
			std::size_t nKernelHeight,
			std::size_t nHStride,
			std::size_t nVStride,
			std::size_t nOutputWidth,
			std::size_t nOutputHeight,
			std::size_t nOutputChannel);
		Convolution(const Convolution &sSrc) = delete;
		~Convolution() = default;
		
	public:
		Convolution &operator=(const Convolution &sSrc) = delete;
		
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

	inline std::string Convolution::typeName()
	{
		return "convolution";
	}
}

#endif