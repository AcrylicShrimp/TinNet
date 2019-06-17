
/*
	2019.03.17
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_NODE_PARAMETER_H

#define _CLASS_TINNET_NODE_PARAMETER_H

#include "../TinNetDLL.h"

#include "../Core/Graph.h"
#include "../Core/Memory.h"
#include "../Core/Shape.h"
#include "../Core/Span.h"
#include "../Initializer/Initializer.h"

#include "Node.h"
#include "NodeInput.h"

#include <cassert>
#include <string_view>

namespace TinNet::Node
{
	class TINNET_DLL Parameter : public Node
	{
		TINNET_NODE_TYPE_DCL(Parameter)

	public:
		Initializer::Initializer *const pInitializer;
		const Core::Shape sParameterShape;

	protected:
		Core::Memory<float> sParameter;
		
	public:
		Parameter(Core::Graph *pGraph, std::string_view sName, Core::Shape sShape, Initializer::Initializer *pInitializer);
		Parameter(const Parameter &sSrc) = delete;
		virtual ~Parameter() noexcept = default;
		
	public:
		Parameter &operator=(const Parameter &sSrc) = delete;
		
	public:
		inline Core::Span<float> parameter() const noexcept;

	protected:
		virtual void __evaluateShape() override;
		virtual void __evaluateOutput() override;
	};

	inline Core::Span<float> Parameter::parameter() const noexcept
	{
		return this->sParameter.span();
	}
}

#endif