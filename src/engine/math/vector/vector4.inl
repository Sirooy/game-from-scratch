#include <cmath>

namespace Math
{

//! Constructors
template<typename T>
constexpr Vector4<T>::Vector4() : X{}, Y{}, Z{}, W{} { }

template<typename T>
constexpr Vector4<T>::Vector4(T value) : X{value}, Y{value}, Z{value}, W{value} { }

template<typename T>
constexpr Vector4<T>::Vector4(T x, T y, T z, T w) : X{x}, Y{y}, Z{z}, W{w} { }

//! Operators
template<typename T>
constexpr T& Vector4<T>::operator[](std::size_t index)
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
constexpr const T& Vector4<T>::operator[](std::size_t index) const
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
constexpr Vector4<T> Vector4<T>::operator+(const Vector4<T>& other) const
{
    return Vector4(X + other.X, Y + other.Y, Z + other.Z, W + other.W);
}

template<typename T>
constexpr Vector4<T>& Vector4<T>::operator+=(const Vector4<T>& other)
{
    X += other.X;
    Y += other.Y;
    Z += other.Z;
    W += other.W;

    return *this;
}

template<typename T>
constexpr Vector4<T> Vector4<T>::operator-(const Vector4<T>& other) const
{
    return Vector4(X - other.X, Y - other.Y, Z - other.Z, W - other.W);
}

template<typename T>
constexpr Vector4<T>& Vector4<T>::operator-=(const Vector4<T>& other)
{
    X -= other.X;
    Y -= other.Y;
    Z -= other.Z;
    W -= other.W;

    return *this;
}

template<typename T>
constexpr Vector4<T> Vector4<T>::operator*(const T value) const
{
    return Vector4(X * value, Y * value, Z * value, W * value);
}

template<typename T>
constexpr Vector4<T>& Vector4<T>::operator*=(const T value)
{
    X *= value;
    Y *= value;
    Z *= value;
    W *= value;

    return *this;
}

template<typename T>
constexpr Vector4<T> Vector4<T>::operator*(const Vector4<T>& other) const
{
    return Vector4(X * other.X, Y * other.Y, Z * other.Z, W * other.W);
}

template<typename T>
constexpr Vector4<T>& Vector4<T>::operator*=(const Vector4<T>& other)
{
    X *= other.X;
    Y *= other.Y;
    Z *= other.Z;
    W *= other.W;

    return *this;
}

template<typename T>
constexpr Vector4<T> Vector4<T>::operator/(const T value) const
{
    return Vector4(X / value, Y / value, Z / value, W / value);
}

template<typename T>
constexpr Vector4<T>& Vector4<T>::operator/=(const T value)
{
    X /= value;
    Y /= value;
    Z /= value;
    W /= value;

    return *this;
}

template<typename T>
constexpr Vector4<T> Vector4<T>::operator/(const Vector4<T>& other) const
{
    return Vector4(X / other.X, Y / other.Y, Z / other.Z, W / other.W);
}

template<typename T>
constexpr Vector4<T>& Vector4<T>::operator/=(const Vector4<T>& other)
{
    X /= other.X;
    Y /= other.Y;
    Z /= other.Z;
    W /= other.W;
    
    return *this;
}

template<typename T>
constexpr bool Vector4<T>::operator==(const Vector4<T>& other) const
{
    return X == other.X && 
           Y == other.Y && 
           Z == other.Z &&
           W == other.W;
}

template<typename T>
constexpr bool Vector4<T>::operator!=(const Vector4<T>& other) const
{
    return X != other.X || 
           Y != other.Y || 
           Z != other.Z ||
           W != other.W;
}

//! Operations
template<typename T>
constexpr T Vector4<T>::Dot(const Vector4<T>& other) const 
{
    return X * other.X + Y * other.Y + Z * other.Z + W * other.W;
}

template<typename T>
constexpr T Vector4<T>::Length() const
{
    return std::sqrt(X * X + Y * Y + Z * Z + W * W);
}

template<typename T>
constexpr T Vector4<T>::LengthSquared() const
{
    return X * X + Y * Y + Z * Z + W * W;
}

template<typename T>
constexpr Vector4<T> Vector4<T>::GetNormalized() const
{
    T l = std::sqrt(X * X + Y * Y + Z * Z + W * W);

    return Vector4(X / l, Y / l, Z / l, W / l);
}

template<typename T>
constexpr Vector4<T> Vector4<T>::GetSafeNormalized() const
{
    T l = std::sqrt(X * X + Y * Y + Z * Z + W * W);

    if(l != 0)
        return Vector4(X / l, Y / l, Z / l, W / l);

    return Vector4(X, Y, Z, W);
}

} //namespace Math