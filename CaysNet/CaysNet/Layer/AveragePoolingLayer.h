
/*
	2017.11.03
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_CAYSNET_LAYER_AVERAGE_POOLING_LAYER_H

#define _CLASS_CAYSNET_LAYER_AVERAGE_POOLING_LAYER_H

/*
	TODO : Place your include directives here.
*/
#include <utility>

namespace CaysNet::Layer
{
	class AveragePoolingLayer
	{
	private:
		/*
			TODO : Place your field declarations here.
		*/
		
		
	public:
		AveragePoolingLayer();
		AveragePoolingLayer(const AveragePoolingLayer &sSrc);
		AveragePoolingLayer(AveragePoolingLayer &&sSrc);
		~AveragePoolingLayer();
		/*
			TODO : Place your other constructors here.
		*/
		
		
	public:
		AveragePoolingLayer &operator=(const AveragePoolingLayer &sSrc);
		AveragePoolingLayer &operator=(AveragePoolingLayer &&sSrc);
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