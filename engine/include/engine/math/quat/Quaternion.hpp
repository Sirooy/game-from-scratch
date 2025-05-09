#pragma once
#include <cstdint>
#include <cstddef>
#include "../vector/Vector3.hpp"

namespace math
{

template<typename T>
struct Matrix4;

template<typename T>
struct Quaternion
{
public:
    using Type = T;
    constexpr static int32_t Size        = 4;
    constexpr static int32_t SizeInBytes = sizeof(T) * Size;

    //! Constructors
    constexpr Quaternion();
    constexpr Quaternion(T x, T y, T z, T w);

    //! Operators
    constexpr T&          operator[](std::size_t index);
    constexpr const T&    operator[](std::size_t index) const;
    constexpr Quaternion  operator+(const Quaternion& other) const;
    constexpr Quaternion& operator+=(const Quaternion& other);
    constexpr Quaternion  operator-(const Quaternion& other) const;
    constexpr Quaternion& operator-=(const Quaternion& other);
    constexpr Quaternion  operator*(const T value) const;
    constexpr Quaternion& operator*=(const T value);
    constexpr Quaternion  operator*(const Quaternion& other) const;
    constexpr Quaternion& operator*=(const Quaternion& other);
    constexpr Quaternion  operator/(const T value) const;
    constexpr Quaternion& operator/=(const T value);
    constexpr bool        operator==(const Quaternion& other) const;
    constexpr bool        operator!=(const Quaternion& other) const;

    //! Operations
    constexpr T                 Dot(const Quaternion& other) const;
    constexpr T                 Length() const;
    constexpr T                 LengthSquared() const;
    constexpr Quaternion        GetNormalized() const;
    constexpr Quaternion        GetSafeNormalized() const;
    constexpr Quaternion        GetConjugated() const;
    constexpr Quaternion        GetInverse() const;
    constexpr Matrix4<T>        ToMatrix4() const;
    constexpr static Quaternion FromAxis(const Vector3<T>& axis, T radians);

public:
    T x, y, z, w;
};

template struct Quaternion<float>;
template struct Quaternion<double>;

using Quat  = Quaternion<float>;
using Quatd = Quaternion<double>;

} //namespace math

#include "Quaternion.inl"