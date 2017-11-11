
/*
	2017.08.16
	Created by AcrylicShrimp.
*/

#include "Activations.h"

namespace CaysNet::Activation
{
	void Activations::serialize(Activation *pActivation, std::ofstream &sOutput)
	{
		IO::Serializable::write(sOutput, pActivation != nullptr);

		if (!pActivation)
			return;

		IO::Serializable::write(sOutput, std::wstring(pActivation->name()));
		pActivation->serialize(sOutput);
	}

	Activation *Activations::deserialize(std::ifstream &sInput)
	{
		if (!IO::Serializable::read<bool>(sInput))
			return nullptr;

		auto pActivation{Activations::createByName(IO::Serializable::readWideString(sInput))};

		if (pActivation)
			pActivation->deserialize(sInput);

		return pActivation;
	}

	Activation *Activations::createByName(const std::wstring &sActivationName)
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
			return new PReLU(.0f);
		else
			return nullptr;
	}
}