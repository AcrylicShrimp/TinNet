
/*
	2017.08.05
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_CAYSNET_ACTIVATIONS_H

#define _CLASS_CAYSNET_ACTIVATIONS_H

#include "../CaysNetDLL.h"

#include "Linear.h"

#include "Sigmoid.h"
#include "TanH.h"

#include "Softmax.h"

#include "ReLU.h"
#include "LReLU.h"
#include "PReLU.h"

#include "../IO/Serializable.h"

#include <fstream>
#include <string>

namespace CaysNet::Activation
{
	class CAYSNET_DLL Activations final
	{
	public:
		Activations() = delete;
		Activations(const Activations &sSrc) = delete;
		Activations(Activations &&sSrc) = delete;
		~Activations() = delete;

	public:
		Activations &operator=(const Activations &sSrc) = delete;
		Activations &operator=(Activations &&sSrc) = delete;

	public:
		static void serialize(Activation *pActivation, std::ofstream &sOutput);
		static Activation *deserialize(std::ifstream &sInput);
		static Activation *createByName(const std::wstring &sActivationName);
	};
}

#endif