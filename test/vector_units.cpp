#include "common.h"

#include <units.h>
#include <literals.h>
#include <vector.h>
#include <to_string.h>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

using namespace dla;
using namespace literals;
using namespace int_literals;
constexpr auto scalar_gravity = -9.81_m_s2;

constexpr auto vector_gravity = vec(0_m_s2, 0_m_s2, scalar_gravity);
constexpr auto double_gravity = vector_gravity + vector_gravity;
constexpr auto square_gravity = vector_gravity * vector_gravity;
constexpr auto no_gravity = vector_gravity / vector_gravity.z;

TEST_CASE("Test vector of units", "[vector_units]") {
	REQUIRE(is_similar<vec<acceleration_unit, 3>>(vector_gravity));
	REQUIRE(is_similar<vec<acceleration_unit, 3>>(double_gravity));
	REQUIRE(is_similar<vec<detail::power_t<acceleration_unit, 2, 1>, 3>>(square_gravity));
	REQUIRE(is_similar<vec3>(no_gravity));
}
