
/*
	2017.08.16
	Created by AcrylicShrimp.
*/

#include "Activations.h"

namespace CaysNet::Activation
{
	Activation *Activations::createByName(const std::wstring &sActivationName, std::ifstream &sInput)
	{
		using namespace std::literals::string_literals;

		if (sActivationName == L"Linear"s)
			return new Linear();
		else if (sActivationName == L"Sigmoid"s)
			return new Sigmoid();
		else if (sActivationName == L"TanH"s)
			return new TanH();
		else if (sActivationName == L"Softmax"s)
			return new Softmax();
		else if (sActivationName == L"ReLU"s)
			return new ReLU();
		else if (sActivationName == L"LReLU"s)
			return new LReLU();
		else if (sActivationName == L"PReLU"s)
			return new PReLU(IO::Serializable::read<float>(sInput));
		else
			return nullptr;
	}
}