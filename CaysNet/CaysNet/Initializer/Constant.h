
/*
	2017.08.05
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_CAYSNET_INITIALIZER_CONSTANT_H

#define _CLASS_CAYSNET_INITIALIZER_CONSTANT_H

#include "../CaysNetDLL.h"

#include "../Layer.h"

namespace CaysNet::Initializer
{
	class CAYSNET_DLL Constant final
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
		void initializeBias(Layer &sLayer) const;
		void initializeWeight(Layer &sLayer) const;
	};
}

#endif