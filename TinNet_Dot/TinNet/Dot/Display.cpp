
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

	std::tuple<std::size_t, const float *> Display::obtainData(std::size_t nViewportWidth, std::size_t nIndex) const
	{
		if (this->sData.size() < nIndex + nViewportWidth)
			nIndex = this->sData.size() < nViewportWidth ? 0 : this->sData.size() - nViewportWidth;

		return std::make_tuple((std::min)(this->sData.size(), nViewportWidth), this->sData.data() + nIndex);
	}
}