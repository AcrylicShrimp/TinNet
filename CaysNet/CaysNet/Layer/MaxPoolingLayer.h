
/*
	2017.11.03
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_CAYSNET_LAYER_MAX_POOLING_LAYER_H

#define _CLASS_CAYSNET_LAYER_MAX_POOLING_LAYER_H

/*
	TODO : Place your include directives here.
*/
#include <utility>

namespace CaysNet::Layer
{
	class MaxPoolingLayer
	{
	private:
		/*
			TODO : Place your field declarations here.
		*/
		
		
	public:
		MaxPoolingLayer();
		MaxPoolingLayer(const MaxPoolingLayer &sSrc);
		MaxPoolingLayer(MaxPoolingLayer &&sSrc);
		~MaxPoolingLayer();
		/*
			TODO : Place your other constructors here.
		*/
		
		
	public:
		MaxPoolingLayer &operator=(const MaxPoolingLayer &sSrc);
		MaxPoolingLayer &operator=(MaxPoolingLayer &&sSrc);
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