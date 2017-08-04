
/*
	2017.08.04
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_CAYSNET_OPTIMIZER_OPTIMIZER_H

#define _CLASS_CAYSNET_OPTIMIZER_OPTIMIZER_H

/*
	TODO : Place your include directives here.
*/
#include <utility>

namespace CaysNet::Optimizer
{
	class Optimizer
	{
	private:
		/*
			TODO : Place your field declarations here.
		*/
		
		
	public:
		Optimizer();
		Optimizer(const Optimizer &sSrc);
		Optimizer(Optimizer &&sSrc);
		~Optimizer();
		/*
			TODO : Place your other constructors here.
		*/
		
		
	public:
		Optimizer &operator=(const Optimizer &sSrc);
		Optimizer &operator=(Optimizer &&sSrc);
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