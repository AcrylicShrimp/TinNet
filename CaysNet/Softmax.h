
/*
	2017.08.04
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_CAYSNET_ACTIVATION_SOFTMAX_H

#define _CLASS_CAYSNET_ACTIVATION_SOFTMAX_H

/*
	TODO : Place your include directives here.
*/
#include <utility>

namespace CaysNet::Activation
{
	class Softmax
	{
	private:
		/*
			TODO : Place your field declarations here.
		*/
		
		
	public:
		Softmax();
		Softmax(const Softmax &sSrc);
		Softmax(Softmax &&sSrc);
		~Softmax();
		/*
			TODO : Place your other constructors here.
		*/
		
		
	public:
		Softmax &operator=(const Softmax &sSrc);
		Softmax &operator=(Softmax &&sSrc);
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