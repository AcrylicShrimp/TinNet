
/*
	2017.08.20
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_CAYSNET_OPTIMIZER_SUPERVISED_NAG_H

#define _CLASS_CAYSNET_OPTIMIZER_SUPERVISED_NAG_H

/*
	TODO : Place your include directives here.
*/
#include <utility>

namespace CaysNet::Optimizer::Supervised
{
	class NAG
	{
	private:
		/*
			TODO : Place your field declarations here.
		*/
		
		
	public:
		NAG();
		NAG(const NAG &sSrc);
		NAG(NAG &&sSrc);
		~NAG();
		/*
			TODO : Place your other constructors here.
		*/
		
		
	public:
		NAG &operator=(const NAG &sSrc);
		NAG &operator=(NAG &&sSrc);
		/*
			TODO : Place your other operator overloadings here.
		*/
		
		
	public:
		/*
			TODO : Place your member function declarations here.
		*/
		
	};
}

#endif