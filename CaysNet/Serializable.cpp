
/*
	2017.08.16
	Created by AcrylicShrimp.
*/

#include "Serializable.h"

namespace CaysNet::IO
{
	void Serializable::write(std::ofstream &sOutput, const std::string &sValue)
	{
		Serializable::write(sOutput, sValue.size());
		sOutput.write(sValue.data(), sValue.size());
	}

	void Serializable::write(std::ofstream &sOutput, const std::wstring &sValue)
	{
		Serializable::write(sOutput, sValue.size());

		for (auto nChar : sValue)
			Serializable::write(sOutput, nChar);
	}

	std::string Serializable::readString(std::ifstream &sInput)
	{
		std::string sValue(Serializable::read<std::string::size_type>(sInput), '\0');
		sInput.read(sValue.data(), sValue.size());

		return sValue;
	}

	std::wstring Serializable::readWideString(std::ifstream &sInput)
	{
		std::wstring sValue(Serializable::read<std::wstring::size_type>(sInput), L'\0');

		for (auto &nChar : sValue)
			nChar = Serializable::read<std::wstring::value_type>(sInput);

		return sValue;
	}
}