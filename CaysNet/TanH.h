
/*
	2017.08.04
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_CAYSNET_ACTIVATION_TAN_H_H

#define _CLASS_CAYSNET_ACTIVATION_TAN_H_H

/*
	TODO : Place your include directives here.
*/
#include <utility>

namespace CaysNet::Activation
{
	class TanH
	{
	private:
		/*
			TODO : Place your field declarations here.
		*/
		
		
	public:
		TanH();
		TanH(const TanH &sSrc);
		TanH(TanH &&sSrc);
		~TanH();
		/*
			TODO : Place your other constructors here.
		*/
		
		
	public:
		TanH &operator=(const TanH &sSrc);
		TanH &operator=(TanH &&sSrc);
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