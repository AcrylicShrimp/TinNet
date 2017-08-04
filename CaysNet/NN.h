
/*
	2017.08.04
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_CAYSNET_NN_H

#define _CLASS_CAYSNET_NN_H

/*
	TODO : Place your include directives here.
*/
#include <utility>

namespace CaysNet
{
	class NN final
	{
	private:
		/*
			TODO : Place your field declarations here.
		*/
		
		
	public:
		NN();
		NN(const NN &sSrc);
		NN(NN &&sSrc);
		~NN();
		/*
			TODO : Place your other constructors here.
		*/
		
		
	public:
		NN &operator=(const NN &sSrc);
		NN &operator=(NN &&sSrc);
		/*
			TODO : Place your other operator overloadings here.
		*/
		
		
	public:
		template<class Activation> NN &addLayer();
	};
}

#endif