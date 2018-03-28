
/*
	2018.03.23
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_DOT_DISPLAY_H

#define _CLASS_TINNET_DOT_DISPLAY_H

#include "../../../TinNet/TinNet/TinNetDLL.h"

#include <algorithm>
#include <cstddef>
#include <tuple>
#include <vector>

namespace TinNet::Dot
{
	class TINNET_DLL Display final
	{
	private:
		float nMin;
		float nMax;
		std::vector<float> sData;
		
	public:
		Display();
		Display(const Display &sSrc) = delete;
		Display(Display &&sSrc) = delete;
		~Display() = default;
		
	public:
		Display &operator=(const Display &sSrc) = delete;
		Display &operator=(Display &&sSrc) = delete;

	public:
		inline float (min)() const;
		inline float (max)() const;
		inline std::size_t length() const;
		void clear();
		void push(float nData);
		std::tuple<std::size_t, std::size_t, float, float, const float *> obtainData(std::size_t nViewportWidth, std::size_t nIndex) const;
	};

	inline float (Display::min)() const
	{
		return this->nMin;
	}

	inline float (Display::max)() const
	{
		return this->nMax;
	}

	inline std::size_t Display::length() const
	{
		return this->sData.size();
	}
}

#endif