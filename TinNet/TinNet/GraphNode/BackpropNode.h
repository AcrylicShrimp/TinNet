
/*
	2018.06.17
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPHNODE_BACKPROPNODE_H

#define _CLASS_TINNET_GRAPHNODE_BACKPROPNODE_H

#include "../TinNetDLL.h"

#include "../Cache.h"
#include "../CacheContainer.h"
#include "../Graph.h"
#include "../Node.h"

#include <string>

namespace TinNet::GraphNode
{
	class TINNET_DLL BackpropNode : public Node
	{
	protected:
		CachePtr pGradient;
		
	public:
		BackpropNode(Graph *pGraph, const std::string &sName);
		BackpropNode(const BackpropNode &sSrc) = delete;
		~BackpropNode() = default;
		
	public:
		BackpropNode &operator=(const BackpropNode &sSrc) = delete;
		
	public:
		virtual std::string type() const override;
		virtual void notifyShapeUpdated() override;
		virtual void notifyBackwardEnabled() override;
		virtual void notifyBackwardDisabled() override;
		virtual Cache backward() override;
		virtual void beginGradient() override;
	};
}

#endif