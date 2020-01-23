
#ifndef _TINNET_TEST_HELPER_RANDOM_H

#define _TINNET_TEST_HELPER_RANDOM_H

#include <cstddef>
#include <functional>
#include <random>
#include <vector>

namespace tinnet::test::helper {
	class Random final {
	public:
		Random()		   = delete;
		~Random() noexcept = delete;

	public:
		static std::vector<float> genPositiveData(std::size_t nLength)
		{
			std::mt19937						  sMT{std::random_device{}()};
			std::uniform_real_distribution<float> sDist{.0f, 1024.f};

			std::vector<float> sResult(nLength, .0f);

			for (auto &nElement: sResult) nElement = sDist(sMT);

			return sResult;
		}

		static std::vector<float> genData(std::size_t nLength)
		{
			std::mt19937						  sMT{std::random_device{}()};
			std::uniform_real_distribution<float> sDist{-1024.f, 1024.f};

			std::vector<float> sResult(nLength, .0f);

			for (auto &nElement: sResult) nElement = sDist(sMT);

			return sResult;
		}

		static std::size_t genIndex()
		{
			std::mt19937							   sMT{std::random_device{}()};
			std::uniform_int_distribution<std::size_t> sDist{1, 128};

			return sDist(sMT);
		}

		static void loopIndex(std::size_t nMaxIndex, const std::function<void(std::size_t)> &fFunc)
		{
			for (std::size_t nIndex{0}; nIndex < nMaxIndex; ++nIndex) fFunc(nIndex);
		}
	};
}	 // namespace tinnet::test::helper

#endif