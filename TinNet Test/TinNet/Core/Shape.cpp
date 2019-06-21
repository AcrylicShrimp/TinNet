
/*
	2019.06.21
	Created by AcrylicShrimp.
*/

#include <catch2/catch.hpp>
#include <TinNet/TinNet.h>

TEST_CASE("TinNet::Core::Shape")
{
	TinNet::Core::Shape sShape;

	REQUIRE(sShape.rank() == 0);
}