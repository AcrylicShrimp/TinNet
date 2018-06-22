
/*
	2018.06.21
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_IO_JSON_H

#define _CLASS_TINNET_IO_JSON_H

#include "../TinNetDLL.h"

#include "JSONObject.h"

#include <cstddef>
#include <string>

namespace TinNet::IO
{
	class TINNET_DLL JSON final
	{
	public:
		JSON() = delete;
		JSON(const JSON &sSrc) = delete;
		~JSON() = delete;
		
	public:
		JSON &operator=(const JSON &sSrc) = delete;
		
	public:
		static JSONObject parse(const std::string &sString);
		static std::string stringify(const JSONObject &sObject);

	private:
		static JSONObject parseNext(const std::string &sString, std::size_t &nIndex, std::size_t nEndIndex);
		static std::string parseString(const std::string &sString, std::size_t &nIndex, std::size_t nEndIndex);
	};
}

#endif