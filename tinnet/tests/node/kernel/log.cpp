
#include "catch2.hpp"
#include "tinnet/includes/node/Builder.h"
#include "tinnet/includes/node/Shape.h"
#include "tinnet/tests/helper/Random.h"

#include <cmath>
#include <cstddef>

TEST_CASE("tinnet::node::kernel::MathFunction log")
{
	auto nLength{tinnet::test::helper::Random::genIndex()};

	auto sNode{tinnet::test::helper::Random::genPositiveData(nLength)};
	auto pNode{tinnet::node::Builder::memory(tinnet::node::Shape{{nLength}}, sNode.data(), true)};
	auto pResult{tinnet::node::Builder::log(pNode)};

	SECTION("Check forward")
	{
		for (std::size_t nIndex{0}; nIndex < nLength; ++nIndex)
			CHECK(
				pResult->output().aligned<float>()[nIndex]
				== Approx(std::log(pNode->output().aligned<float>()[nIndex] + 1e-5f)));
	}

	pResult->computeGradient();

	SECTION("Check backward")
	{
		for (std::size_t nIndex{0}; nIndex < nLength; ++nIndex)
			CHECK(
				pNode->gradient().aligned<float>()[nIndex]
				== Approx(1.f / (pNode->output().aligned<float>()[nIndex] + 1e-5f)));
	}
}