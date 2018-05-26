
/*
	2018.05.27
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPH_NODE_MULTIPLYBP_H

#define _CLASS_TINNET_GRAPH_NODE_MULTIPLYBP_H

/*
	TODO : Place the include directives here.
*/


#include <utility>

namespace TinNet::Graph::Node
{
	class MultiplyBP
	{
	private:
		/*
			TODO : Place the class member variable declarations here.
		*/
		
		
	public:
		MultiplyBP();
		MultiplyBP(const MultiplyBP &sSrc);
		MultiplyBP(MultiplyBP &&sSrc);
		~MultiplyBP();
		/*
			TODO : Place the declarations of other constructors here.
		*/
		
		
	public:
		MultiplyBP &operator=(const MultiplyBP &sSrc);
		MultiplyBP &operator=(MultiplyBP &&sSrc);
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