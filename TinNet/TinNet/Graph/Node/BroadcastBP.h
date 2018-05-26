
/*
	2018.05.27
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPH_NODE_BROADCASTBP_H

#define _CLASS_TINNET_GRAPH_NODE_BROADCASTBP_H

/*
	TODO : Place the include directives here.
*/


#include <utility>

namespace TinNet::Graph::Node
{
	class BroadcastBP
	{
	private:
		/*
			TODO : Place the class member variable declarations here.
		*/
		
		
	public:
		BroadcastBP();
		BroadcastBP(const BroadcastBP &sSrc);
		BroadcastBP(BroadcastBP &&sSrc);
		~BroadcastBP();
		/*
			TODO : Place the declarations of other constructors here.
		*/
		
		
	public:
		BroadcastBP &operator=(const BroadcastBP &sSrc);
		BroadcastBP &operator=(BroadcastBP &&sSrc);
		/*
			TODO : Place other operator overloadings here.
		*/
		
		
	public:
		/*
			TODO : Place the member function declarations here.
		*/
		
	};
}

#endif