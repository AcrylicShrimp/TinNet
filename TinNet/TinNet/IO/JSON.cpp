
/*
	2018.06.21
	Created by AcrylicShrimp.
*/

#include "JSON.h"

namespace TinNet::IO
{
	JSONObject JSON::parse(const std::string &sString)
	{
		return {};
	}

	std::string JSON::stringify(const JSONObject &sObject)
	{
		return "";
	}

	JSONObject JSON::parseNext(const std::string &sString, std::size_t &nIndex, std::size_t nEndIndex)
	{
		return {};
	}

	std::string JSON::parseString(const std::string &sString, std::size_t &nIndex, std::size_t nEndIndex)
	{
		if (nIndex >= nEndIndex || sString[nIndex] != '"')
			return "";

		std::string sResult;

		for (++nIndex; nIndex < nEndIndex && sString[nIndex] != '"'; ++nIndex)
		{
			//if (sString[nIndex])
		}

		if (nIndex < nEndIndex && sString[nIndex] == '"')
			++nIndex;

		return sResult;
	}
}