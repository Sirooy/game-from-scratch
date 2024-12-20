#pragma once
#include <concepts>
#include <cstdint>

namespace Math
{

//!########## ########## ##########
//!##########  Vector 2  ##########
//!########## ########## ##########

template<typename T>
concept IsNumberConcept = std::integral<T> || std::floating_point<T>;

template<typename T> //requires IsNumberConcept<T>
struct Vector2
{
public:
    using Type = T;
    static constexpr int32_t Size        = 2;
    static constexpr int32_t SizeInBytes = sizeof(T) * Size;

    //! Constructors
    constexpr Vector2();
    constexpr Vector2(T value);
    constexpr Vector2(T x, T y);

    //! Operators
    constexpr T&       operator[](std::size_t index);
    constexpr const T& operator[](std::size_t index) const;
    constexpr Vector2  operator+(const Vector2 other) const;
    constexpr Vector2& operator+=(const Vector2 other);
    constexpr Vector2  operator-(const Vector2 other) const;
    constexpr Vector2& operator-=(const Vector2 other);
    constexpr Vector2  operator*(const T value) const;
    constexpr Vector2& operator*=(const T value);
    constexpr Vector2  operator*(const Vector2 other) const;
    constexpr Vector2& operator*=(const Vector2 other);
    constexpr Vector2  operator/(const T value) const;
    constexpr Vector2& operator/=(const T value);
    constexpr Vector2  operator/(const Vector2 other) const;
    constexpr Vector2  operator/=(const Vector2 other);
    constexpr bool     operator==(const Vector2 other) const;
    constexpr bool     operator!=(const Vector2 other) const;

    //! Operations
    constexpr T       Dot(const Vector2 other) const;
    constexpr T       Length() const;
    constexpr T       LengthSquared() const;
    constexpr T       Cross2D(const Vector2 other) const;
    constexpr Vector2 GetNormalized() const;
    constexpr Vector2 GetSafeNormalized() const;
    constexpr Vector2 GetReflected(const Vector2 normal) const;
    constexpr Vector2 GetRotated(T radians) const;

public:
    T X, Y;
};

template class Vector2<float>;
template class Vector2<double>;

using Vec2  = Vector2<float>;
using Vec2d = Vector2<double>;

} // namespace Math

#include "vector2.inl"