
/*
	2019.03.17
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_INITIALIZER_XAVIER_H

#define _CLASS_TINNET_INITIALIZER_XAVIER_H

#include "../TinNetDLL.h"

#include "../Core/Span.h"

#include "Initializer.h"

#include <cmath>
#include <cstddef>
#include <random>

namespace TinNet::Initializer
{
	class TINNET_DLL Xavier : public Initializer
	{
	protected:
		std::mt19937_64 sEngine;
		std::normal_distribution<float> sDist;
		
	public:
		Xavier(std::size_t nFanIn, std::size_t nFanOut);
		Xavier(std::mt19937_64::result_type nSeed, std::size_t nFanIn, std::size_t nFanOut);
		Xavier(const Xavier &sSrc) = default;
		virtual ~Xavier() noexcept = default;
		
	public:
		Xavier &operator=(const Xavier &sSrc) = default;
		virtual void operator()(Core::Span<float> sSpan) override;
	};
}

#endif