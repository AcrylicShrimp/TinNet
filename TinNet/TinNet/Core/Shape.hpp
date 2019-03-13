
namespace TinNet::Core
{
	template<class I> Shape::Shape(I iBegin, I iEnd) :
		sDimension(iBegin, iEnd)
	{
		//Empty.
	}

	template<class I> void Shape::assign(I iBegin, I iEnd)
	{
		this->sDimension.assign(iBegin, iEnd);
	}

	template<class I> bool Shape::equals(I iBegin, I iEnd) const
	{
		auto iThisBegin{this->sDimension.cbegin()};
		auto iThisEnd{this->sDimension.cend()};

		for (; iBegin != iEnd && iThisBegin != iThisEnd; ++iBegin, ++iThisBegin)
			if (*iBegin != *iThisBegin)
				return false;

		for (; iBegin != iEnd; ++iBegin)
			if (*iBegin != 1)
				return false;

		for (; iThisBegin != iThisEnd; ++iThisBegin)
			if (*iThisBegin != 1)
				return false;

		return true;
	}
}