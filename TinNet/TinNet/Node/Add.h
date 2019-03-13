
/*
	2019.03.13
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_NODE_ADD_H

#define _CLASS_TINNET_NODE_ADD_H

#include "../TinNetDLL.h"

#include "Node.h"
#include "NodeInput.h"

#include <cstddef>
#include <string_view>

namespace TinNet::Node
{
	class TINNET_DLL Add : public Node
	{
	protected:
		NodeInput sInputLeft;
		NodeInput sInputRight;

	public:
		Add(std::string_view sName);
		Add(const Add &sSrc) = delete;
		virtual ~Add() noexcept = default;

	protected:
		virtual void __evaluateShape() override;
		virtual void __evaluateOutput() override;
		void __backwardOpLeft(const Node *pDy);
		void __backwardOpRight(const Node *pDy);
	};
}

#endif