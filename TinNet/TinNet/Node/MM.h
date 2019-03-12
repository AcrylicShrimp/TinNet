
/*
	2019.03.11
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_NODE_MM_H

#define _CLASS_TINNET_NODE_MM_H

#include "../TinNetDLL.h"

#include "../Core/Node.h"
#include "../Core/NodeInput.h"
#include "../Core/Shape.h"
#include "../Core/Span.h"

#include "../Compute/GEMM.h"

#include <string_view>

namespace TinNet::Node
{
	class TINNET_DLL MM : public Core::Node
	{
	protected:
		Core::NodeInput sInputLeft;
		Core::NodeInput sInputRight;

	public:
		MM(std::string_view sName);
		MM(const MM &sSrc) = delete;
		virtual ~MM() noexcept = default;
		
	public:
		MM &operator=(const MM &sSrc) = delete;
		
	public:
		virtual void updateShape() override;
		virtual void evaluate() override;
		
	protected:
		Core::Span backwardOpLeft(const Core::Node *pDy);
		Core::Span backwardOpRight(const Core::Node *pDy);
	};
}

#endif