#include <cmath>
#include "../matrix/Matrix4.hpp"

namespace math
{

//! Constructors
template<typename T>
constexpr Quaternion<T>::Quaternion() : x{}, y{}, z{}, w{} { }

template<typename T>
constexpr Quaternion<T>::Quaternion(T x, T y, T z, T w) : x{x}, y{y}, z{z}, w{w} { }

//! Operators
template<typename T>
constexpr T& Quaternion<T>::operator[](std::size_t index)
{
    switch (index)
    {
        default:
        case 0: return x;
        case 1: return y;
        case 2: return z;
        case 3: return w;
    }
}

template<typename T>
constexpr const T& Quaternion<T>::operator[](std::size_t index) const
{
    switch (index)
    {
        default:
        case 0: return x;
        case 1: return y;
        case 2: return z;
        case 3: return w;
    }
}

template<typename T>
constexpr Quaternion<T> Quaternion<T>::operator+(const Quaternion<T>& other) const
{
    return Quaternion(x + other.x, y + other.y, z + other.z, w + other.w);
}

template<typename T>
constexpr Quaternion<T>& Quaternion<T>::operator+=(const Quaternion<T>& other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    w += other.w;

    return *this;
}

template<typename T>
constexpr Quaternion<T> Quaternion<T>::operator-(const Quaternion<T>& other) const
{
    return Quaternion(x - other.x, y - other.y, z - other.z, w - other.w);
}

template<typename T>
constexpr Quaternion<T>& Quaternion<T>::operator-=(const Quaternion<T>& other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    w -= other.w;

    return *this;
}

template<typename T>
constexpr Quaternion<T> Quaternion<T>::operator*(const T value) const
{
    return Quaternion(x * value, y * value, z * value, w * value);
}

template<typename T>
constexpr Quaternion<T>& Quaternion<T>::operator*=(const T value)
{
    x *= value;
    y *= value;
    z *= value;
    w *= value;

    return *this;
}

template<typename T>
constexpr Quaternion<T> Quaternion<T>::operator*(const Quaternion<T>& other) const
{
    T dot            = x * other.x + y * other.y + z * other.z;
    Vector3<T> cross = Vector3 { 
        y * other.z - z * other.y, 
        z * other.x - x * other.z,
        x * other.y - y * other.x 
    };
    
    return Quaternion(
        w * other.x + other.w * x + cross.x,
        w * other.y + other.w * y + cross.y,
        w * other.z + other.w * z + cross.z,
        w * other.w - dot 
    );
}

template<typename T>
constexpr Quaternion<T>& Quaternion<T>::operator*=(const Quaternion<T>& other)
{
    T dot            = x * other.x + y * other.y + z * other.z;
    Vector3<T> cross = Vector3 { 
        y * other.z - z * other.y, 
        z * other.x - x * other.z,
        x * other.y - y * other.x 
    };

    x = w * other.x + other.w * x + cross.x;
    y = w * other.y + other.w * y + cross.y;
    z = w * other.z + other.w * z + cross.z;
    w = w * other.w - dot;

    return *this;
}

template<typename T>
constexpr Quaternion<T> Quaternion<T>::operator/(const T value) const
{
    T invValue = 1 / value;

    return Quaternion(x * invValue, y * invValue, z * invValue, w * invValue);
}

template<typename T>
constexpr Quaternion<T>& Quaternion<T>::operator/=(const T value)
{
    T invValue = 1 / value;

    x *= invValue;
    y *= invValue;
    z *= invValue;
    w *= invValue;

    return *this;
}

template<typename T>
constexpr bool Quaternion<T>::operator==(const Quaternion<T>& other) const
{
    return x == other.x && 
           y == other.y && 
           z == other.z &&
           w == other.w;
}

template<typename T>
constexpr bool Quaternion<T>::operator!=(const Quaternion<T>& other) const
{
    return x != other.x || 
           y != other.y || 
           z != other.z ||
           w != other.w;
}

//! Operations
template<typename T>
constexpr T Quaternion<T>::Dot(const Quaternion& other) const
{
    return x * other.x + y * other.y + z * other.z + w * other.w;
}

template<typename T>
constexpr T Quaternion<T>::Length() const
{
    return std::sqrt(x * x + y * y + z * z + w * w);
}

template<typename T>
constexpr T Quaternion<T>::LengthSquared() const
{
    return x * x + y * y + z * z + w * w;
}

template<typename T>
constexpr Quaternion<T> Quaternion<T>::GetNormalized() const
{
    T invL = 1 / std::sqrt(x * x + y * y + z * z + w * w);

    return Quaternion(x * invL, y * invL, z * invL, w * invL);
}

template<typename T>
constexpr Quaternion<T> Quaternion<T>::GetSafeNormalized() const
{
    T l = std::sqrt(x * x + y * y + z * z + w * w);

    if(l != 0)
    {
        T invL = 1 / l;
        return Quaternion(x * invL, y * invL, z * invL, w * invL);
    }

    return Quaternion(x, y, z, w);
}

template<typename T>
constexpr Quaternion<T> Quaternion<T>::GetConjugated() const
{
    return Quaternion(-x, -y, -z, w);
}

template<typename T>
constexpr Quaternion<T> Quaternion<T>::GetInverse() const
{
    T invLs = 1 / (x * x + y * y + z * z + w * w);

    return Quaternion(-x * invLs, -y * invLs, -z * invLs, w * invLs); 
}

template<typename T>
constexpr Matrix4<T> Quaternion<T>::ToMatrix4() const
{
    T ww = w * w;
    T xy = x * y;
    T xz = x * z;
    T xw = x * w;
    T yz = y * z;
    T yw = y * w;
    T zw = z * w;

    return Matrix4<T>(
        2 * (ww + x*x) - 1,
        2 * (xy + zw),
        2 * (xz - yw),
        0,
        2 * (xy - zw),
        2 * (ww + y*y) - 1,
        2 * (yz + xw),
        0,
        2 * (xz + yw),
        2 * (yz - xw),
        2 * (ww + z*z) - 1,
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

    return Quaternion(sin * axis.x, sin * axis.y, sin * axis.z, cos);
}

} //namespace math