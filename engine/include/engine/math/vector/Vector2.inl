#include <cmath>

namespace math
{

//! Constructors
template<typename T>
constexpr Vector2<T>::Vector2() : x{}, y{} { }

template<typename T>
constexpr Vector2<T>::Vector2(T value) : x{value}, y{value} { }

template<typename T>
constexpr Vector2<T>::Vector2(T x, T y) : x{x}, y{y} { }

//! Operators
template<typename T>
constexpr T& Vector2<T>::operator[](std::size_t index)
{
    switch (index)
    {
        default:
        case 0: return x;
        case 1: return y;
    }
}

template<typename T>
constexpr const T& Vector2<T>::operator[](std::size_t index) const
{
    switch (index)
    {
        default:
        case 0: return x;
        case 1: return y;
    }
}

template<typename T>
constexpr Vector2<T> Vector2<T>::operator+(const Vector2<T> other) const
{
    return Vector2(x + other.x, y + other.y);
}

template<typename T>
constexpr Vector2<T>& Vector2<T>::operator+=(const Vector2<T> other)
{
    x += other.x;
    y += other.y;

    return *this;
}

template<typename T>
constexpr Vector2<T> Vector2<T>::operator-(const Vector2<T> other) const
{
    return Vector2(x - other.x, y - other.y);
}

template<typename T>
constexpr Vector2<T>& Vector2<T>::operator-=(const Vector2<T> other)
{
    x -= other.x;
    y -= other.y;

    return *this;
}

template<typename T>
constexpr Vector2<T> Vector2<T>::operator*(const T value) const
{
    return Vector2(x * value, y * value);
}

template<typename T>
constexpr Vector2<T>& Vector2<T>::operator*=(const T value)
{
    x *= value;
    y *= value;

    return *this;
}

template<typename T>
constexpr Vector2<T> Vector2<T>::operator*(const Vector2<T> other) const
{
    return Vector2(x * other.x, y * other.y);
}

template<typename T>
constexpr Vector2<T>& Vector2<T>::operator*=(const Vector2<T> other)
{
    x *= other.x;
    y *= other.y;

    return *this;
}

template<typename T>
constexpr Vector2<T> Vector2<T>::operator/(const T value) const
{
    T invValue = 1 / value;

    return Vector2(x * invValue, y * invValue);
}

template<typename T>
constexpr Vector2<T>& Vector2<T>::operator/=(const T value)
{
    T invValue = 1 / value;

    x *= invValue;
    y *= invValue;

    return *this;
}

template<typename T>
constexpr Vector2<T> Vector2<T>::operator/(const Vector2<T> other) const
{
    return Vector2(x / other.x, y / other.y);
}

template<typename T>
constexpr Vector2<T>& Vector2<T>::operator/=(const Vector2<T> other)
{
    x /= other.x;
    y /= other.y;
    
    return *this;
}

template<typename T>
constexpr bool Vector2<T>::operator==(const Vector2<T> other) const
{
    return x == other.x && 
           y == other.y;
}

template<typename T>
constexpr bool Vector2<T>::operator!=(const Vector2<T> other) const
{
    return x != other.x || 
           y != other.y;
}

//! Operations
template<typename T>
constexpr T Vector2<T>::Dot(const Vector2<T> other) const 
{
    return x * other.x + y * other.y;
}

template<typename T>
constexpr T Vector2<T>::Length() const
{
    return std::sqrt(x * x + y * y);
}

template<typename T>
constexpr T Vector2<T>::LengthSquared() const
{
    return x * x + y * y;
}

template<typename T>
constexpr T Vector2<T>::Cross2D(const Vector2 other) const
{
    return x * other.y - y * other.x;
}

template<typename T>
constexpr Vector2<T> Vector2<T>::GetNormalized() const
{
    T invL = 1 / std::sqrt(x * x + y * y);

    return Vector2(x * invL, y * invL);
}

template<typename T>
constexpr Vector2<T> Vector2<T>::GetSafeNormalized() const
{
    T l = std::sqrt(x * x + y * y);

    if(l != 0)
    {
        T invL = 1 / l;
        return Vector2(x * invL, y * invL);
    }

    return Vector2(x, y);
}

template<typename T>
constexpr Vector2<T> Vector2<T>::GetReflected(const Vector2<T> normal) const
{
    T proj = Dot(normal) * 2;

    return Vector2(x - normal.x * proj, 
                   y - normal.y * proj);
}

template<typename T>
constexpr Vector2<T> Vector2<T>::GetRotated(T radians) const
{
    T cos = std::cos(radians);
    T sin = std::sin(radians);

    return Vector2(x + cos - y * sin, 
                   x * sin + y * cos);
}

} //namespace math