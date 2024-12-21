#include <cmath>

namespace Math
{

//! Constructors
template<typename T>
constexpr Vector3<T>::Vector3() : X{}, Y{}, Z{} { }

template<typename T>
constexpr Vector3<T>::Vector3(T value) : X{value}, Y{value}, Z{value} { }

template<typename T>
constexpr Vector3<T>::Vector3(T x, T y, T z) : X{x}, Y{y}, Z{z} { }

//! Operators
template<typename T>
constexpr T& Vector3<T>::operator[](std::size_t index)
{
    switch (index)
    {
        default:
        case 0: return X;
        case 1: return Y;
        case 2: return Z;
    }
}

template<typename T>
constexpr const T& Vector3<T>::operator[](std::size_t index) const
{
    switch (index)
    {
        default:
        case 0: return X;
        case 1: return Y;
        case 2: return Z;
    }
}

template<typename T>
constexpr Vector3<T> Vector3<T>::operator+(const Vector3<T>& other) const
{
    return Vector3(X + other.X, Y + other.Y, Z + other.Z);
}

template<typename T>
constexpr Vector3<T>& Vector3<T>::operator+=(const Vector3<T>& other)
{
    X += other.X;
    Y += other.Y;
    Z += other.Z;
    return *this;
}

template<typename T>
constexpr Vector3<T> Vector3<T>::operator-(const Vector3<T>& other) const
{
    return Vector3(X - other.X, Y - other.Y, Z - other.Z);
}

template<typename T>
constexpr Vector3<T>& Vector3<T>::operator-=(const Vector3<T>& other)
{
    X -= other.X;
    Y -= other.Y;
    Z -= other.Z;
    return *this;
}

template<typename T>
constexpr Vector3<T> Vector3<T>::operator*(const T value) const
{
    return Vector3(X * value, Y * value, Z * value);
}

template<typename T>
constexpr Vector3<T>& Vector3<T>::operator*=(const T value)
{
    X *= value;
    Y *= value;
    Z *= value;
    return *this;
}

template<typename T>
constexpr Vector3<T> Vector3<T>::operator*(const Vector3<T>& other) const
{
    return Vector3(X * other.X, Y * other.Y, Z * other.Z);
}

template<typename T>
constexpr Vector3<T>& Vector3<T>::operator*=(const Vector3<T>& other)
{
    X *= other.X;
    Y *= other.Y;
    Z *= other.Z;
    return *this;
}

template<typename T>
constexpr Vector3<T> Vector3<T>::operator/(const T value) const
{
    return Vector3(X / value, Y / value, Z / value);
}

template<typename T>
constexpr Vector3<T>& Vector3<T>::operator/=(const T value)
{
    X /= value;
    Y /= value;
    Z /= value;
    return *this;
}

template<typename T>
constexpr Vector3<T> Vector3<T>::operator/(const Vector3<T>& other) const
{
    return Vector3(X / other.X, Y / other.Y, Z / other.Z);
}

template<typename T>
constexpr Vector3<T>& Vector3<T>::operator/=(const Vector3<T>& other)
{
    X /= other.X;
    Y /= other.Y;
    Z /= other.Z;
    return *this;
}

template<typename T>
constexpr bool Vector3<T>::operator==(const Vector3<T>& other) const
{
    return X == other.X && 
           Y == other.Y && 
           Z == other.Z;
}

template<typename T>
constexpr bool Vector3<T>::operator!=(const Vector3<T>& other) const
{
    return X != other.X || 
           Y != other.Y || 
           Z != other.Z;
}

//! Operations
template<typename T>
constexpr T Vector3<T>::Dot(const Vector3<T>& other) const 
{
    return X * other.X + Y * other.Y + Z * other.Z;
}

template<typename T>
constexpr T Vector3<T>::Length() const
{
    return std::sqrt(X * X + Y * Y + Z * Z);
}

template<typename T>
constexpr T Vector3<T>::LengthSquared() const
{
    return X * X + Y * Y + Z * Z;
}

template<typename T>
constexpr Vector3<T> Vector3<T>::Cross(const Vector3& other) const
{
    return Vector3(Y * other.Z - Z * other.Y,
                   Z * other.X - X * other.Z,
                   X * other.Y - Y * other.X);
}

template<typename T>
constexpr Vector3<T> Vector3<T>::GetNormalized() const
{
    T l = std::sqrt(X * X + Y * Y + Z * Z);

    return Vector3(X / l, Y / l, Z / l);
}

template<typename T>
constexpr Vector3<T> Vector3<T>::GetSafeNormalized() const
{
    T l = std::sqrt(X * X + Y * Y + Z * Z);

    if(l != 0)
        return Vector3(X / l, Y / l, Z / l);

    return Vector3(X, Y, Z);
}

template<typename T>
constexpr Vector3<T> Vector3<T>::GetReflected(const Vector3<T>& normal) const
{
    T proj = Dot(normal) * 2;

    return Vector3(X - normal.X * proj, 
                   Y - normal.Y * proj,
                   Z - normal.Z * proj);
}

} //namespace Math