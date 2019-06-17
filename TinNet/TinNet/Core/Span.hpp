
/*
	2019.06.15
	Created by AcrylicShrimp.
*/

namespace TinNet::Core
{
	template<class T> Span<T>::Span() noexcept :
		pBase{nullptr},
		nLength{0}
	{
		//Empty.
	}

	template<class T> Span<T>::Span(T *pBase, std::size_t nLength) noexcept :
		pBase{pBase},
		nLength{nLength}
	{
		//Empty.
	}
}