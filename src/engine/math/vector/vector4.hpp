#pragma once
#include <cstdint>

namespace Math
{

//!########## ########## ##########
//!##########  Vector 4  ##########
//!########## ########## ##########

template<typename T>
struct Vector4
{
public:
    using Type = T;
    static constexpr int32_t Size        = 4;
    static constexpr int32_t SizeInBytes = sizeof(T) * Size;

    //! Constructors
    constexpr Vector4();
    constexpr Vector4(T value);
    constexpr Vector4(T x, T y, T z, T w);

    //! Operators
    constexpr T&       operator[](std::size_t index);
    constexpr const T& operator[](std::size_t index) const;
    constexpr Vector4  operator+(const Vector4& other) const;
    constexpr Vector4& operator+=(const Vector4& other);
    constexpr Vector4  operator-(const Vector4& other) const;
    constexpr Vector4& operator-=(const Vector4& other);
    constexpr Vector4  operator*(const T value) const;
    constexpr Vector4& operator*=(const T value);
    constexpr Vector4  operator*(const Vector4& other) const;
    constexpr Vector4& operator*=(const Vector4& other);
    constexpr Vector4  operator/(const T value) const;
    constexpr Vector4& operator/=(const T value);
    constexpr Vector4  operator/(const Vector4& other) const;
    constexpr Vector4& operator/=(const Vector4& other);
    constexpr bool     operator==(const Vector4& other) const;
    constexpr bool     operator!=(const Vector4& other) const;

    //! Operations
    constexpr T       Dot(const Vector4& other) const;
    constexpr T       Length() const;
    constexpr T       LengthSquared() const;
    constexpr Vector4 GetNormalized() const;
    constexpr Vector4 GetSafeNormalized() const;

public:
    T X, Y, Z, W;
};

//Instantiate common templates
template class Vector4<float>;
template class Vector4<double>;

using Vec4  = Vector4<float>;
using Vec4d = Vector4<double>;

} // namespace Math

#include "vector4.inl"

