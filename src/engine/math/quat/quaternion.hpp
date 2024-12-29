#pragma once
#include <cstdint>
#include <cstddef>
#include "../vector/vector3.hpp"
#include "../matrix/matrix4.hpp"

namespace Math
{

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
    constexpr Vector3<T>  operator*(const Vector3<T>& v) const;
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
    T X, Y, Z, W;
};

template struct Quaternion<float>;
template struct Quaternion<double>;

using Quat  = Quaternion<float>;
using Quatd = Quaternion<double>;

} //namespace Math

#include <cmath>

namespace Math
{

//! Constructors
template<typename T>
constexpr Quaternion<T>::Quaternion() : X{}, Y{}, Z{}, W{} { }

template<typename T>
constexpr Quaternion<T>::Quaternion(T x, T y, T z, T w) : X{x}, Y{y}, Z{z}, W{w} { }

//! Operators
template<typename T>
constexpr T& Quaternion<T>::operator[](std::size_t index)
{
    switch (index)
    {
        default:
        case 0: return X;
        case 1: return Y;
        case 2: return Z;
        case 3: return W;
    }
}

template<typename T>
constexpr const T& Quaternion<T>::operator[](std::size_t index) const
{
    switch (index)
    {
        default:
        case 0: return X;
        case 1: return Y;
        case 2: return Z;
        case 3: return W;
    }
}

template<typename T>
constexpr Quaternion<T> Quaternion<T>::operator+(const Quaternion<T>& other) const
{
    return Quaternion(X + other.X, Y + other.Y, Z + other.Z, W + other.W);
}

template<typename T>
constexpr Quaternion<T>& Quaternion<T>::operator+=(const Quaternion<T>& other)
{
    X += other.X;
    Y += other.Y;
    Z += other.Z;
    W += other.W;

    return *this;
}

template<typename T>
constexpr Quaternion<T> Quaternion<T>::operator-(const Quaternion<T>& other) const
{
    return Quaternion(X - other.X, Y - other.Y, Z - other.Z, W - other.W);
}

template<typename T>
constexpr Quaternion<T>& Quaternion<T>::operator-=(const Quaternion<T>& other)
{
    X -= other.X;
    Y -= other.Y;
    Z -= other.Z;
    W -= other.W;

    return *this;
}

template<typename T>
constexpr Quaternion<T> Quaternion<T>::operator*(const T value) const
{
    return Quaternion(X * value, Y * value, Z * value, W * value);
}

template<typename T>
constexpr Quaternion<T>& Quaternion<T>::operator*=(const T value)
{
    X *= value;
    Y *= value;
    Z *= value;
    W *= value;

    return *this;
}

template<typename T>
constexpr Quaternion<T> Quaternion<T>::operator*(const Quaternion<T>& other) const
{
    T dot            = X * other.X + Y * other.Y + Z * other.Z;
    Vector3<T> cross = Vector3 { 
        Y * other.Z - Z * other.Y, 
        Z * other.X - X * other.Z,
        X * other.Y - Y * other.X 
    };
    
    return Quaternion(
        W * other.X + other.W * X + cross.X,
        W * other.Y + other.W * Y + cross.Y,
        W * other.Z + other.W * Z + cross.Z,
        W * other.W - dot 
    );
}

template<typename T>
constexpr Quaternion<T>& Quaternion<T>::operator*=(const Quaternion<T>& other)
{
    T dot            = X * other.X + Y * other.Y + Z * other.Z;
    Vector3<T> cross = Vector3 { 
        Y * other.Z - Z * other.Y, 
        Z * other.X - X * other.Z,
        X * other.Y - Y * other.X 
    };

    X = W * other.X + other.W * X + cross.X;
    Y = W * other.Y + other.W * Y + cross.Y;
    Z = W * other.Z + other.W * Z + cross.Z;
    W = W * other.W - dot;

    return *this;
}

template<typename T>
constexpr Vector3<T> Quaternion<T>::operator*(const Vector3<T>& v) const
{
    T dot1            = X * v.X + Y * v.Y + Z * v.Z;
    Vector3<T> cross1 = Vector3( 
        Y * v.Z - Z * v.Y, 
        Z * v.X - X * v.Z,
        X * v.Y - Y * v.X 
    );

    Quaternion<T> q = Quaternion(
        W * v.X + cross1.X,
        W * v.Y + cross1.Y,
        W * v.Z + cross1.Z,
        -dot1
    );
    Quaternion<T> conj = GetConjugated();

    Vector3<T> cross2 = Vector3( 
        q.Y * conj.Z - q.Z * conj.Y, 
        q.Z * conj.X - q.X * conj.Z,
        q.X * conj.Y - q.Y * conj.X 
    );
    
    return Vector3<T>(
        q.W * conj.X + conj.W * q.X + cross2.X,
        q.W * conj.Y + conj.W * q.Y + cross2.Y,
        q.W * conj.Z + conj.W * q.Z + cross2.Z
    );
}

template<typename T>
constexpr Quaternion<T> Quaternion<T>::operator/(const T value) const
{
    return Quaternion(X / value, Y / value, Z / value, W / value);
}

template<typename T>
constexpr Quaternion<T>& Quaternion<T>::operator/=(const T value)
{
    X /= value;
    Y /= value;
    Z /= value;
    W /= value;

    return *this;
}

template<typename T>
constexpr bool Quaternion<T>::operator==(const Quaternion<T>& other) const
{
    return X == other.X && 
           Y == other.Y && 
           Z == other.Z &&
           W == other.W;
}

template<typename T>
constexpr bool Quaternion<T>::operator!=(const Quaternion<T>& other) const
{
    return X != other.X || 
           Y != other.Y || 
           Z != other.Z ||
           W != other.W;
}

//! Operations
template<typename T>
constexpr T Quaternion<T>::Dot(const Quaternion& other) const
{
    return X * other.X + Y * other.Y + Z * other.Z + W * other.W;
}

template<typename T>
constexpr T Quaternion<T>::Length() const
{
    return std::sqrt(X * X + Y * Y + Z * Z + W * W);
}

template<typename T>
constexpr T Quaternion<T>::LengthSquared() const
{
    return X * X + Y * Y + Z * Z + W * W;
}

template<typename T>
constexpr Quaternion<T> Quaternion<T>::GetNormalized() const
{
    T l = std::sqrt(X * X + Y * Y + Z * Z + W * W);

    return Quaternion(X / l, Y / l, Z / l, W / l);
}

template<typename T>
constexpr Quaternion<T> Quaternion<T>::GetSafeNormalized() const
{
    T l = std::sqrt(X * X + Y * Y + Z * Z + W * W);

    if(l != 0)
        return Quaternion(X / l, Y / l, Z / l, W / l);

    return Quaternion(X, Y, Z, W);
}

template<typename T>
constexpr Quaternion<T> Quaternion<T>::GetConjugated() const
{
    return Quaternion(-X, -Y, -Z, W);
}

template<typename T>
constexpr Quaternion<T> Quaternion<T>::GetInverse() const
{
    T ls = X * X + Y * Y + Z * Z + W * W;
    return Quaternion(-X / ls, -Y / ls, -Z / ls, W / ls); 
}

template<typename T>
constexpr Matrix4<T> Quaternion<T>::ToMatrix4() const
{
    T ww = W * W;
    T xy = X * Y;
    T xz = X * Z;
    T xw = X * W;
    T yz = Y * Z;
    T yw = Y * W;
    T zw = Z * W;

    return Matrix4<T>(
        2 * (ww + X*X) - 1,
        2 * (xy + zw),
        2 * (xz - yw),
        0,
        2 * (xy - zw),
        2 * (ww + Y*Y) - 1,
        2 * (yz + xw),
        0,
        2 * (xz + yw),
        2 * (yz - xw),
        2 * (ww + Z*Z) - 1,
        0,
        0,
        0,
        0,
        1
    );
}


template<typename T>
constexpr Quaternion<T> Quaternion<T>::FromAxis(const Vector3<T>& axis, T radians)
{
    T halfAngle = radians * 0.5;
    T cos       = std::cos(halfAngle);
    T sin       = std::sin(halfAngle);

    return Quaternion(sin * axis.X, sin * axis.Y, sin * axis.Z, cos);
}

} //namespace Math