
/*
	2018.01.15
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_CAYSNET_VECTOR_H

#define _CLASS_CAYSNET_VECTOR_H

#include <cassert>
#include <cstddef>
#include <vector>

namespace CaysNet
{
	class Vector final
	{
	public:
		Vector() = delete;
		Vector(const Vector &sSrc) = delete;
		~Vector() = delete;
		
	public:
		Vector &operator=(const Vector &sSrc) = delete;
		
	public:
		static void add(const std::vector<float> &sLeft, const std::vector<float> &sRight, std::vector<float> &sDest);
		static void sub(const std::vector<float> &sLeft, const std::vector<float> &sRight, std::vector<float> &sDest);
		static void mul(const std::vector<float> &sLeft, const std::vector<float> &sRight, std::vector<float> &sDest);
		static void div(const std::vector<float> &sLeft, const std::vector<float> &sRight, std::vector<float> &sDest);
	};
}

#endif