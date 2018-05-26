
/*
	2018.05.27
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPH_NODE_DIVIDEBP_H

#define _CLASS_TINNET_GRAPH_NODE_DIVIDEBP_H

/*
	TODO : Place the include directives here.
*/


#include <utility>

namespace TinNet::Graph::Node
{
	class DivideBP
	{
	private:
		/*
			TODO : Place the class member variable declarations here.
		*/
		
		
	public:
		DivideBP();
		DivideBP(const DivideBP &sSrc);
		DivideBP(DivideBP &&sSrc);
		~DivideBP();
		/*
			TODO : Place the declarations of other constructors here.
		*/
		
		
	public:
		DivideBP &operator=(const DivideBP &sSrc);
		DivideBP &operator=(DivideBP &&sSrc);
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