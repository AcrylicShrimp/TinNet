
#ifndef _TINNET_NODE_SHAPE_H

#define _TINNET_NODE_SHAPE_H

#include <cstddef>
#include <functional>
#include <numeric>
#include <ostream>
#include <utility>
#include <vector>

namespace tinnet::node {
	class Shape final {
	private:
		std::vector<std::size_t> sDimension;

	public:
		Shape();
		Shape(const std::vector<std::size_t> &sRhs);
		Shape(std::vector<std::size_t> &&sRhs) noexcept;
		Shape(const Shape &sRhs)	 = default;
		Shape(Shape &&sRhs) noexcept = default;
		~Shape() noexcept			 = default;

	public:
		Shape &				 operator=(const std::vector<std::size_t> &sRhs);
		Shape &				 operator=(std::vector<std::size_t> &&sRhs) noexcept;
		Shape &				 operator=(const Shape &sRhs) = default;
		Shape &				 operator=(Shape &&sRhs) noexcept = default;
		bool				 operator==(const Shape &sRhs) const;
		friend bool			 operator==(const Shape &sLhs, const std::vector<std::size_t> &sRhs);
		friend bool			 operator==(const std::vector<std::size_t> &sLhs, const Shape &sRhs);
		bool				 operator!=(const Shape &sRhs) const;
		friend bool			 operator!=(const Shape &sLhs, const std::vector<std::size_t> &sRhs);
		friend bool			 operator!=(const std::vector<std::size_t> &sLhs, const Shape &sRhs);
		friend std::ostream &operator<<(std::ostream &sLhs, const Shape &sRhs);
		Shape				 extend() const;
		Shape				 extend(std::size_t nRank) const;
		Shape				 shrink() const;
		Shape				 squeeze() const;
		static Shape		 broadcast(const Shape &sLhs, const Shape &sRhs);

	public:
		std::size_t &operator[](std::size_t nIndex)
		{
			return this->sDimension[nIndex];
		}
		std::size_t operator[](std::size_t nIndex) const
		{
			return this->sDimension[nIndex];
		}
		std::size_t rank() const noexcept
		{
			return this->sDimension.size();
		}
		std::size_t size() const noexcept
		{
			return std::accumulate(
				this->sDimension.cbegin(),
				this->sDimension.cend(),
				1,
				std::multiplies<std::size_t>{});
		}
		bool scalar() const noexcept
		{
			return this->rank() == 0;
		}
		bool vector() const noexcept
		{
			return this->rank() == 1;
		}
		bool matrix() const noexcept
		{
			return this->rank() == 2;
		}
		bool tensor() const noexcept
		{
			return this->rank() >= 3;
		}

	public:
		friend void swap(Shape &sLhs, Shape &sRhs) noexcept
		{
			using std::swap;
			swap(sLhs.sDimension, sRhs.sDimension);
		}
	};

}	 // namespace tinnet::node

#endif