
/*
	2018.01.19
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_LAYER_FULLLAYER_GPU_H

#define _CLASS_TINNET_LAYER_FULLLAYER_GPU_H

#include "../../../TinNet/TinNet/TinNetDLL.h"

#include <utility>

namespace TinNet::Layer
{
	class FullLayer_GPU
	{
	private:
		/*
			TODO : Place the class member variable declarations here.
		*/
		
		
	public:
		FullLayer_GPU();
		FullLayer_GPU(const FullLayer_GPU &sSrc);
		FullLayer_GPU(FullLayer_GPU &&sSrc);
		~FullLayer_GPU();
		/*
			TODO : Place the declarations of other constructors here.
		*/
		
		
	public:
		FullLayer_GPU &operator=(const FullLayer_GPU &sSrc);
		FullLayer_GPU &operator=(FullLayer_GPU &&sSrc);
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