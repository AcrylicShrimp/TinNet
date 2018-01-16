
/*
	2017.08.16
	Created by AcrylicShrimp.
*/

#ifndef _INTERFACE_TINNET_IO_SERIALIZABLE_H

#define _INTERFACE_TINNET_IO_SERIALIZABLE_H

#include "../TinNetDLL.h"

#include <cstddef>
#include <cstdint>
#include <fstream>
#include <utility>

namespace TinNet::IO
{
	class TINNET_DLL Serializable
	{
	public:
		Serializable() = default;
		Serializable(const Serializable &sSrc) = default;
		Serializable(Serializable &&sSrc) = default;
		~Serializable() = default;

	public:
		Serializable &operator=(const Serializable &sSrc) = default;
		Serializable &operator=(Serializable &&sSrc) = default;

	public:
		virtual void serialize(std::ofstream &sOutput) const = 0;
		virtual void deserialize(std::ifstream &sInput) = 0;

		inline static constexpr bool isLittleEndian();
		template<class DataType> inline static DataType reverse(DataType tValue);
		template<class DataType> inline static DataType toBigEndian(DataType tValue);
		template<class DataType> inline static DataType toLittleEndian(DataType tValue);
		template<class DataType> inline static void write(std::ofstream &sOutput, DataType tValue);
		template<class DataType> inline static DataType read(std::ifstream &sInput);
		static void write(std::ofstream &sOutput, const std::string &sValue);
		static void write(std::ofstream &sOutput, const std::wstring &sValue);
		static std::string readString(std::ifstream &sInput);
		static std::wstring readWideString(std::ifstream &sInput);
	};

	inline constexpr bool Serializable::isLittleEndian()
	{
		static constexpr union
		{
			uint16_t nFirst;
			uint8_t vSecond[2];
		} sEndianness{1};

		return sEndianness.vSecond[0];
	}

	template<class DataType> inline DataType Serializable::reverse(DataType tValue)
	{
		union
		{
			DataType tFirst;
			uint8_t vSecond[sizeof(DataType)];
		} sReverse{tValue};

		for (std::size_t nIndex{0}, nSize{sizeof(DataType) / 2}; nIndex < nSize; ++nIndex)
			std::swap(sReverse.vSecond[nIndex], sReverse.vSecond[sizeof(DataType) - nIndex]);

		return sReverse.tFirst;
	}

	template<class DataType> inline DataType Serializable::toBigEndian(DataType tValue)
	{
		return Serializable::isLittleEndian() ? Serializable::reverse(tValue) : tValue;
	}

	template<class DataType> inline DataType Serializable::toLittleEndian(DataType tValue)
	{
		return Serializable::isLittleEndian() ? tValue : Serializable::reverse(tValue);
	}

	template<class DataType> inline void Serializable::write(std::ofstream &sOutput, DataType tValue)
	{
		union
		{
			DataType tFirst;
			uint8_t vSecond[sizeof(DataType)];
		} sSerialize{Serializable::toLittleEndian(tValue)};

		sOutput.write(reinterpret_cast<const char *>(sSerialize.vSecond), sizeof(DataType));
	}

	template<class DataType> inline DataType Serializable::read(std::ifstream &sInput)
	{
		union
		{
			uint8_t vFirst[sizeof(DataType)];
			DataType tSecond;
		} sDeserialize;

		sInput.read(reinterpret_cast<char *>(sDeserialize.vFirst), sizeof(DataType));

		return Serializable::toLittleEndian(sDeserialize.tSecond);
	}
}

#endif