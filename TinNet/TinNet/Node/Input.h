
/*
	2019.03.13
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_NODE_INPUT_H

#define _CLASS_TINNET_NODE_INPUT_H

#include "../TinNetDLL.h"

#include "../Core/Shape.h"
#include "../Core/Span.h"

#include "Node.h"

#include <string_view>

namespace TinNet::Node
{
	class TINNET_DLL Input : public Node
	{
	protected:
		Core::Span sInputSpan;
		Core::Shape sInputShape;

	public:
		Input(std::string_view sName);
		Input(const Input &&sSrc) = delete;
		virtual ~Input() noexcept = default;

	public:
		Input &operator=(const Input &sSrc) = delete;

	public:
		void feed(Core::Span sSpan, Core::Shape sShape);

	protected:
		virtual void __evaluateShape() override;
		virtual void __evaluateOutput() override;
	};
}

#endif