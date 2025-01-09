#pragma once
#include <cstdint>
#include <cstddef>
#include "../vector/Vector2.hpp"
#include "../vector/Vector3.hpp"

namespace math
{

//Column based 3x3 matrix
template<typename T>
struct Matrix3
{
public:
    using Type = T;
    constexpr static int32_t Size        = 3 * 3;
    constexpr static int32_t SizeInBytes = sizeof(T) * Size;
    constexpr static int32_t NumColumns  = 3;

    //! Constructors
    constexpr Matrix3();
    constexpr Matrix3(T value);
    constexpr Matrix3(T m11, T m22, T m33);
    constexpr Matrix3(T m11, T m21, T m31, T m12, T m22, T m32, T m13, T m23, T m33);

    //! Operators
    constexpr T*       operator[](std::size_t index);
    constexpr const T* operator[](std::size_t index) const;
    constexpr Matrix3  operator+(const Matrix3& other) const;
    constexpr Matrix3& operator+=(const Matrix3& other);
    constexpr Matrix3  operator-(const Matrix3& other) const;
    constexpr Matrix3& operator-=(const Matrix3& other);
    constexpr Matrix3  operator*(const T value) const;
    constexpr Matrix3& operator*=(const T value);
    constexpr Matrix3  operator*(const Matrix3& other) const;
    constexpr Matrix3& operator*=(const Matrix3& other);
    constexpr Matrix3  operator/(const T value) const;
    constexpr Matrix3& operator/=(const T value);
    constexpr bool     operator==(const Matrix3& other) const;
    constexpr bool     operator!=(const Matrix3& other) const;

    //! Operations
    constexpr T              Determinant() const;
    constexpr Matrix3        GetInverse() const;
    constexpr Matrix3        GetTranspose() const;
    constexpr Matrix3        GetScaled(const Vector3<T>& scale) const;
    constexpr Matrix3        GetScaled2D(const Vector2<T> scale) const;
    constexpr Matrix3        GetRotatedX(T radians) const;
    constexpr Matrix3        GetRotatedY(T radians) const;
    constexpr Matrix3        GetRotatedZ(T radians) const;
    constexpr Matrix3        GetTranslated2D(const Vector2<T> v) const;
    constexpr static Matrix3 CreateScale(const Vector3<T>& scale);
    constexpr static Matrix3 CreateScale2D(const Vector2<T> scale);
    constexpr static Matrix3 CreateRotationX(T radians);
    constexpr static Matrix3 CreateRotationY(T radians);
    constexpr static Matrix3 CreateRotationZ(T radians);
    constexpr static Matrix3 CreateTranslation2D(const Vector2<T> v);
    constexpr static Matrix3 CreateTransform2D(const Vector2<T> scale, T radians, 
        const Vector2<T> translation);

public:
    T arr[Size];
};

template struct Matrix3<float>;
template struct Matrix3<double>;

using Mat3  = Matrix3<float>;
using Mat3d = Matrix3<double>;

} //namespace math

#include "Matrix3.inl"