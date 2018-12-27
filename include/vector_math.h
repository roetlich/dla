#pragma once

#include <cmath>

#include "units.h"
#include "detail.h"

namespace unit {
    namespace vector {
        template<class T, std::size_t N>
        struct vec;
    }

    namespace math {
    #define MAKE_SYMMETRIC_BINARY_OPERAND(op) \
        template<class T, class U, std::size_t N> \
        constexpr auto operator op(const vector::vec<T, N>& lhs, const vector::vec<U, N>& rhs) noexcept { \
            vector::vec<decltype(std::declval<T>() op std::declval<U>()), N> res{}; \
            auto lhs_it = lhs.begin(); \
            auto rhs_it = rhs.begin(); \
            auto it = res.begin(); \
            const auto it_end = res.end(); \
            for (; it != it_end;) { \
                *it = *lhs_it op *rhs_it; \
                ++lhs_it; \
                ++rhs_it; \
				++it; \
            } \
            return res; \
        }

        MAKE_SYMMETRIC_BINARY_OPERAND(+)
        MAKE_SYMMETRIC_BINARY_OPERAND(-)
        MAKE_SYMMETRIC_BINARY_OPERAND(*)
        MAKE_SYMMETRIC_BINARY_OPERAND(/)

    #undef MAKE_SYMMETRIC_BINARY_OPERAND
    }
}
