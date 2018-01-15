
/*
	2018.01.15
	Created by AcrylicShrimp.
*/

#include "Vector.h"

namespace CaysNet
{
	void Vector::add(const std::vector<float> &sLeft, const std::vector<float> &sRight, std::vector<float> &sDest)
	{
		assert(sLeft.size() == sRight.size() && sRight.size() == sDest.size());

		for (std::size_t nIndex{0}, nSize{sDest.size()}; nIndex < nSize; ++nIndex)
			sDest[nIndex] = sLeft[nIndex] + sRight[nIndex];
	}

	void Vector::sub(const std::vector<float> &sLeft, const std::vector<float> &sRight, std::vector<float> &sDest)
	{
		assert(sLeft.size() == sRight.size() && sRight.size() == sDest.size());

		for (std::size_t nIndex{0}, nSize{sDest.size()}; nIndex < nSize; ++nIndex)
			sDest[nIndex] = sLeft[nIndex] - sRight[nIndex];
	}

	void Vector::mul(const std::vector<float> &sLeft, const std::vector<float> &sRight, std::vector<float> &sDest)
	{
		assert(sLeft.size() == sRight.size() && sRight.size() == sDest.size());

		for (std::size_t nIndex{0}, nSize{sDest.size()}; nIndex < nSize; ++nIndex)
			sDest[nIndex] = sLeft[nIndex] * sRight[nIndex];
	}

	void Vector::div(const std::vector<float> &sLeft, const std::vector<float> &sRight, std::vector<float> &sDest)
	{
		assert(sLeft.size() == sRight.size() && sRight.size() == sDest.size());

		for (std::size_t nIndex{0}, nSize{sDest.size()}; nIndex < nSize; ++nIndex)
			sDest[nIndex] = sLeft[nIndex] / sRight[nIndex];
	}
}