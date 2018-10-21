
/*
	2018.09.16
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_SPAN_H

#define _CLASS_TINNET_SPAN_H

/*
	TODO : Place the include directives here.
*/


#include <utility>

namespace TinNet
{
	class Span
	{
	private:
		/*
			TODO : Place the class member variable declarations here.
		*/
		
		
	public:
		Span();
		Span(const Span &sSrc);
		Span(Span &&sSrc);
		~Span();
		/*
			TODO : Place the declarations of other constructors here.
		*/
		
		
	public:
		Span &operator=(const Span &sSrc);
		Span &operator=(Span &&sSrc);
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