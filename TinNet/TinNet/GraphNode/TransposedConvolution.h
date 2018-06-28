
/*
	2018.06.23
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPHNODE_TRANSPOSEDCONVOLUTION_H

#define _CLASS_TINNET_GRAPHNODE_TRANSPOSEDCONVOLUTION_H

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
	class TINNET_DLL TransposedConvolution final : public VariableNode
	{
	protected:
		Cache sOutputCache;
		std::vector<float> sOutput;
		std::vector<std::size_t> sOutputIndexList;
		Shape sInputShape;
		Shape sOutputShape;
		Shape sOutputInternalShape;
		Shape sKernelShape;
		Accessor sInputAccessor;
		Accessor sOutputAccessor;
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
		TransposedConvolution(Graph *pGraph, const std::string &sName, NodePtr pSharingNode,
			std::size_t nKernelWidth,
			std::size_t nKernelHeight,
			std::size_t nHStride,
			std::size_t nVStride,
			std::size_t nOutputWidth,
			std::size_t nOutputHeight,
			std::size_t nOutputChannel);
		TransposedConvolution(const TransposedConvolution &sSrc) = delete;
		~TransposedConvolution() = default;
		
	public:
		TransposedConvolution &operator=(const TransposedConvolution &sSrc) = delete;
		
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

	inline std::string TransposedConvolution::typeName()
	{
		return "transposedConvolution";
	}
}

#endif