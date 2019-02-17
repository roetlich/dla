#pragma once

#include "matrix_math.h"

#include <cmath>

namespace dla {
#define MAKE_MATRIX_MATRIX_BINARY_OPERATOR(op) \
    template<class T, class U, std::size_t N, std::size_t M> \
    constexpr auto operator op(const mat<T, N, M>& lhs, const mat<U, N, M>& rhs) noexcept { \
        mat<decltype(std::declval<T>() op std::declval<U>()), N, M> res{}; \
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
    MAKE_MATRIX_MATRIX_BINARY_OPERATOR(+)
    MAKE_MATRIX_MATRIX_BINARY_OPERATOR(-)
    MAKE_MATRIX_MATRIX_BINARY_OPERATOR(*)
    MAKE_MATRIX_MATRIX_BINARY_OPERATOR(/)
    MAKE_MATRIX_MATRIX_BINARY_OPERATOR(%)
    MAKE_MATRIX_MATRIX_BINARY_OPERATOR(&)
    MAKE_MATRIX_MATRIX_BINARY_OPERATOR(|)
    MAKE_MATRIX_MATRIX_BINARY_OPERATOR(^)
    MAKE_MATRIX_MATRIX_BINARY_OPERATOR(<<)
    MAKE_MATRIX_MATRIX_BINARY_OPERATOR(>>)
#undef MAKE_MATRIX_MATRIX_BINARY_OPERATOR

#define MAKE_MATRIX_SCALAR_BINARY_OPERATOR(op) \
    template<class T, class U, std::size_t N, std::size_t M> \
    constexpr auto operator op(const mat<T, N, M>& lhs, const U& rhs) noexcept { \
        mat<decltype(std::declval<T>() op std::declval<U>()), N, M> res{}; \
        auto lhs_it = lhs.begin(); \
        auto it = res.begin(); \
        const auto it_end = res.end(); \
        for (; it != it_end;) { \
            *it = *lhs_it op rhs; \
            ++lhs_it; \
            ++it; \
        } \
        return res; \
    }
    MAKE_MATRIX_SCALAR_BINARY_OPERATOR(+)
    MAKE_MATRIX_SCALAR_BINARY_OPERATOR(-)
    MAKE_MATRIX_SCALAR_BINARY_OPERATOR(*)
    MAKE_MATRIX_SCALAR_BINARY_OPERATOR(/)
    MAKE_MATRIX_SCALAR_BINARY_OPERATOR(%)
    MAKE_MATRIX_SCALAR_BINARY_OPERATOR(&)
    MAKE_MATRIX_SCALAR_BINARY_OPERATOR(|)
    MAKE_MATRIX_SCALAR_BINARY_OPERATOR(^)
    MAKE_MATRIX_SCALAR_BINARY_OPERATOR(<<)
    MAKE_MATRIX_SCALAR_BINARY_OPERATOR(>>)
#undef MAKE_MATRIX_SCALAR_BINARY_OPERATOR

#define MAKE_SCALAR_VECTOR_BINARY_OPERATOR(op) \
    template<class T, class U, std::size_t N, std::size_t M> \
    constexpr auto operator op(const T& lhs, const mat<U, N, M>& rhs) noexcept { \
        mat<decltype(std::declval<T>() op std::declval<U>()), N, M> res{}; \
        auto rhs_it = rhs.begin(); \
        auto it = res.begin(); \
        const auto it_end = res.end(); \
        for (; it != it_end;) { \
            *it = lhs op *rhs_it; \
            ++rhs_it; \
            ++it; \
        } \
        return res; \
    }
    MAKE_SCALAR_VECTOR_BINARY_OPERATOR(+)
    MAKE_SCALAR_VECTOR_BINARY_OPERATOR(-)
    MAKE_SCALAR_VECTOR_BINARY_OPERATOR(*)
    MAKE_SCALAR_VECTOR_BINARY_OPERATOR(/)
    MAKE_SCALAR_VECTOR_BINARY_OPERATOR(%)
    MAKE_SCALAR_VECTOR_BINARY_OPERATOR(&)
    MAKE_SCALAR_VECTOR_BINARY_OPERATOR(|)
    MAKE_SCALAR_VECTOR_BINARY_OPERATOR(^)
    MAKE_SCALAR_VECTOR_BINARY_OPERATOR(<<)
    MAKE_SCALAR_VECTOR_BINARY_OPERATOR(>>)
#undef MAKE_SCALAR_VECTOR_BINARY_OPERATOR

#define MAKE_MATRIX_UNARY_OPERATOR(op) \
    template<class T, std::size_t N, std::size_t M> \
    constexpr auto operator op(const mat<T, N, M>& val) noexcept { \
        mat<decltype(op std::declval<T>()), N, M> res{}; \
        auto val_it = val.begin(); \
        auto it = res.begin(); \
        const auto it_end = res.end(); \
        for (; it != it_end;) { \
            *it = op *val_it; \
            ++val_it; \
            ++it; \
        } \
        return res; \
    }
    MAKE_MATRIX_UNARY_OPERATOR(+)
    MAKE_MATRIX_UNARY_OPERATOR(-)
    MAKE_MATRIX_UNARY_OPERATOR(~)
#undef MAKE_MATRIX_UNARY_OPERATOR

    template<class T, class U, std::size_t N, std::size_t M>
    constexpr auto operator==(const mat<T, N, M>& lhs, const mat<U, N, M>& rhs) noexcept {
        auto res = lhs[0] == rhs[0];
        if constexpr (N > 1) {
            auto lhs_it = lhs.begin() + 1;
            auto rhs_it = rhs.begin() + 1;
            const auto lhs_it_end = lhs.end();
            for (; lhs_it != lhs_it_end;) {
                res &= *lhs_it == *rhs_it;
                ++lhs_it;
                ++rhs_it;
            }
        }
        return res;
    }
    template<class T, class U, std::size_t N, std::size_t M>
    constexpr auto operator!=(const mat<T, N, M>& lhs, const mat<U, N, M>& rhs) noexcept {
        return !(lhs == rhs);
    }

    template<class T, class U, std::size_t N, std::size_t M>
    constexpr auto compare(const mat<T, N, M>& lhs, const mat<U, N, M>& rhs) noexcept {
        mat<decltype(std::declval<T>() == std::declval<U>()), N, M> res{};
        auto lhs_it = lhs.begin();
        auto rhs_it = rhs.begin();
        auto it = res.begin();
        const auto it_end = res.end();
        for (; it != it_end;) {
            *it = *lhs_it == *rhs_it;
            ++lhs_it;
            ++rhs_it;
            ++it;
        }
        return res;
    }

    template<class T, std::size_t N, std::size_t M>
    constexpr auto abs(const mat<T, N, M>& val) noexcept {
        mat<T, N, M> res{};
        auto val_it = val.begin();
        auto it = res.begin();
        const auto it_end = res.end();
        for (; it != it_end;) {
            *it = math::abs(*val_it);
            ++val_it;
            ++it;
        }
        return res;
    }

    template<class T, std::size_t N, std::size_t M>
    constexpr auto transpose(const mat<T, N, M>& val) noexcept {
        mat<T, M, N> res{};
        for (std::size_t i = 0; i < res.num_col; i++) {
            for (std::size_t j = 0; j < res.num_row; j++) {
                res[i][j] = val[j][i];
            }
        }
        return res;
    }

    template<class T, class U, std::size_t N, std::size_t M, std::size_t L>
    constexpr auto dot(const mat<T, N, M>& lhs, const mat<U, M, L>& rhs) {
        using res_t = mat<decltype(std::declval<T>() * std::declval<U>()), N, L>;
        res_t res{};
        for (std::size_t i = 0; i < res_t::row_size; i++) {
            for (std::size_t j = 0; j < res_t::col_size; j++) {
                for (std::size_t k = 0; k < M; k++) {
                    res[i][j] += rhs[i][k] * lhs[k][j];
                }                
            }
        }
        return res;
    }
    template<class T, class U, std::size_t N, std::size_t M>
    constexpr auto dot(const mat<T, N, M>& lhs, const vec<U, M>& rhs) {
        using res_t = vec<decltype(std::declval<T>() * std::declval<U>()), N>;
        res_t res{};
        for (std::size_t i = 0; i < res_t::size; i++) {
            for (std::size_t k = 0; k < M; k++) {
                res[i] += lhs[k][i] * rhs[k];
            }                
        }
        return res;
    }
    template<class T, class U, std::size_t N, std::size_t M>
    constexpr auto dot(const vec<T, N>& lhs, const mat<U, N, M>& rhs) {
        using res_t = vec<decltype(std::declval<T>() * std::declval<U>()), M>;
        res_t res{};
        for (std::size_t i = 0; i < res_t::size; i++) {
            res[i] = dla::dot(rhs[i], lhs);
        }
        return res;
    }
}