
/*
	2018.05.29
	Created by AcrylicShrimp.
*/

namespace TinNet
{
	template<class ...P> Iterator<P...>::Iterator() :
		sShape{},
		nAxis{0},
		nMaxAxis{0},
		sIndex(sizeof...(P), 0),
		bContinue{false}
	{
		//Empty.
	}

	template<class ...P> Iterator<P...> &Iterator<P...>::operator++()
	{
		this->decrement(this->nAxis);
		++this->sAxis[this->nAxis];

		for (auto nIndex{this->nAxis}; this->sAxis[nIndex] == this->sShape[this->sShape.rank() - nIndex - 1];)
		{
			if (nIndex == this->nMaxAxis)
			{
				this->bContinue = false;
				return *this;
			}

			this->sAxis[nIndex++] = 0;
			this->decrement(nIndex);

			++this->sAxis[nIndex];
			this->increment(nIndex);
		}

		this->increment(this->nAxis);

		return *this;
	}

	template<class ...P> void Iterator<P...>::init(const Shape &sShape, const P &...sAccessor)
	{
		if (!sShape.element())
			throw std::invalid_argument("element cannot be zero");

		this->sShape = sShape.shrink();
		this->sAccessor = {sAccessor...};

		if (!this->sShape.rank())
			this->sShape = this->sShape.expand();

		this->sAxis.resize(this->sShape.rank(), 0);
	}

	template<class ...P> void Iterator<P...>::prepare()
	{
		this->prepare(0);
	}

	template<class ...P> void Iterator<P...>::prepare(std::size_t nBeginAxis)
	{
		this->prepare(0, this->sShape.rank() - 1);
	}

	template<class ...P> void Iterator<P...>::prepare(std::size_t nBeginAxis, std::size_t nEndAxis)
	{
		if (nEndAxis < nBeginAxis)
			throw std::invalid_argument("begin axis cannot be greater than end axis");

		if (this->sShape.rank() <= nEndAxis)
			throw std::invalid_argument("axis is too large");

		this->nAxis = nBeginAxis;
		this->nMaxAxis = nEndAxis;
		this->bContinue = true;

		std::fill(this->sAxis.begin(), this->sAxis.end(), 0);
		std::fill(this->sIndex.begin(), this->sIndex.end(), 0);
	}

	template<class ...P> void Iterator<P...>::decrement(std::size_t nAxis)
	{
		for (std::size_t nIndex{0}; nIndex < sizeof...(P); ++nIndex)
			this->sIndex[nIndex] -= this->sAccessor[nIndex].index(nAxis, this->sAxis[nAxis]);
	}

	template<class ...P> void Iterator<P...>::increment(std::size_t nAxis)
	{
		for (std::size_t nIndex{0}; nIndex < sizeof...(P); ++nIndex)
			this->sIndex[nIndex] += this->sAccessor[nIndex].index(nAxis, this->sAxis[nAxis]);
	}
}