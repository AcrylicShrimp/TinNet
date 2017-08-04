
/*
	2017.08.04
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_CAYSNET_ACTIVATION_SIGMOID_H

#define _CLASS_CAYSNET_ACTIVATION_SIGMOID_H

/*
	TODO : Place your include directives here.
*/
#include <utility>

namespace CaysNet::Activation
{
	class Sigmoid
	{
	private:
		/*
			TODO : Place your field declarations here.
		*/
		
		
	public:
		Sigmoid();
		Sigmoid(const Sigmoid &sSrc);
		Sigmoid(Sigmoid &&sSrc);
		~Sigmoid();
		/*
			TODO : Place your other constructors here.
		*/
		
		
	public:
		Sigmoid &operator=(const Sigmoid &sSrc);
		Sigmoid &operator=(Sigmoid &&sSrc);
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