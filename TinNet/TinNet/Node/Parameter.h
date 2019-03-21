
/*
	2019.03.17
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_NODE_PARAMETER_H

#define _CLASS_TINNET_NODE_PARAMETER_H

#include "../TinNetDLL.h"

#include "../Core/Graph.h"
#include "../Core/Shape.h"
#include "../Core/Span.h"
#include "../Initializer/InitializerBase.h"

#include "Node.h"
#include "NodeInput.h"

#include <string_view>

namespace TinNet::Node
{
	class TINNET_DLL Parameter : public Node
	{
		TINNET_NODE_TYPE_DCL(Parameter)

	protected:
		Core::Shape sParameterShape;
		Core::Memory sParameter;
		
	public:
		Parameter(Core::Graph *pGraph, std::string_view sName, Core::Shape sShape);
		Parameter(const Parameter &sSrc) = delete;
		virtual ~Parameter() noexcept = default;
		
	public:
		Parameter &operator=(const Parameter &sSrc) = delete;
		
	public:
		inline Core::Span parameter() const noexcept;
		template<class T> void initialize(T sInitializer);
		template<class I> void initialize(I iBegin, I iEnd);

	protected:
		virtual void __evaluateShape() override;
		virtual void __evaluateOutput() override;
	};

	inline Core::Span Parameter::parameter() const noexcept
	{
		return this->sParameter.span();
	}
}

#include "Parameter.hpp"

#endif