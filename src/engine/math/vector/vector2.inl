#include <cmath>

namespace Math
{

//! Constructors
template<typename T>
constexpr Vector2<T>::Vector2() : X{}, Y{} { }

template<typename T>
constexpr Vector2<T>::Vector2(T value) : X{value}, Y{value} { }

template<typename T>
constexpr Vector2<T>::Vector2(T x, T y) : X{x}, Y{y} { }

//! Operators
template<typename T>
constexpr T& Vector2<T>::operator[](std::size_t index)
{
    switch (index)
    {
        default:
        case 0: return X;
        case 1: return Y;
    }
}

template<typename T>
constexpr const T& Vector2<T>::operator[](std::size_t index) const
{
    switch (index)
    {
        default:
        case 0: return X;
        case 1: return Y;
    }
}

template<typename T>
constexpr Vector2<T> Vector2<T>::operator+(const Vector2<T> other) const
{
    return Vector2(X + other.X, Y + other.Y);
}

template<typename T>
constexpr Vector2<T>& Vector2<T>::operator+=(const Vector2<T> other)
{
    X += other.X;
    Y += other.Y;

    return *this;
}

template<typename T>
constexpr Vector2<T> Vector2<T>::operator-(const Vector2<T> other) const
{
    return Vector2(X - other.X, Y - other.Y);
}

template<typename T>
constexpr Vector2<T>& Vector2<T>::operator-=(const Vector2<T> other)
{
    X -= other.X;
    Y -= other.Y;

    return *this;
}

template<typename T>
constexpr Vector2<T> Vector2<T>::operator*(const T value) const
{
    return Vector2(X * value, Y * value);
}

template<typename T>
constexpr Vector2<T>& Vector2<T>::operator*=(const T value)
{
    X *= value;
    Y *= value;

    return *this;
}

template<typename T>
constexpr Vector2<T> Vector2<T>::operator*(const Vector2<T> other) const
{
    return Vector2(X * other.X, Y * other.Y);
}

template<typename T>
constexpr Vector2<T>& Vector2<T>::operator*=(const Vector2<T> other)
{
    X *= other.X;
    Y *= other.Y;

    return *this;
}

template<typename T>
constexpr Vector2<T> Vector2<T>::operator/(const T value) const
{
    return Vector2(X / value, Y / value);
}

template<typename T>
constexpr Vector2<T>& Vector2<T>::operator/=(const T value)
{
    X /= value;
    Y /= value;

    return *this;
}

template<typename T>
constexpr Vector2<T> Vector2<T>::operator/(const Vector2<T> other) const
{
    return Vector2(X / other.X, Y / other.Y);
}

template<typename T>
constexpr Vector2<T>& Vector2<T>::operator/=(const Vector2<T> other)
{
    X /= other.X;
    Y /= other.Y;
    
    return *this;
}

template<typename T>
constexpr bool Vector2<T>::operator==(const Vector2<T> other) const
{
    return X == other.X && 
           Y == other.Y;
}

template<typename T>
constexpr bool Vector2<T>::operator!=(const Vector2<T> other) const
{
    return X != other.X || 
           Y != other.Y;
}

//! Operations
template<typename T>
constexpr T Vector2<T>::Dot(const Vector2<T> other) const 
{
    return X * other.X + Y * other.Y;
}

template<typename T>
constexpr T Vector2<T>::Length() const
{
    return std::sqrt(X * X + Y * Y);
}

template<typename T>
constexpr T Vector2<T>::LengthSquared() const
{
    return X * X + Y * Y;
}

template<typename T>
constexpr T Vector2<T>::Cross2D(const Vector2 other) const
{
    return X * other.Y - Y * other.X;
}

template<typename T>
constexpr Vector2<T> Vector2<T>::GetNormalized() const
{
    T l = std::sqrt(X * X + Y * Y);

    return Vector2(X / l, Y / l);
}

template<typename T>
constexpr Vector2<T> Vector2<T>::GetSafeNormalized() const
{
    T l = std::sqrt(X * X + Y * Y);

    if(l != 0)
        return Vector2(X / l, Y / l);

    return Vector2(X, Y);
}

template<typename T>
constexpr Vector2<T> Vector2<T>::GetReflected(const Vector2<T> normal) const
{
    T proj = Dot(normal) * 2;

    return Vector2(X - normal.X * proj, 
                   Y - normal.Y * proj);
}

template<typename T>
constexpr Vector2<T> Vector2<T>::GetRotated(T radians) const
{
    T cos = std::cos(radians);
    T sin = std::sin(radians);

    return Vector2(X + cos - Y * sin, 
                   X * sin + Y * cos);
}

} //namespace Math