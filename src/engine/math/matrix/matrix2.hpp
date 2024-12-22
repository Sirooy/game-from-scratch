#pragma once
#include <cstdint>
#include <cstddef>
#include "../vector/vector2.hpp"

namespace Math
{

//Column based 2x2 matrix
template<typename T>
struct Matrix2
{
public:
    using Type = T;
    constexpr static int32_t Size        = 2 * 2;
    constexpr static int32_t SizeInBytes = sizeof(T) * Size;
    constexpr static int32_t NumColumns  = 2;

    //! Constructors
    constexpr Matrix2();
    constexpr Matrix2(T value);
    constexpr Matrix2(T m11, T m22);
    constexpr Matrix2(T m11, T m21, T m12, T m22);

    //! Operators
    constexpr T*       operator[](std::size_t index);
    constexpr const T* operator[](std::size_t index) const;
    constexpr Matrix2  operator+(const Matrix2& other) const;
    constexpr Matrix2& operator+=(const Matrix2& other);
    constexpr Matrix2  operator-(const Matrix2& other) const;
    constexpr Matrix2& operator-=(const Matrix2& other);
    constexpr Matrix2  operator*(const T value) const;
    constexpr Matrix2& operator*=(const T value);
    constexpr Matrix2  operator*(const Matrix2& other) const;
    constexpr Matrix2& operator*=(const Matrix2& other);
    constexpr Matrix2  operator/(const T value) const;
    constexpr Matrix2& operator/=(const T value);
    constexpr bool     operator==(const Matrix2& other) const;
    constexpr bool     operator!=(const Matrix2& other) const;

    //! Operations
    constexpr T              Determinant() const;
    constexpr Matrix2        GetInverse() const;
    constexpr Matrix2        GetTranspose() const;
    constexpr Matrix2        GetScaled(const Vector2<T> scale) const;
    constexpr Matrix2        GetRotated(T radians) const;
    constexpr static Matrix2 CreateScale(const Vector2<T> scale);
    constexpr static Matrix2 CreateRotation(T radians);  
private:
    T Arr[Size];
};

template struct Matrix2<float>;
template struct Matrix2<double>;

using Mat2  = Matrix2<float>;
using Mat2d = Matrix2<double>;

} //namespace Math

#include "matrix2.inl"