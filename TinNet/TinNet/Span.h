
/*
	2018.09.16
	Created by AcrylicShrimp.
*/

#ifndef _CLASS_TINNET_SPAN_H

#define _CLASS_TINNET_SPAN_H

#include <array>
#include <cstddef>
#include <iterator>
#include <type_traits>

namespace TinNet
{
	template<class T> class Span final
	{
	public:
		using element_type = T;
		using index_type = std::ptrdiff_t;
		using difference_type = std::ptrdiff_t;
		using value_type = std::remove_cv<T>;
		using const_value_type = const value_type;
		using pointer = T * ;
		using const_pointer = const T *;
		using reference = T & ;
		using const_reference = const T &;
		using iterator = std::iterator<std::random_access_iterator_tag, value_type, difference_type, pointer, reference>;
		using const_iterator = std::iterator<std::random_access_iterator_tag, const_value_type, difference_type, const_pointer, const_reference>;
		using reverse_iterator = std::reverse_iterator<iterator>;
		using const_reverse_iterator = std::reverse_iterator<const_iterator>;

	private:
		pointer pBegin;
		index_type nSize;

	public:
		constexpr Span() noexcept;
		constexpr Span(pointer ptr, index_type count);
		constexpr Span(pointer firstElem, pointer lastElem);
		template<std::size_t N> constexpr Span(element_type(&arr)[N]) noexcept;
		template<std::size_t N> constexpr Span(std::array<value_type, N> &arr) noexcept;
		template<std::size_t N> constexpr Span(const std::array<value_type, N> &arr) noexcept;
		template<class Container> constexpr Span(Container &cont);
		template<class Container> constexpr Span(const Container &cont);
		template<class U> constexpr Span(const Span<U> &s) noexcept;
		constexpr Span(const Span &other) = default;
		~Span() = default;

	public:
		constexpr Span &operator=(const Span &other) noexcept = default;

	public:
		constexpr iterator begin() const noexcept;
		constexpr const_iterator cbegin() const noexcept;
		constexpr iterator end() const noexcept;
		constexpr const_iterator cend() const noexcept;
		constexpr reverse_iterator rbegin() const noexcept;
		constexpr const_reverse_iterator crbegin() const noexcept;
		constexpr reverse_iterator rend() const noexcept;
		constexpr const_reverse_iterator crend() const noexcept;
		constexpr reference operator[](index_type idx) const;
		constexpr reference operator()(index_type idx) const;
		constexpr pointer data() const noexcept;
		constexpr index_type size() const noexcept;
		constexpr index_type size_bytes() const noexcept;
		constexpr bool empty() const noexcept;
		constexpr Span<element_type> first(std::ptrdiff_t Count) const;
		constexpr Span<element_type> last(std::ptrdiff_t Count) const;
		constexpr Span<element_type> subspan(std::ptrdiff_t Offset, std::ptrdiff_t Count) const;

	};
}

#endif