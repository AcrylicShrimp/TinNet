
/*
	2018.06.21
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_IO_JSONOBJECT_H

#define _CLASS_TINNET_IO_JSONOBJECT_H

#include "../TinNetDLL.h"

#include <cstddef>
#include <cstdint>
#include <initializer_list>
#include <map>
#include <string>
#include <utility>
#include <variant>
#include <vector>

namespace TinNet::IO
{
	class TINNET_DLL JSONObject final
	{
	public:
		enum class Type
		{
			Null,
			Bool,
			Number,
			String,
			Object,
			Array
		};

	private:
		Type eType;
		std::variant<void *, bool, std::int64_t, double, std::string, std::map<std::string, JSONObject>, std::vector<JSONObject>> sValue;

	public:
		JSONObject();
		JSONObject(bool bValue);
		JSONObject(std::int64_t nValue);
		JSONObject(double nValue);
		JSONObject(const std::string &sValue);
		JSONObject(std::string &&sValue);
		JSONObject(const JSONObject &sSrc) = default;
		JSONObject(JSONObject &&sSrc) = default;
		JSONObject(const std::vector<JSONObject> &sValue);
		JSONObject(std::vector<JSONObject> &&sValue);
		JSONObject(std::initializer_list<JSONObject> sValue);
		virtual ~JSONObject() = default;

	public:
		bool &operator=(bool bValue);
		std::int64_t &operator=(int64_t nValue);
		double &operator=(double nValue);
		std::string &operator=(const std::string &sValue);
		std::string &operator=(std::string &&sValue);
		JSONObject &operator=(const JSONObject &sSrc) = default;
		JSONObject &operator=(JSONObject &&sSrc) = default;
		JSONObject &operator=(const std::vector<JSONObject> &sValue);
		JSONObject &operator=(std::vector<JSONObject> &&sValue);
		JSONObject &operator=(std::initializer_list<JSONObject> sValue);
		JSONObject &operator[](const std::string &sKey);
		JSONObject &operator[](std::size_t nIndex);
		const JSONObject &operator[](std::size_t nIndex) const;

	public:
		inline Type type() const;
		inline bool isNull() const;
		inline bool isBool() const;
		inline bool isNumber() const;
		inline bool isInteger() const;
		inline bool isDecimal() const;
		inline bool isString() const;
		inline bool isObject() const;
		inline bool isArray() const;
		inline void asNull();
		inline bool &asBool();
		inline std::int64_t &asInteger();
		inline double &asDecimal();
		inline std::string &asString();
		inline JSONObject &asObject();
		inline JSONObject &asArray();
		inline std::size_t length() const;
		void removeNull();
		void remove(const std::string &sKey);
		const JSONObject *obtain(const std::string &sKey) const;
		void push(const JSONObject &sObject);
		void put(const std::string &sKey, const JSONObject &sObject);
	};

	inline JSONObject::Type JSONObject::type() const
	{
		return this->eType;
	}

	inline bool JSONObject::isNull() const
	{
		return this->eType == Type::Null;
	}

	inline bool JSONObject::isBool() const
	{
		return this->eType == Type::Bool;
	}

	inline bool JSONObject::isNumber() const
	{
		return this->eType == Type::Number;
	}

	inline bool JSONObject::isInteger() const
	{
		return std::holds_alternative<std::int64_t>(this->sValue);
	}

	inline bool JSONObject::isDecimal() const
	{
		return std::holds_alternative<double>(this->sValue);
	}

	inline bool JSONObject::isString() const
	{
		return this->eType == Type::String;
	}

	inline bool JSONObject::isObject() const
	{
		return this->eType == Type::Object;
	}

	inline bool JSONObject::isArray() const
	{
		return this->eType == Type::Array;
	}

	inline void JSONObject::asNull()
	{
		if (this->isNull())
			return;

		this->eType = Type::Null;
		this->sValue = nullptr;
	}

	inline bool &JSONObject::asBool()
	{
		if (!this->isBool())
		{
			this->eType = Type::Bool;
			this->sValue = false;
		}

		return std::get<bool>(this->sValue);
	}

	inline std::int64_t &JSONObject::asInteger()
	{
		if (!this->isInteger())
			if (this->isDecimal())
				this->sValue = static_cast<std::int64_t>(this->asDecimal());
			else
			{
				this->eType = Type::Number;
				this->sValue = 0i64;
			}

		return std::get<std::int64_t>(this->sValue);
	}

	inline double &JSONObject::asDecimal()
	{
		if (!this->isDecimal())
			if (this->isInteger())
				this->sValue = static_cast<double>(this->asInteger());
			else
			{
				this->eType = Type::Number;
				this->sValue = .0;
			}

		return std::get<double>(this->sValue);
	}

	inline std::string &JSONObject::asString()
	{
		if (!this->isString())
		{
			this->eType = Type::String;
			this->sValue = "";
		}

		return std::get<std::string>(this->sValue);
	}

	inline JSONObject &JSONObject::asObject()
	{
		if (!this->isObject())
		{
			this->eType = Type::Object;
			this->sValue = std::map<std::string, JSONObject>{};
		}

		return *this;
	}

	inline JSONObject &JSONObject::asArray()
	{
		if (!this->isArray())
		{
			this->eType = Type::Array;
			this->sValue = std::vector<JSONObject>{};
		}

		return *this;
	}

	inline std::size_t JSONObject::length() const
	{
		if (!this->isArray)
			return 0;

		return std::get<std::vector<JSONObject>>(this->sValue).size();
	}
}

#endif