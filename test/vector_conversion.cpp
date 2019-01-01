#include "vector.h"

int main() {
	using namespace dla;

	constexpr auto only_one_element = vec1(1.0f);
	[[maybe_unused]] constexpr float just_that_element = only_one_element;

	constexpr auto float_vec = vec3(1.0f);
	constexpr auto double_vec = dvec3(1.0f);
	constexpr auto int_vec = ivec3(1);
	constexpr auto uint_vec = uvec3(1u);
	constexpr auto fd_prod_vec = float_vec * double_vec;
	constexpr auto id_prod_vec = int_vec * double_vec;
	constexpr auto iu_prod_vec = int_vec * uint_vec;
	static_assert(std::is_same_v<std::remove_const_t<decltype(fd_prod_vec)>, dvec3>);
	static_assert(std::is_same_v<std::remove_const_t<decltype(id_prod_vec)>, dvec3>);
	static_assert(std::is_same_v<std::remove_const_t<decltype(iu_prod_vec)>, uvec3>);
}