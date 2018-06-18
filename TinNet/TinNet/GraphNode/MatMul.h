
/*
	2018.06.18
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_GRAPHNODE_MATMUL_H

#define _CLASS_TINNET_GRAPHNODE_MATMUL_H

/*
	TODO : Place the include directives here.
*/


#include <utility>

namespace TinNet::GraphNode
{
	class MatMul
	{
	private:
		/*
			TODO : Place the class member variable declarations here.
		*/
		
		
	public:
		MatMul();
		MatMul(const MatMul &sSrc);
		MatMul(MatMul &&sSrc);
		~MatMul();
		/*
			TODO : Place the declarations of other constructors here.
		*/
		
		
	public:
		MatMul &operator=(const MatMul &sSrc);
		MatMul &operator=(MatMul &&sSrc);
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