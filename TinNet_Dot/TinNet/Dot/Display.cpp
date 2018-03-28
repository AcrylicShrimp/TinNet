
/*
	2018.03.23
	Created by AcrylicShrimp.
*/

#include "Display.h"

#include "Dot.h"

namespace TinNet::Dot
{
	Display::Display() :
		nMin{.0f},
		nMax{.0f}
	{
		//Empty.
	}

	void Display::clear()
	{
		this->nMin = this->nMax = .0f;
		this->sData.clear();
	}

	void Display::push(float nData)
	{
		if (this->sData.size())
		{
			if (this->nMin > nData)
				this->nMin = nData;

			if (this->nMax < nData)
				this->nMax = nData;
		}
		else
			this->nMin = this->nMax = nData;

		this->sData.emplace_back(nData);

		Dot::repaintWindow();
	}

	std::tuple<std::size_t, std::size_t, float, float, const float *> Display::obtainData(std::size_t nViewportWidth, std::size_t nIndex) const
	{
		if (this->sData.size() < nIndex + nViewportWidth)
			nIndex = this->sData.size() < nViewportWidth ? 0 : this->sData.size() - nViewportWidth;

		if (this->sData.empty())
			return std::make_tuple((std::min)(this->sData.size(), nViewportWidth), nIndex, .0f, .0f, this->sData.data() + nIndex);

		auto nCount{(std::min)(this->sData.size(), nViewportWidth)};
		auto sMinMax{std::minmax_element(this->sData.cbegin() + nIndex, this->sData.cbegin() + nIndex + nCount)};

		return std::make_tuple((std::min)(this->sData.size(), nViewportWidth), nIndex, *sMinMax.first, *sMinMax.second, this->sData.data() + nIndex);
	}
}