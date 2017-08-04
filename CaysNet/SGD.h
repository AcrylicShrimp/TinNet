
/*
	2017.08.04
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_CAYSNET_OPTIMIZER_SGD_H

#define _CLASS_CAYSNET_OPTIMIZER_SGD_H

/*
	TODO : Place your include directives here.
*/
#include <utility>

namespace CaysNet::Optimizer
{
	class SGD
	{
	private:
		/*
			TODO : Place your field declarations here.
		*/
		
		
	public:
		SGD();
		SGD(const SGD &sSrc);
		SGD(SGD &&sSrc);
		~SGD();
		/*
			TODO : Place your other constructors here.
		*/
		
		
	public:
		SGD &operator=(const SGD &sSrc);
		SGD &operator=(SGD &&sSrc);
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