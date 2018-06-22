
/*
	2018.06.21
	Created by AcrylicShrimp.
*/

#include "JSONObject.h"

namespace TinNet::IO
{
	JSONObject::JSONObject() :
		eType{Type::Null},
		sValue{nullptr}
	{
		//Empty.
	}

	JSONObject::JSONObject(bool bValue) :
		eType{Type::Bool},
		sValue{bValue}
	{
		//Empty.
	}

	JSONObject::JSONObject(std::int64_t nValue) :
		eType{Type::Number},
		sValue{nValue}
	{
		//Empty.
	}

	JSONObject::JSONObject(double nValue) :
		eType{Type::Number},
		sValue{nValue}
	{
		//Empty.
	}

	JSONObject::JSONObject(const std::string &sValue) :
		eType{Type::String},
		sValue{sValue}
	{
		//Empty.
	}

	JSONObject::JSONObject(std::string &&sValue) :
		eType{Type::String},
		sValue{std::move(sValue)}
	{
		//Empty.
	}

	JSONObject::JSONObject(const std::vector<JSONObject> &sValue) :
		eType{Type::Array},
		sValue{sValue}
	{
		//Empty.
	}

	JSONObject::JSONObject(std::vector<JSONObject> &&sValue) :
		eType{Type::Array},
		sValue{std::move(sValue)}
	{
		//Empty.
	}

	JSONObject::JSONObject(std::initializer_list<JSONObject> sValue) :
		eType{Type::Array},
		sValue{std::vector<JSONObject>(sValue)}
	{
		//Empty.
	}

	bool &JSONObject::operator=(bool bValue)
	{
		return this->asBool() = bValue;
	}

	std::int64_t &JSONObject::operator=(int64_t nValue)
	{
		return this->asInteger() = nValue;
	}

	double &JSONObject::operator=(double nValue)
	{
		return this->asDecimal() = nValue;
	}

	std::string &JSONObject::operator=(const std::string &sValue)
	{
		return this->asString() = sValue;
	}

	std::string &JSONObject::operator=(std::string &&sValue)
	{
		return this->asString() = std::move(sValue);
	}

	JSONObject &JSONObject::operator=(const std::vector<JSONObject> &sValue)
	{
		this->asArray();
		
		std::get<std::vector<JSONObject>>(this->sValue) = sValue;

		return *this;
	}

	JSONObject &JSONObject::operator=(std::vector<JSONObject> &&sValue)
	{
		this->asArray();

		std::get<std::vector<JSONObject>>(this->sValue) = std::move(sValue);

		return *this;
	}

	JSONObject &JSONObject::operator=(std::initializer_list<JSONObject> sValue)
	{
		this->asArray();

		std::get<std::vector<JSONObject>>(this->sValue) = std::vector<JSONObject>(sValue);

		return *this;
	}

	JSONObject &JSONObject::operator[](const std::string &sKey)
	{
		return std::get<std::map<std::string, JSONObject>>(this->sValue)[sKey];
	}

	JSONObject &JSONObject::operator[](std::size_t nIndex)
	{
		return std::get<std::vector<JSONObject>>(this->sValue)[nIndex];
	}

	const JSONObject &JSONObject::operator[](std::size_t nIndex) const
	{
		return std::get<std::vector<JSONObject>>(this->sValue)[nIndex];
	}

	void JSONObject::removeNull()
	{
		if (!this->isObject())
			return;

		auto &sMap{std::get<std::map<std::string, JSONObject>>(this->sValue)};

		for (auto iIndex{sMap.cbegin()}, iEnd{sMap.cend()}; iIndex != iEnd;)
			if (iIndex->second.isNull())
				iIndex = sMap.erase(iIndex);
			else
				++iIndex;
	}

	void JSONObject::remove(const std::string &sKey)
	{
		if (!this->isObject())
			return;

		std::get<std::map<std::string, JSONObject>>(this->sValue).erase(sKey);
	}

	const JSONObject *JSONObject::obtain(const std::string &sKey) const
	{
		if (!this->isObject())
			return nullptr;

		auto &sMap{std::get<std::map<std::string, JSONObject>>(this->sValue)};
		auto iIndex{sMap.find(sKey)};

		return iIndex == sMap.cend() ? nullptr : &iIndex->second;
	}

	void JSONObject::push(const JSONObject &sObject)
	{
		if (!this->isArray())
			return;

		std::get<std::vector<JSONObject>>(this->sValue).emplace_back(sObject);
	}

	void JSONObject::put(const std::string &sKey, const JSONObject &sObject)
	{
		if (!this->isObject())
			return;

		std::get<std::map<std::string, JSONObject>>(this->sValue)[sKey] = sObject;
	}
}