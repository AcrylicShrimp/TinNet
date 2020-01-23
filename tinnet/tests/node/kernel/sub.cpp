
#include "catch2.hpp"
#include "tinnet/includes/node/Builder.h"
#include "tinnet/includes/node/Shape.h"
#include "tinnet/tests/helper/Random.h"

#include <cstddef>

TEST_CASE("tinnet::node::kernel::BasicArithmetic sub")
{
	std::size_t nLength{tinnet::test::helper::Random::genIndex()};

	auto sLeft{tinnet::test::helper::Random::genData(nLength)};
	auto sRight{tinnet::test::helper::Random::genData(nLength)};

	auto pLeft{tinnet::node::Builder::memory(tinnet::node::Shape{{nLength}}, sLeft.data(), true)};
	auto pRight{tinnet::node::Builder::memory(tinnet::node::Shape{{nLength}}, sRight.data(), true)};
	auto pResult{pLeft - pRight};

	SECTION("Check forward")
	{
		for (std::size_t nIndex{0}; nIndex < nLength; ++nIndex)
			CHECK(pResult->output().aligned<float>()[nIndex] == Approx(sLeft[nIndex] - sRight[nIndex]));
	}

	pResult->computeGradient();

	SECTION("Check backward")
	{
		for (std::size_t nIndex{0}; nIndex < nLength; ++nIndex) {
			CHECK(pLeft->gradient().aligned<float>()[nIndex] == Approx(1.f));
			CHECK(pRight->gradient().aligned<float>()[nIndex] == Approx(-1.f));
		}
	}
}