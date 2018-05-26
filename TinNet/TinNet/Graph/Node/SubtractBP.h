
/*
	2018.05.27
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPH_NODE_SUBTRACTBP_H

#define _CLASS_TINNET_GRAPH_NODE_SUBTRACTBP_H

/*
	TODO : Place the include directives here.
*/


#include <utility>

namespace TinNet::Graph::Node
{
	class SubtractBP
	{
	private:
		/*
			TODO : Place the class member variable declarations here.
		*/
		
		
	public:
		SubtractBP();
		SubtractBP(const SubtractBP &sSrc);
		SubtractBP(SubtractBP &&sSrc);
		~SubtractBP();
		/*
			TODO : Place the declarations of other constructors here.
		*/
		
		
	public:
		SubtractBP &operator=(const SubtractBP &sSrc);
		SubtractBP &operator=(SubtractBP &&sSrc);
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