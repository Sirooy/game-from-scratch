#include <cmath>

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
constexpr Vector3<T> Quaternion<T>::operator*(const Vector3<T>& v) const
{
    T dot1            = x * v.x + y * v.y + z * v.z;
    Vector3<T> cross1 = Vector3( 
        y * v.z - z * v.y, 
        z * v.x - x * v.z,
        x * v.y - y * v.x 
    );

    Quaternion<T> q = Quaternion(
        w * v.x + cross1.x,
        w * v.y + cross1.y,
        w * v.z + cross1.z,
        -dot1
    );
    Quaternion<T> conj = GetConjugated();

    Vector3<T> cross2 = Vector3( 
        q.y * conj.z - q.z * conj.y, 
        q.z * conj.x - q.x * conj.z,
        q.x * conj.y - q.y * conj.x 
    );
    
    return Vector3<T>(
        q.w * conj.x + conj.w * q.x + cross2.x,
        q.w * conj.y + conj.w * q.y + cross2.y,
        q.w * conj.z + conj.w * q.z + cross2.z
    );
}

template<typename T>
constexpr Quaternion<T> Quaternion<T>::operator/(const T value) const
{
    return Quaternion(x / value, y / value, z / value, w / value);
}

template<typename T>
constexpr Quaternion<T>& Quaternion<T>::operator/=(const T value)
{
    x /= value;
    y /= value;
    z /= value;
    w /= value;

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
    T l = std::sqrt(x * x + y * y + z * z + w * w);

    return Quaternion(x / l, y / l, z / l, w / l);
}

template<typename T>
constexpr Quaternion<T> Quaternion<T>::GetSafeNormalized() const
{
    T l = std::sqrt(x * x + y * y + z * z + w * w);

    if(l != 0)
        return Quaternion(x / l, y / l, z / l, w / l);

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
    T ls = x * x + y * y + z * z + w * w;
    return Quaternion(-x / ls, -y / ls, -z / ls, w / ls); 
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