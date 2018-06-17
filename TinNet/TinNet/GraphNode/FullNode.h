
/*
	2018.06.17
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPHNODE_FULLNODE_H

#define _CLASS_TINNET_GRAPHNODE_FULLNODE_H

#include "../TinNetDLL.h"

#include "../Cache.h"
#include "../CacheContainer.h"
#include "../Graph.h"
#include "BackpropNode.h"

#include <string>

namespace TinNet::GraphNode
{
	class TINNET_DLL FullNode : public BackpropNode
	{
	protected:
		CachePtr pOutput;
		
	public:
		FullNode(Graph *pGraph, const std::string &sName);
		FullNode(const FullNode &sSrc) = delete;
		~FullNode();
		
	public:
		FullNode &operator=(const FullNode &sSrc) = delete;
		
	public:
		virtual std::string type() const override;
		virtual void notifyShapeUpdated() override;
		virtual Cache forward() override;
	};
}

#endif