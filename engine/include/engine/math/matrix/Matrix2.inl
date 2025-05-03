#include <cmath>

namespace math
{

//! Constructors
template<typename T>
constexpr Matrix2<T>::Matrix2() : 
    arr{1, 0, 0, 1} { }

template<typename T>
constexpr Matrix2<T>::Matrix2(T value) : 
    arr{value, 0, 0, value} { }

template<typename T>
constexpr Matrix2<T>::Matrix2(T m11, T m22) : 
    arr{m11, 0, 0, m22} { }

template<typename T>
constexpr Matrix2<T>::Matrix2(T m11, T m21, T m12, T m22) : 
    arr{m11, m21, m12, m22} { }

//! Operators
template<typename T>
constexpr T* Matrix2<T>::operator[](std::size_t index)
{
    return &arr[index * NumColumns];
}

template<typename T>
constexpr const T* Matrix2<T>::operator[](std::size_t index) const
{
    return &arr[index * NumColumns];
}

template<typename T>
constexpr Matrix2<T> Matrix2<T>::operator+(const Matrix2<T>& other) const
{
    return Matrix2(
        arr[0] + other.arr[0], arr[1] + other.arr[1], 
        arr[2] + other.arr[2], arr[3] + other.arr[3]
    );
}

template<typename T>
constexpr Matrix2<T>& Matrix2<T>::operator+=(const Matrix2<T>& other)
{
    arr[0] += other.arr[0];
    arr[1] += other.arr[1];
    arr[2] += other.arr[2];
    arr[3] += other.arr[3];

    return *this;
}

template<typename T>
constexpr Matrix2<T> Matrix2<T>::operator-(const Matrix2<T>& other) const
{
    return Matrix2(
        arr[0] - other.arr[0], arr[1] - other.arr[1], 
        arr[2] - other.arr[2], arr[3] - other.arr[3]
    );
}

template<typename T>
constexpr Matrix2<T>& Matrix2<T>::operator-=(const Matrix2<T>& other)
{
    arr[0] -= other.arr[0];
    arr[1] -= other.arr[1];
    arr[2] -= other.arr[2];
    arr[3] -= other.arr[3];

    return *this;
}

template<typename T>
constexpr Matrix2<T> Matrix2<T>::operator*(const T value) const
{
    return Matrix2(
        arr[0] * value, arr[1] * value, 
        arr[2] * value, arr[3] * value
    );
}

template<typename T>
constexpr Matrix2<T>& Matrix2<T>::operator*=(const T value)
{
    arr[0] *= value;
    arr[1] *= value;
    arr[2] *= value;
    arr[3] *= value;

    return *this;
}

template<typename T>
constexpr Matrix2<T> Matrix2<T>::operator*(const Matrix2<T>& other) const
{
    return Matrix2(
        arr[0] * other.arr[0] + arr[2] * other.arr[1],
        arr[1] * other.arr[0] + arr[3] * other.arr[1],
        arr[0] * other.arr[2] + arr[2] * other.arr[3],
        arr[1] * other.arr[2] + arr[3] * other.arr[3]
    );
}

template<typename T>
constexpr Matrix2<T>& Matrix2<T>::operator*=(const Matrix2<T>& other)
{
    //Row 1
    T val1 = arr[0] * other.arr[0] + arr[2] * other.arr[1];
    T val2 = arr[0] * other.arr[2] + arr[2] * other.arr[3];

    arr[0] = val1;
    arr[2] = val2;

    //Row 2
    val1 = arr[1] * other.arr[0] + arr[3] * other.arr[1];
    val2 = arr[1] * other.arr[2] + arr[3] * other.arr[3];

    arr[1] = val1;
    arr[3] = val2;

    return *this;
}

template<typename T>
constexpr Matrix2<T> Matrix2<T>::operator/(const T value) const
{
    T invValue = 1 / value;

    return Matrix2(
        arr[0] * invValue, arr[1] * invValue, 
        arr[2] * invValue, arr[3] * invValue
    );
}

template<typename T>
constexpr Matrix2<T>& Matrix2<T>::operator/=(const T value)
{
    T invValue = 1 / value;
    
    arr[0] *= invValue;
    arr[1] *= invValue;
    arr[2] *= invValue;
    arr[3] *= invValue;

    return *this;
}

template<typename T>
constexpr bool Matrix2<T>::operator==(const Matrix2<T>& other) const
{
    return arr[0] == other.arr[0] && 
           arr[1] == other.arr[1] && 
           arr[2] == other.arr[2] &&
           arr[3] == other.arr[3];
}

template<typename T>
constexpr bool Matrix2<T>::operator!=(const Matrix2<T>& other) const
{
    return arr[0] != other.arr[0] || 
           arr[1] != other.arr[1] || 
           arr[2] != other.arr[2] ||
           arr[3] != other.arr[3];
}

//! Operations
template<typename T>
constexpr T Matrix2<T>::Determinant() const
{
    return arr[0] * arr[3] - arr[1] * arr[2];
}

template<typename T>
constexpr Matrix2<T> Matrix2<T>::GetInverse() const
{
    T det    = Determinant();
    T invDet = 1 / det;

    return Matrix2(
         invDet * arr[3],
        -invDet * arr[1],
         invDet * arr[2],
        -invDet * arr[0]
    );
}

template<typename T>
constexpr Matrix2<T> Matrix2<T>::GetTranspose() const
{
    return Matrix2(
        arr[0],
        arr[2],
        arr[1],
        arr[3]
    );
}

template<typename T>
constexpr Matrix2<T> Matrix2<T>::GetScaled(const Vector2<T> scale) const
{
    return Matrix2(
        arr[0] * scale.x,
        arr[1] * scale.x,
        arr[2] * scale.y,
        arr[3] * scale.y
    );
}

template<typename T>
constexpr Matrix2<T> Matrix2<T>::GetRotated(T radians) const
{
    T cos = std::cos(radians);
    T sin = std::sin(radians);

    return Matrix2(
         arr[0] * cos + arr[2] * sin,
         arr[1] * cos + arr[3] * sin,
        -arr[0] * sin + arr[2] * cos,
        -arr[1] * sin + arr[3] * cos
    );
}

template<typename T>
constexpr Matrix2<T> Matrix2<T>::CreateScale(const Vector2<T> scale)
{
    return Matrix2(
        scale.x, 0,
        0, scale.y
    );
}

template<typename T>
constexpr Matrix2<T> Matrix2<T>::CreateRotation(T radians)
{
    T cos = std::cos(radians);
    T sin = std::sin(radians);

    return Matrix2(
         cos, sin,
        -sin, cos
    );
}  

} //namespace math