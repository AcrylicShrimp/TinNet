
#include "catch2.hpp"
#include "tinnet/includes/node/Builder.h"
#include "tinnet/includes/node/Shape.h"

#include <cstddef>
#include <cstdint>
#include <limits>
#include <vector>

TEST_CASE("tinnet::node::kernel::Add")
{
	SECTION("Epoch")
	{
		std::size_t nLength{GENERATE(take(4u, random(1u, 8192u)))};

		std::vector<float> sLeft;
		std::vector<float> sRight;

		sLeft.reserve(nLength);
		sRight.reserve(nLength);

		SECTION("Fill left")
		{
			sLeft.emplace_back(GENERATE_COPY(
				take(nLength, random(std::numeric_limits<float>::min(), std::numeric_limits<float>::max()))));
		}
		SECTION("Fill right")
		{
			sLeft.emplace_back(GENERATE_COPY(
				take(nLength, random(std::numeric_limits<float>::min(), std::numeric_limits<float>::max()))));
		}

		auto pLeft{tinnet::node::Builder::memory(tinnet::node::Shape{{nLength}}, sLeft.data(), true)};
		auto pRight{tinnet::node::Builder::memory(tinnet::node::Shape{{nLength}}, sRight.data(), true)};
		auto pResult{pLeft + pRight};

		SECTION("Check forward")
		{
			std::size_t nIndex{GENERATE_COPY(range(static_cast<std::size_t>(0u), nLength))};

			CHECK(pResult->output().aligned<float>()[nIndex] == Approx(sLeft[nIndex] + sRight[nIndex]));
		}

		pResult->computeGradient();

		SECTION("Check backward")
		{
			std::size_t nIndex{GENERATE_COPY(range(static_cast<std::size_t>(0u), nLength))};

			CHECK(pLeft->gradient().aligned<float>()[nIndex] == Approx(1.f));
			CHECK(pRight->gradient().aligned<float>()[nIndex] == Approx(1.f));
		}
	}
}