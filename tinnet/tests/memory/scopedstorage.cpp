
#include "tinnet/includes/memory/ScopedStorage.h"

#include "catch2.hpp"

#include <cstddef>
#include <cstdint>

TEST_CASE("tinnet::memory::ScopedStorage")
{
	SECTION("Alignment")
	{
		for (std::uint64_t nIndex{0}; nIndex < 1024; ++nIndex) {
			tinnet::memory::ScopedStorage sStorage{sizeof(float)};

			CHECK((reinterpret_cast<std::size_t>(sStorage.aligned()) % 32 == 0) == true);
		}
	}
}