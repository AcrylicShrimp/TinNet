
/*
	2017.08.05
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_INITIALIZER_CONSTANT_H

#define _CLASS_TINNET_INITIALIZER_CONSTANT_H

#include "../TinNetDLL.h"

namespace TinNet::Initializer
{
	class TINNET_DLL Constant final
	{
	private:
		float nConstant;

	public:
		Constant(float nNewConstant);
		Constant(const Constant &sSrc);
		~Constant() = default;

	public:
		Constant &operator=(const Constant &sSrc);

	public:
		//void initializeBias(Layer::LayerBase &sLayer) const;
		//void initializeWeight(Layer::LayerBase &sLayer) const;
	};
}

#endif