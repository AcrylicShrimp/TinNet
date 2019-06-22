
/*
	2019.06.21
	Created by AcrylicShrimp.
*/

#include <catch2/catch.hpp>
#include <TinNet/TinNet.h>

#include <cstddef>
#include <cstdint>
#include <initializer_list>
#include <limits>
#include <vector>

using T = TinNet::Core::Shape;

TEST_CASE("TinNet::Core::Shape")
{
	SECTION("Ctors")
	{
		SECTION("Static")
		{
			REQUIRE(T{}.rank() == 0);
			REQUIRE(T{}.size() == 1);
			REQUIRE(T{1}.rank() == 1);
			REQUIRE(T{1}.size() == 1);
			REQUIRE(T{1, 2}.rank() == 2);
			REQUIRE(T{1, 2}.size() == 1 * 2);
			REQUIRE(T{1, 2, 3}.rank() == 3);
			REQUIRE(T{1, 2, 3}.size() == 1 * 2 * 3);
			REQUIRE(T{1, 2, 3, 4}.rank() == 4);
			REQUIRE(T{1, 2, 3, 4}.size() == 1 * 2 * 3 * 4);
			REQUIRE(T{1, 2, 3, 4, 5}.rank() == 5);
			REQUIRE(T{1, 2, 3, 4, 5}.size() == 1 * 2 * 3 * 4 * 5);
			REQUIRE(T{1, 2, 3, 4, 5, 6}.rank() == 6);
			REQUIRE(T{1, 2, 3, 4, 5, 6}.size() == 1 * 2 * 3 * 4 * 5 * 6);
		}

		SECTION("Dynamic")
		{
			const auto nNum{GENERATE(0, 1, 2, 3, 4, 5, 6, take(10, random(7, 4096)))};

			std::vector<std::size_t> sDimensionList(nNum);

			for (std::size_t nIndex{0}; nIndex < nNum; ++nIndex)
				sDimensionList[nIndex] = nIndex + 1;

			std::size_t nSize{1};

			for (auto nAxis : sDimensionList)
				nSize *= nAxis;

			REQUIRE(T{sDimensionList.cbegin(), sDimensionList.cend()}.rank() == nNum);
			REQUIRE(T{sDimensionList.cbegin(), sDimensionList.cend()}.size() == nSize);
		}
	}

	SECTION("Copy Ctor")
	{
		SECTION("Static")
		{
			REQUIRE(T{static_cast<const T &>(T{})}.rank() == 0);
			REQUIRE(T{static_cast<const T &>(T{})}.size() == 1);
			REQUIRE(T{static_cast<const T &>(T{1})}.rank() == 1);
			REQUIRE(T{static_cast<const T &>(T{1})}.size() == 1);
			REQUIRE(T{static_cast<const T &>(T{1})}.rank() == 1);
			REQUIRE(T{static_cast<const T &>(T{1})}.size() == 1);

			REQUIRE(T{static_cast<const T &>(T{})}.rank() == 0);
			REQUIRE(T{static_cast<const T &>(T{})}.size() == 1);
			REQUIRE(T{static_cast<const T &>(T{1})}.rank() == 1);
			REQUIRE(T{static_cast<const T &>(T{1})}.size() == 1);
			REQUIRE(T{static_cast<const T &>(T{1, 2})}.rank() == 2);
			REQUIRE(T{static_cast<const T &>(T{1, 2})}.size() == 1 * 2);
			REQUIRE(T{static_cast<const T &>(T{1, 2, 3})}.rank() == 3);
			REQUIRE(T{static_cast<const T &>(T{1, 2, 3})}.size() == 1 * 2 * 3);
			REQUIRE(T{static_cast<const T &>(T{1, 2, 3, 4})}.rank() == 4);
			REQUIRE(T{static_cast<const T &>(T{1, 2, 3, 4})}.size() == 1 * 2 * 3 * 4);
			REQUIRE(T{static_cast<const T &>(T{1, 2, 3, 4, 5})}.rank() == 5);
			REQUIRE(T{static_cast<const T &>(T{1, 2, 3, 4, 5})}.size() == 1 * 2 * 3 * 4 * 5);
			REQUIRE(T{static_cast<const T &>(T{1, 2, 3, 4, 5, 6})}.rank() == 6);
			REQUIRE(T{static_cast<const T &>(T{1, 2, 3, 4, 5, 6})}.size() == 1 * 2 * 3 * 4 * 5 * 6);
		}

		SECTION("Dynamic")
		{
			const auto nNum{GENERATE(0, 1, 2, 3, 4, 5, 6, take(10, random(7, 4096)))};

			std::vector<std::size_t> sDimensionList(nNum);

			for (std::size_t nIndex{0}; nIndex < nNum; ++nIndex)
				sDimensionList[nIndex] = nIndex + 1;

			std::size_t nSize{1};

			for (auto nAxis : sDimensionList)
				nSize *= nAxis;

			REQUIRE(T{static_cast<const T &>(T{sDimensionList.cbegin(), sDimensionList.cend()})}.rank() == nNum);
			REQUIRE(T{static_cast<const T &>(T{sDimensionList.cbegin(), sDimensionList.cend()})}.size() == nSize);
		}
	}

	SECTION("Move Ctor")
	{
		SECTION("Static")
		{
			REQUIRE(T{T{}}.rank() == 0);
			REQUIRE(T{T{}}.size() == 1);
			REQUIRE(T{T{1}}.rank() == 1);
			REQUIRE(T{T{1}}.size() == 1);
			REQUIRE(T{T{1}}.rank() == 1);
			REQUIRE(T{T{1}}.size() == 1);

			REQUIRE(T{T{}}.rank() == 0);
			REQUIRE(T{T{}}.size() == 1);
			REQUIRE(T{T{1}}.rank() == 1);
			REQUIRE(T{T{1}}.size() == 1);
			REQUIRE(T{T{1, 2}}.rank() == 2);
			REQUIRE(T{T{1, 2}}.size() == 1 * 2);
			REQUIRE(T{T{1, 2, 3}}.rank() == 3);
			REQUIRE(T{T{1, 2, 3}}.size() == 1 * 2 * 3);
			REQUIRE(T{T{1, 2, 3, 4}}.rank() == 4);
			REQUIRE(T{T{1, 2, 3, 4}}.size() == 1 * 2 * 3 * 4);
			REQUIRE(T{T{1, 2, 3, 4, 5}}.rank() == 5);
			REQUIRE(T{T{1, 2, 3, 4, 5}}.size() == 1 * 2 * 3 * 4 * 5);
			REQUIRE(T{T{1, 2, 3, 4, 5, 6}}.rank() == 6);
			REQUIRE(T{T{1, 2, 3, 4, 5, 6}}.size() == 1 * 2 * 3 * 4 * 5 * 6);
		}

		SECTION("Dynamic")
		{
			const auto nNum{GENERATE(0, 1, 2, 3, 4, 5, 6, take(10, random(7, 4096)))};

			std::vector<std::size_t> sDimensionList(nNum);

			for (std::size_t nIndex{0}; nIndex < nNum; ++nIndex)
				sDimensionList[nIndex] = nIndex + 1;

			std::size_t nSize{1};

			for (auto nAxis : sDimensionList)
				nSize *= nAxis;

			REQUIRE(T{T{sDimensionList.cbegin(), sDimensionList.cend()}}.rank() == nNum);
			REQUIRE(T{T{sDimensionList.cbegin(), sDimensionList.cend()}}.size() == nSize);
		}
	}

	SECTION("Assignment")
	{
		REQUIRE((T{} = {}).rank() == 0);
		REQUIRE((T{} = {}).size() == 1);
		REQUIRE((T{} = {1}).rank() == 1);
		REQUIRE((T{} = {1}).size() == 1);
		REQUIRE((T{} = {1, 2}).rank() == 2);
		REQUIRE((T{} = {1, 2}).size() == 1 * 2);
		REQUIRE((T{} = {1, 2, 3}).rank() == 3);
		REQUIRE((T{} = {1, 2, 3}).size() == 1 * 2 * 3);
		REQUIRE((T{} = {1, 2, 3, 4}).rank() == 4);
		REQUIRE((T{} = {1, 2, 3, 4}).size() == 1 * 2 * 3 * 4);
		REQUIRE((T{} = {1, 2, 3, 4, 5}).rank() == 5);
		REQUIRE((T{} = {1, 2, 3, 4, 5}).size() == 1 * 2 * 3 * 4 * 5);
		REQUIRE((T{} = {1, 2, 3, 4, 5, 6}).rank() == 6);
		REQUIRE((T{} = {1, 2, 3, 4, 5, 6}).size() == 1 * 2 * 3 * 4 * 5 * 6);
	}

	SECTION("Copy Assignment")
	{
		SECTION("Static")
		{
			REQUIRE((T{} = static_cast<const T &>(T{})).rank() == 0);
			REQUIRE((T{} = static_cast<const T &>(T{})).size() == 1);
			REQUIRE((T{} = static_cast<const T &>(T{1})).rank() == 1);
			REQUIRE((T{} = static_cast<const T &>(T{1})).size() == 1);
			REQUIRE((T{} = static_cast<const T &>(T{1, 2})).rank() == 2);
			REQUIRE((T{} = static_cast<const T &>(T{1, 2})).size() == 1 * 2);
			REQUIRE((T{} = static_cast<const T &>(T{1, 2, 3})).rank() == 3);
			REQUIRE((T{} = static_cast<const T &>(T{1, 2, 3})).size() == 1 * 2 * 3);
			REQUIRE((T{} = static_cast<const T &>(T{1, 2, 3, 4})).rank() == 4);
			REQUIRE((T{} = static_cast<const T &>(T{1, 2, 3, 4})).size() == 1 * 2 * 3 * 4);
			REQUIRE((T{} = static_cast<const T &>(T{1, 2, 3, 4, 5})).rank() == 5);
			REQUIRE((T{} = static_cast<const T &>(T{1, 2, 3, 4, 5})).size() == 1 * 2 * 3 * 4 * 5);
			REQUIRE((T{} = static_cast<const T &>(T{1, 2, 3, 4, 5, 6})).rank() == 6);
			REQUIRE((T{} = static_cast<const T &>(T{1, 2, 3, 4, 5, 6})).size() == 1 * 2 * 3 * 4 * 5 * 6);
		}

		SECTION("Dynamic")
		{
			const auto nNum{GENERATE(0, 1, 2, 3, 4, 5, 6, take(10, random(7, 4096)))};

			std::vector<std::size_t> sDimensionList(nNum);

			for (std::size_t nIndex{0}; nIndex < nNum; ++nIndex)
				sDimensionList[nIndex] = nIndex + 1;

			std::size_t nSize{1};

			for (auto nAxis : sDimensionList)
				nSize *= nAxis;

			REQUIRE((T{} = static_cast<const T &>(T{sDimensionList.cbegin(), sDimensionList.cend()})).rank() == nNum);
			REQUIRE((T{} = static_cast<const T &>(T{sDimensionList.cbegin(), sDimensionList.cend()})).size() == nSize);
		}
	}

	SECTION("Move Assignment")
	{
		SECTION("Static")
		{
			REQUIRE((T{} = T{}).rank() == 0);
			REQUIRE((T{} = T{}).size() == 1);
			REQUIRE((T{} = T{1}).rank() == 1);
			REQUIRE((T{} = T{1}).size() == 1);
			REQUIRE((T{} = T{1, 2}).rank() == 2);
			REQUIRE((T{} = T{1, 2}).size() == 1 * 2);
			REQUIRE((T{} = T{1, 2, 3}).rank() == 3);
			REQUIRE((T{} = T{1, 2, 3}).size() == 1 * 2 * 3);
			REQUIRE((T{} = T{1, 2, 3, 4}).rank() == 4);
			REQUIRE((T{} = T{1, 2, 3, 4}).size() == 1 * 2 * 3 * 4);
			REQUIRE((T{} = T{1, 2, 3, 4, 5}).rank() == 5);
			REQUIRE((T{} = T{1, 2, 3, 4, 5}).size() == 1 * 2 * 3 * 4 * 5);
			REQUIRE((T{} = T{1, 2, 3, 4, 5, 6}).rank() == 6);
			REQUIRE((T{} = T{1, 2, 3, 4, 5, 6}).size() == 1 * 2 * 3 * 4 * 5 * 6);
		}

		SECTION("Dynamic")
		{
			const auto nNum{GENERATE(0, 1, 2, 3, 4, 5, 6, take(10, random(7, 4096)))};

			std::vector<std::size_t> sDimensionList(nNum);

			for (std::size_t nIndex{0}; nIndex < nNum; ++nIndex)
				sDimensionList[nIndex] = nIndex + 1;

			std::size_t nSize{1};

			for (auto nAxis : sDimensionList)
				nSize *= nAxis;

			REQUIRE((T{} = T{sDimensionList.cbegin(), sDimensionList.cend()}).rank() == nNum);
			REQUIRE((T{} = T{sDimensionList.cbegin(), sDimensionList.cend()}).size() == nSize);
		}
	}


}