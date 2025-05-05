#include <cmath>

namespace math
{

//! Constructors
template<typename T>
constexpr Vector3<T>::Vector3() : x{}, y{}, z{} { }

template<typename T>
constexpr Vector3<T>::Vector3(T value) : x{value}, y{value}, z{value} { }

template<typename T>
constexpr Vector3<T>::Vector3(T x, T y, T z) : x{x}, y{y}, z{z} { }

//! Operators
template<typename T>
constexpr T& Vector3<T>::operator[](std::size_t index)
{
    switch (index)
    {
        default:
        case 0: return x;
        case 1: return y;
        case 2: return z;
    }
}

template<typename T>
constexpr const T& Vector3<T>::operator[](std::size_t index) const
{
    switch (index)
    {
        default:
        case 0: return x;
        case 1: return y;
        case 2: return z;
    }
}

template<typename T>
constexpr Vector3<T> Vector3<T>::operator+(const Vector3<T>& other) const
{
    return Vector3(x + other.x, y + other.y, z + other.z);
}

template<typename T>
constexpr Vector3<T>& Vector3<T>::operator+=(const Vector3<T>& other)
{
    x += other.x;
    y += other.y;
    z += other.z;

    return *this;
}

template<typename T>
constexpr Vector3<T> Vector3<T>::operator-() const
{
    return Vector3(-x, -y, -z);
}


template<typename T>
constexpr Vector3<T> Vector3<T>::operator-(const Vector3<T>& other) const
{
    return Vector3(x - other.x, y - other.y, z - other.z);
}

template<typename T>
constexpr Vector3<T>& Vector3<T>::operator-=(const Vector3<T>& other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;

    return *this;
}

template<typename T>
constexpr Vector3<T> Vector3<T>::operator*(const T value) const
{
    return Vector3(x * value, y * value, z * value);
}

template<typename T>
constexpr Vector3<T>& Vector3<T>::operator*=(const T value)
{
    x *= value;
    y *= value;
    z *= value;

    return *this;
}

template<typename T>
constexpr Vector3<T> Vector3<T>::operator*(const Vector3<T>& other) const
{
    return Vector3(x * other.x, y * other.y, z * other.z);
}

template<typename T>
constexpr Vector3<T>& Vector3<T>::operator*=(const Vector3<T>& other)
{
    x *= other.x;
    y *= other.y;
    z *= other.z;

    return *this;
}

template<typename T>
constexpr Vector3<T> Vector3<T>::operator/(const T value) const
{
    T invValue = 1 / value;

    return Vector3(x * invValue, y * invValue, z * invValue);
}

template<typename T>
constexpr Vector3<T>& Vector3<T>::operator/=(const T value)
{
    T invValue = 1 / value;

    x *= invValue;
    y *= invValue;
    z *= invValue;

    return *this;
}

template<typename T>
constexpr Vector3<T> Vector3<T>::operator/(const Vector3<T>& other) const
{
    return Vector3(x / other.x, y / other.y, z / other.z);
}

template<typename T>
constexpr Vector3<T>& Vector3<T>::operator/=(const Vector3<T>& other)
{
    x /= other.x;
    y /= other.y;
    z /= other.z;
    
    return *this;
}

template<typename T>
constexpr bool Vector3<T>::operator==(const Vector3<T>& other) const
{
    return x == other.x && 
           y == other.y && 
           z == other.z;
}

template<typename T>
constexpr bool Vector3<T>::operator!=(const Vector3<T>& other) const
{
    return x != other.x || 
           y != other.y || 
           z != other.z;
}

//! Operations
template<typename T>
constexpr T Vector3<T>::Dot(const Vector3<T>& other) const 
{
    return x * other.x + y * other.y + z * other.z;
}

template<typename T>
constexpr T Vector3<T>::Length() const
{
    return std::sqrt(x * x + y * y + z * z);
}

template<typename T>
constexpr T Vector3<T>::LengthSquared() const
{
    return x * x + y * y + z * z;
}

template<typename T>
constexpr Vector3<T> Vector3<T>::Cross(const Vector3& other) const
{
    return Vector3(y * other.z - z * other.y,
                   z * other.x - x * other.z,
                   x * other.y - y * other.x);
}

template<typename T>
constexpr Vector3<T> Vector3<T>::GetNormalized() const
{
    T invL = 1 / std::sqrt(x * x + y * y + z * z);

    return Vector3(x * invL, y * invL, z * invL);
}

template<typename T>
constexpr Vector3<T> Vector3<T>::GetSafeNormalized() const
{
    T l = std::sqrt(x * x + y * y + z * z);

    if(l != 0)
    {
        T invL = 1 / l;
        return Vector3(x * invL, y * invL, z * invL);
    }

    return Vector3(x, y, z);
}

template<typename T>
constexpr Vector3<T> Vector3<T>::GetReflected(const Vector3<T>& normal) const
{
    T proj = Dot(normal) * 2;

    return Vector3(x - normal.x * proj, 
                   y - normal.y * proj,
                   z - normal.z * proj);
}

} //namespace math