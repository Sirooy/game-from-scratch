#include <cmath>

namespace math
{

//! Constructors
template<typename T>
constexpr Vector4<T>::Vector4() : x{}, y{}, z{}, w{} { }

template<typename T>
constexpr Vector4<T>::Vector4(T value) : x{value}, y{value}, z{value}, w{value} { }

template<typename T>
constexpr Vector4<T>::Vector4(T x, T y, T z, T w) : x{x}, y{y}, z{z}, w{w} { }

//! Operators
template<typename T>
constexpr T& Vector4<T>::operator[](std::size_t index)
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
constexpr const T& Vector4<T>::operator[](std::size_t index) const
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
constexpr Vector4<T> Vector4<T>::operator+(const Vector4<T>& other) const
{
    return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
}

template<typename T>
constexpr Vector4<T>& Vector4<T>::operator+=(const Vector4<T>& other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    w += other.w;

    return *this;
}

template<typename T>
constexpr Vector4<T> Vector4<T>::operator-(const Vector4<T>& other) const
{
    return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
}

template<typename T>
constexpr Vector4<T>& Vector4<T>::operator-=(const Vector4<T>& other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    w -= other.w;

    return *this;
}

template<typename T>
constexpr Vector4<T> Vector4<T>::operator*(const T value) const
{
    return Vector4(x * value, y * value, z * value, w * value);
}

template<typename T>
constexpr Vector4<T>& Vector4<T>::operator*=(const T value)
{
    x *= value;
    y *= value;
    z *= value;
    w *= value;

    return *this;
}

template<typename T>
constexpr Vector4<T> Vector4<T>::operator*(const Vector4<T>& other) const
{
    return Vector4(x * other.x, y * other.y, z * other.z, w * other.w);
}

template<typename T>
constexpr Vector4<T>& Vector4<T>::operator*=(const Vector4<T>& other)
{
    x *= other.x;
    y *= other.y;
    z *= other.z;
    w *= other.w;

    return *this;
}

template<typename T>
constexpr Vector4<T> Vector4<T>::operator/(const T value) const
{
    return Vector4(x / value, y / value, z / value, w / value);
}

template<typename T>
constexpr Vector4<T>& Vector4<T>::operator/=(const T value)
{
    x /= value;
    y /= value;
    z /= value;
    w /= value;

    return *this;
}

template<typename T>
constexpr Vector4<T> Vector4<T>::operator/(const Vector4<T>& other) const
{
    return Vector4(x / other.x, y / other.y, z / other.z, w / other.w);
}

template<typename T>
constexpr Vector4<T>& Vector4<T>::operator/=(const Vector4<T>& other)
{
    x /= other.x;
    y /= other.y;
    z /= other.z;
    w /= other.w;
    
    return *this;
}

template<typename T>
constexpr bool Vector4<T>::operator==(const Vector4<T>& other) const
{
    return x == other.x && 
           y == other.y && 
           z == other.z &&
           w == other.w;
}

template<typename T>
constexpr bool Vector4<T>::operator!=(const Vector4<T>& other) const
{
    return x != other.x || 
           y != other.y || 
           z != other.z ||
           w != other.w;
}

//! Operations
template<typename T>
constexpr T Vector4<T>::Dot(const Vector4<T>& other) const 
{
    return x * other.x + y * other.y + z * other.z + w * other.w;
}

template<typename T>
constexpr T Vector4<T>::Length() const
{
    return std::sqrt(x * x + y * y + z * z + w * w);
}

template<typename T>
constexpr T Vector4<T>::LengthSquared() const
{
    return x * x + y * y + z * z + w * w;
}

template<typename T>
constexpr Vector4<T> Vector4<T>::GetNormalized() const
{
    T l = std::sqrt(x * x + y * y + z * z + w * w);

    return Vector4(x / l, y / l, z / l, w / l);
}

template<typename T>
constexpr Vector4<T> Vector4<T>::GetSafeNormalized() const
{
    T l = std::sqrt(x * x + y * y + z * z + w * w);

    if(l != 0)
        return Vector4(x / l, y / l, z / l, w / l);

    return Vector4(x, y, z, w);
}

} //namespace math