
#include "catch2.hpp"
#include "tinnet/includes/node/Builder.h"
#include "tinnet/includes/node/Shape.h"
#include "tinnet/tests/helper/Random.h"

#include <cstddef>

TEST_CASE("tinnet::node::kernel::NNFunction relu")
{
	auto nLength{tinnet::test::helper::Random::genIndex()};

	auto sNode{tinnet::test::helper::Random::genData(nLength)};
	auto pNode{tinnet::node::Builder::memory(tinnet::node::Shape{{nLength}}, sNode.data(), true)};
	auto pResult{tinnet::node::Builder::relu(pNode, .1f)};

	SECTION("Check forward")
	{
		auto fRectify{[](float nV, float nA) {
			return nV < .0f ? nA * nV : nV;
		}};

		for (std::size_t nIndex{0}; nIndex < nLength; ++nIndex)
			CHECK(
				pResult->output().aligned<float>()[nIndex]
				== Approx(fRectify(pNode->output().aligned<float>()[nIndex], .1f)));
	}

	pResult->computeGradient();

	SECTION("Check backward")
	{
		auto fRectify{[](float nV, float nA) {
			return nV < .0f ? nA : 1.f;
		}};

		for (std::size_t nIndex{0}; nIndex < nLength; ++nIndex)
			CHECK(
				pNode->gradient().aligned<float>()[nIndex]
				== Approx(fRectify(pNode->output().aligned<float>()[nIndex], .1f)));
	}
}