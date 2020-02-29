
#include "tinnet/includes/node/Shape.h"

#include "catch2.hpp"

#include <cstddef>
#include <vector>

TEST_CASE("tinnet::node::Shape")
{
	SECTION("Scalar shape")
	{
		tinnet::node::Shape sShape;

		CHECK(sShape.rank() == 0);
		CHECK(sShape.size() == 1);
		CHECK(sShape.scalar() == true);
		CHECK(sShape.vector() == false);
		CHECK(sShape.matrix() == false);
		CHECK(sShape.tensor() == false);
	}
	SECTION("Vector shape")
	{
		tinnet::node::Shape sShape{{1}};

		CHECK(sShape.rank() == 1);
		CHECK(sShape.size() == 1);
		CHECK(sShape.scalar() == false);
		CHECK(sShape.vector() == true);
		CHECK(sShape.matrix() == false);
		CHECK(sShape.tensor() == false);
	}
	SECTION("Matrix shape")
	{
		tinnet::node::Shape sShape{{1, 1}};

		CHECK(sShape.rank() == 2);
		CHECK(sShape.size() == 1);
		CHECK(sShape.scalar() == false);
		CHECK(sShape.vector() == false);
		CHECK(sShape.matrix() == true);
		CHECK(sShape.tensor() == false);
	}
	SECTION("Tensor shape")
	{
		tinnet::node::Shape sShape{{1, 1, 1}};

		CHECK(sShape.rank() == 3);
		CHECK(sShape.size() == 1);
		CHECK(sShape.scalar() == false);
		CHECK(sShape.vector() == false);
		CHECK(sShape.matrix() == false);
		CHECK(sShape.tensor() == true);
	}
	SECTION("Ctor, Rank, Size #1")
	{
		tinnet::node::Shape sShape{{1, 2, 3, 4, 5, 6, 7, 8, 9}};

		CHECK(sShape.rank() == 9);
		CHECK(sShape.size() == 1 * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9);
		CHECK(sShape.scalar() == false);
		CHECK(sShape.vector() == false);
		CHECK(sShape.matrix() == false);
		CHECK(sShape.tensor() == true);
	}
	SECTION("Ctor, Rank, Size #2")
	{
		tinnet::node::Shape sShape{tinnet::node::Shape{{1, 2, 3, 4, 5, 6, 7, 8, 9}}};

		CHECK(sShape.rank() == 9);
		CHECK(sShape.size() == 1 * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9);
		CHECK(sShape.scalar() == false);
		CHECK(sShape.vector() == false);
		CHECK(sShape.matrix() == false);
		CHECK(sShape.tensor() == true);
	}
	SECTION("Comparison operators")
	{
		CHECK(
			(tinnet::node::Shape{{1, 2, 3, 4, 5, 6, 7, 8, 9}} == std::vector<std::size_t>{1, 2, 3, 4, 5, 6, 7, 8, 9})
			== true);
		CHECK(
			(tinnet::node::Shape{{1, 2, 3, 4, 5, 6, 7, 8, 9}} == std::vector<std::size_t>{1, 2, 3, 4, 5, 6, 7, 8, 8})
			== false);
		CHECK(
			(tinnet::node::Shape{{1, 2, 3, 4, 5, 6, 7, 8, 9}} != std::vector<std::size_t>{1, 2, 3, 4, 5, 6, 7, 8, 9})
			== false);
		CHECK(
			(tinnet::node::Shape{{1, 2, 3, 4, 5, 6, 7, 8, 9}} != std::vector<std::size_t>{1, 2, 3, 4, 5, 6, 7, 8, 8})
			== true);
		CHECK(
			(tinnet::node::Shape{{1, 2, 3, 4, 5, 6, 7, 8, 9}} == tinnet::node::Shape{{1, 2, 3, 4, 5, 6, 7, 8, 9}})
			== true);
		CHECK(
			(tinnet::node::Shape{{1, 2, 3, 4, 5, 6, 7, 8, 9}} == tinnet::node::Shape{{1, 2, 3, 4, 5, 6, 7, 8, 8}})
			== false);
		CHECK(
			(tinnet::node::Shape{{1, 2, 3, 4, 5, 6, 7, 8, 9}} != tinnet::node::Shape{{1, 2, 3, 4, 5, 6, 7, 8, 9}})
			== false);
		CHECK(
			(tinnet::node::Shape{{1, 2, 3, 4, 5, 6, 7, 8, 9}} != tinnet::node::Shape{{1, 2, 3, 4, 5, 6, 7, 8, 8}})
			== true);

		CHECK(
			(std::vector<std::size_t>{1, 2, 3, 4, 5, 6, 7, 8, 9} == tinnet::node::Shape{{1, 2, 3, 4, 5, 6, 7, 8, 9}})
			== true);
		CHECK(
			(std::vector<std::size_t>{1, 2, 3, 4, 5, 6, 7, 8, 8} == tinnet::node::Shape{{1, 2, 3, 4, 5, 6, 7, 8, 9}})
			== false);
		CHECK(
			(std::vector<std::size_t>{1, 2, 3, 4, 5, 6, 7, 8, 9} != tinnet::node::Shape{{1, 2, 3, 4, 5, 6, 7, 8, 9}})
			== false);
		CHECK(
			(std::vector<std::size_t>{1, 2, 3, 4, 5, 6, 7, 8, 8} != tinnet::node::Shape{{1, 2, 3, 4, 5, 6, 7, 8, 9}})
			== true);
		CHECK(
			(tinnet::node::Shape{{1, 2, 3, 4, 5, 6, 7, 8, 9}} == tinnet::node::Shape{{1, 2, 3, 4, 5, 6, 7, 8, 9}})
			== true);
		CHECK(
			(tinnet::node::Shape{{1, 2, 3, 4, 5, 6, 7, 8, 8}} == tinnet::node::Shape{{1, 2, 3, 4, 5, 6, 7, 8, 9}})
			== false);
		CHECK(
			(tinnet::node::Shape{{1, 2, 3, 4, 5, 6, 7, 8, 9}} != tinnet::node::Shape{{1, 2, 3, 4, 5, 6, 7, 8, 9}})
			== false);
		CHECK(
			(tinnet::node::Shape{{1, 2, 3, 4, 5, 6, 7, 8, 8}} != tinnet::node::Shape{{1, 2, 3, 4, 5, 6, 7, 8, 9}})
			== true);
	}
	SECTION("Assignment operators")
	{
		CHECK(
			((tinnet::node::Shape{} = std::vector<std::size_t>{1, 2, 3, 4, 5, 6, 7, 8, 9})
			 == tinnet::node::Shape{{1, 2, 3, 4, 5, 6, 7, 8, 9}})
			== true);
		CHECK(
			((tinnet::node::Shape{} = tinnet::node::Shape{{1, 2, 3, 4, 5, 6, 7, 8, 9}})
			 == tinnet::node::Shape{{1, 2, 3, 4, 5, 6, 7, 8, 9}})
			== true);
	}
	SECTION("Extend, Shrink, Squeeze")
	{
		CHECK(tinnet::node::Shape{}.extend() == tinnet::node::Shape{{1}});
		CHECK(tinnet::node::Shape{{1}}.extend() == tinnet::node::Shape{{1, 1}});
		CHECK(tinnet::node::Shape{{1, 10}}.extend() == tinnet::node::Shape{{1, 1, 10}});
		CHECK(tinnet::node::Shape{{1, 10, 20}}.extend() == tinnet::node::Shape{{1, 1, 10, 20}});

		CHECK(tinnet::node::Shape{{1, 10, 2, 20}}.extend(0) == tinnet::node::Shape{{1, 10, 2, 20}});
		CHECK(tinnet::node::Shape{{1, 10, 2, 20}}.extend(1) == tinnet::node::Shape{{1, 10, 2, 20}});
		CHECK(tinnet::node::Shape{{1, 10, 2, 20}}.extend(10) == tinnet::node::Shape{{1, 1, 1, 1, 1, 1, 1, 10, 2, 20}});

		CHECK(tinnet::node::Shape{{1, 1, 1, 1}}.shrink() == tinnet::node::Shape{});
		CHECK(tinnet::node::Shape{{1, 10, 2, 20}}.shrink() == tinnet::node::Shape{{10, 2, 20}});
		CHECK(tinnet::node::Shape{{10, 20, 30, 40}}.shrink() == tinnet::node::Shape{{10, 20, 30, 40}});

		CHECK(tinnet::node::Shape{{1, 1, 1, 1}}.squeeze() == tinnet::node::Shape{});
		CHECK(tinnet::node::Shape{{1, 10, 1, 20}}.squeeze() == tinnet::node::Shape{{10, 20}});
		CHECK(tinnet::node::Shape{{1, 10, 2, 20}}.squeeze() == tinnet::node::Shape{{10, 2, 20}});
	}
	SECTION("Broadcast")
	{
		CHECK(
			tinnet::node::Shape::broadcast(tinnet::node::Shape{{}}, tinnet::node::Shape{{}})
			== tinnet::node::Shape{{}});
		CHECK(
			tinnet::node::Shape::broadcast(tinnet::node::Shape{{1, 2, 3, 4, 5, 6, 7, 8, 9}}, tinnet::node::Shape{{}})
			== tinnet::node::Shape{{1, 2, 3, 4, 5, 6, 7, 8, 9}});
		CHECK(
			tinnet::node::Shape::broadcast(tinnet::node::Shape{{}}, tinnet::node::Shape{{1, 2, 3, 4, 5, 6, 7, 8, 9}})
			== tinnet::node::Shape{{1, 2, 3, 4, 5, 6, 7, 8, 9}});
		CHECK(
			tinnet::node::Shape::broadcast(tinnet::node::Shape{{1, 20, 1, 40}}, tinnet::node::Shape{{10, 1, 30, 1}})
			== tinnet::node::Shape{{10, 20, 30, 40}});
		CHECK(
			tinnet::node::Shape::broadcast(tinnet::node::Shape{{10, 20, 30, 40}}, tinnet::node::Shape{{10, 20, 30, 40}})
			== tinnet::node::Shape{{10, 20, 30, 40}});

		CHECK_THROWS(tinnet::node::Shape::broadcast(
			tinnet::node::Shape{{10, 20, 30, 40}},
			tinnet::node::Shape{{40, 30, 20, 10}}));
	}
}