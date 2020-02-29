
#include "catch2.hpp"
#include "tinnet/includes/node/Builder.h"
#include "tinnet/includes/node/Shape.h"
#include "tinnet/tests/helper/Random.h"

#include <cstddef>

TEST_CASE("tinnet::node::kernel::BasicArithmetic neg")
{
	auto nLength{tinnet::test::helper::Random::genIndex()};

	auto sNode{tinnet::test::helper::Random::genData(nLength)};
	auto pNode{tinnet::node::Builder::memory(tinnet::node::Shape{{nLength}}, sNode.data(), true)};
	auto pResult{-pNode};

	SECTION("Check forward")
	{
		for (std::size_t nIndex{0}; nIndex < nLength; ++nIndex)
			CHECK(pResult->output().aligned<float>()[nIndex] == Approx(-pNode->output().aligned<float>()[nIndex]));
	}

	pResult->computeGradient();

	SECTION("Check backward")
	{
		for (std::size_t nIndex{0}; nIndex < nLength; ++nIndex)
			CHECK(pNode->gradient().aligned<float>()[nIndex] == Approx(-1.f));
	}
}