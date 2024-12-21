#include <cmath>

namespace Math
{

template<typename T>
constexpr Matrix2<T>::Matrix2() : 
    Arr{1, 0, 0, 1} { }

template<typename T>
constexpr Matrix2<T>::Matrix2(T value) : 
    Arr{value, 0, 0, value} { }

template<typename T>
constexpr Matrix2<T>::Matrix2(T m11, T m22) : 
    Arr{m11, 0, 0, m22} { }

template<typename T>
constexpr Matrix2<T>::Matrix2(T m11, T m21, T m12, T m22) : 
    Arr{m11, m21, m12, m22} { }

//! Operators

template<typename T>
constexpr T* Matrix2<T>::operator[](std::size_t index)
{
    return &Arr[index * NumColumns];
}

template<typename T>
constexpr const T* Matrix2<T>::operator[](std::size_t index) const
{
    return &Arr[index * NumColumns];
}

template<typename T>
constexpr Matrix2<T> Matrix2<T>::operator+(const Matrix2<T>& other) const
{
    return Matrix2(Arr[0] + other.Arr[0], Arr[1] + other.Arr[1], 
                   Arr[2] + other.Arr[2], Arr[3] + other.Arr[3]);
}

template<typename T>
constexpr Matrix2<T>& Matrix2<T>::operator+=(const Matrix2<T>& other)
{
    Arr[0] += other.Arr[0];
    Arr[1] += other.Arr[1];
    Arr[2] += other.Arr[2];
    Arr[3] += other.Arr[3];
    return *this;
}

template<typename T>
constexpr Matrix2<T> Matrix2<T>::operator-(const Matrix2<T>& other) const
{
    return Matrix2(Arr[0] - other.Arr[0], Arr[1] - other.Arr[1], 
                   Arr[2] - other.Arr[2], Arr[3] - other.Arr[3]);
}

template<typename T>
constexpr Matrix2<T>& Matrix2<T>::operator-=(const Matrix2<T>& other)
{
    Arr[0] -= other.Arr[0];
    Arr[1] -= other.Arr[1];
    Arr[2] -= other.Arr[2];
    Arr[3] -= other.Arr[3];
    return *this;
}

template<typename T>
constexpr Matrix2<T> Matrix2<T>::operator*(const T value) const
{
    return Matrix2(Arr[0] * value, Arr[1] * value, 
                   Arr[2] * value, Arr[3] * value);
}

template<typename T>
constexpr Matrix2<T>& Matrix2<T>::operator*=(const T value)
{
    Arr[0] *= value;
    Arr[1] *= value;
    Arr[2] *= value;
    Arr[3] *= value;
    return *this;
}

template<typename T>
constexpr Matrix2<T> Matrix2<T>::operator*(const Matrix2<T>& other) const
{
    return Matrix2(
        Arr[0] * other.Arr[0] + Arr[2] * other.Arr[1],
        Arr[1] * other.Arr[0] + Arr[3] * other.Arr[1], //1
        Arr[0] * other.Arr[2] + Arr[2] * other.Arr[3],
        Arr[1] * other.Arr[2] + Arr[3] * other.Arr[3]); //3
}

template<typename T>
constexpr Matrix2<T>& Matrix2<T>::operator*=(const Matrix2<T>& other)
{
    T val1 = Arr[0] * other.Arr[0] + Arr[2] * other.Arr[1];
    T val2 = Arr[0] * other.Arr[2] + Arr[2] * other.Arr[3];

    Arr[0] = val1;
    Arr[2] = val2;

    val1 = Arr[1] * other.Arr[0] + Arr[3] * other.Arr[1];
    val2 = Arr[1] * other.Arr[2] + Arr[3] * other.Arr[3];

    Arr[1] = val1;
    Arr[3] = val2;

    return *this;
}

template<typename T>
constexpr Matrix2<T> Matrix2<T>::operator/(const T value) const
{
    return Matrix2(Arr[0] / value, Arr[1] / value, 
                   Arr[2] / value, Arr[3] / value);
}

template<typename T>
constexpr Matrix2<T>& Matrix2<T>::operator/=(const T value)
{
    Arr[0] /= value;
    Arr[1] /= value;
    Arr[2] /= value;
    Arr[3] /= value;
    return *this;
}

template<typename T>
constexpr bool Matrix2<T>::operator==(const Matrix2<T>& other) const
{
    return Arr[0] == other.Arr[0] && 
           Arr[1] == other.Arr[1] && 
           Arr[2] == other.Arr[2] &&
           Arr[3] == other.Arr[3];
}

template<typename T>
constexpr bool Matrix2<T>::operator!=(const Matrix2<T>& other) const
{
    return Arr[0] != other.Arr[0] || 
           Arr[1] != other.Arr[1] || 
           Arr[2] != other.Arr[2] ||
           Arr[3] != other.Arr[3];
}

//! Operations
template<typename T>
constexpr T Matrix2<T>::Determinant() const
{
    return Arr[0] * Arr[3] - Arr[1] * Arr[2];
}

template<typename T>
constexpr Matrix2<T> Matrix2<T>::GetInverse() const
{
    T det    = Determinant();
    T invDet = 1 / det;

    return Matrix2(
         invDet * Arr[3],
        -invDet * Arr[1],
         invDet * Arr[2],
        -invDet * Arr[0]
    );
}

template<typename T>
constexpr Matrix2<T> Matrix2<T>::GetTranspose() const
{
    return Matrix2(
        Arr[0],
        Arr[2],
        Arr[1],
        Arr[3]
    );
}

template<typename T>
constexpr Matrix2<T> Matrix2<T>::GetScaled(const Vector2<T> scale) const
{
    return Matrix2(
        Arr[0] * scale.X,
        Arr[1] * scale.X,
        Arr[2] * scale.Y,
        Arr[3] * scale.Y
    );
}

template<typename T>
constexpr Matrix2<T> Matrix2<T>::GetRotated(T radians) const
{
    T cos = std::cos(radians);
    T sin = std::sin(radians);

    return Matrix2(
         Arr[0] * cos + Arr[2] * sin,
         Arr[1] * cos + Arr[3] * sin,
        -Arr[0] * sin + Arr[2] * cos,
        -Arr[1] * sin + Arr[3] * cos
    );
}

template<typename T>
constexpr Matrix2<T> Matrix2<T>::CreateScale(const Vector2<T> scale)
{
    return Matrix2(
        scale.X,
        0,
        0,
        scale.Y
    );
}

template<typename T>
constexpr Matrix2<T> Matrix2<T>::CreateRotation(T radians)
{
    T cos = std::cos(radians);
    T sin = std::sin(radians);

    return Matrix2(
         cos,
         sin,
        -sin,
         cos
    );
}  

} //namespace Math