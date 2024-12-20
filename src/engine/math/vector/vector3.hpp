#pragma once
#include <cstdint>

namespace Math
{

//!########## ########## ##########
//!##########  Vector 3  ##########
//!########## ########## ##########

template<typename T>
struct Vector3
{
public:
    using Type = T;
    static constexpr int32_t Size        = 3;
    static constexpr int32_t SizeInBytes = sizeof(T) * Size;

    //! Constructors
    constexpr Vector3();
    constexpr Vector3(T value);
    constexpr Vector3(T x, T y, T z);

    //! Operators
    constexpr T&       operator[](std::size_t index);
    constexpr const T& operator[](std::size_t index) const;
    constexpr Vector3  operator+(const Vector3& other) const;
    constexpr Vector3& operator+=(const Vector3& other);
    constexpr Vector3  operator-(const Vector3& other) const;
    constexpr Vector3& operator-=(const Vector3& other);
    constexpr Vector3  operator*(const T value) const;
    constexpr Vector3& operator*=(const T value);
    constexpr Vector3  operator*(const Vector3& other) const;
    constexpr Vector3& operator*=(const Vector3& other);
    constexpr Vector3  operator/(const T value) const;
    constexpr Vector3& operator/=(const T value);
    constexpr Vector3  operator/(const Vector3& other) const;
    constexpr Vector3  operator/=(const Vector3& other);
    constexpr bool     operator==(const Vector3& other) const;
    constexpr bool     operator!=(const Vector3& other) const;

    //! Operations
    constexpr T       Dot(const Vector3& other) const;
    constexpr T       Length() const;
    constexpr T       LengthSquared() const;
    constexpr Vector3 Cross(const Vector3& other) const;
    constexpr Vector3 GetNormalized() const;
    constexpr Vector3 GetSafeNormalized() const;
    constexpr Vector3 GetReflected(const Vector3& normal) const;

public:
    T X, Y, Z;
};

template class Vector3<float>;
template class Vector3<double>;

using Vec3  = Vector3<float>;
using Vec3d = Vector3<double>;

} // namespace Math

#include "vector3.inl"