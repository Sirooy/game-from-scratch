#include <cmath>
#include "../vector/Vector3.hpp"
#include "../vector/Vector4.hpp"
#include "../quat/quaternion.hpp"

namespace math
{

//! Constructors
template<typename T>
constexpr Matrix4<T>::Matrix4() : 
    arr{1, 0, 0, 0, 
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1} { }

template<typename T>
constexpr Matrix4<T>::Matrix4(T value) : 
    arr{value, 0, 0, 0,
        0, value, 0, 0,
        0, 0, value, 0,
        0, 0, 0, value} { }

template<typename T>
constexpr Matrix4<T>::Matrix4(T m11, T m22, T m33, T m44) : 
    arr{m11, 0, 0, 0, 
        0, m22, 0, 0, 
        0, 0, m33, 0,
        0, 0, 0, m44} { }

template<typename T>
constexpr Matrix4<T>::Matrix4(T m11, T m21, T m31, T m41, T m12, T m22, T m32, T m42, 
        T m13, T m23, T m33, T m43, T m14, T m24, T m34, T m44) : 
    arr{m11, m21, m31, m41,
        m12, m22, m32, m42,
        m13, m23, m33, m43,
        m14, m24, m34, m44} { }

//! Operators
template<typename T>
constexpr T* Matrix4<T>::operator[](std::size_t index)
{
    return &arr[index * NumColumns];
}

template<typename T>
constexpr const T* Matrix4<T>::operator[](std::size_t index) const
{
    return &arr[index * NumColumns];
}

template<typename T>
constexpr Matrix4<T> Matrix4<T>::operator+(const Matrix4<T>& other) const
{
    return Matrix4(
        arr[0]  + other.arr[0],  arr[1]  + other.arr[1],  arr[2]  + other.arr[2],  arr[3]  + other.arr[3],
        arr[4]  + other.arr[4],  arr[5]  + other.arr[5],  arr[6]  + other.arr[6],  arr[7]  + other.arr[7],
        arr[8]  + other.arr[8],  arr[9]  + other.arr[9],  arr[10] + other.arr[10], arr[11] + other.arr[11],
        arr[12] + other.arr[12], arr[13] + other.arr[13], arr[14] + other.arr[14], arr[15] + other.arr[15]
    );
}

template<typename T>
constexpr Matrix4<T>& Matrix4<T>::operator+=(const Matrix4<T>& other)
{
    arr[0]  += other.arr[0];
    arr[1]  += other.arr[1];
    arr[2]  += other.arr[2];
    arr[3]  += other.arr[3];
    arr[4]  += other.arr[4];
    arr[5]  += other.arr[5];
    arr[6]  += other.arr[6];
    arr[7]  += other.arr[7];
    arr[8]  += other.arr[8];
    arr[9]  += other.arr[9];
    arr[10] += other.arr[10];
    arr[11] += other.arr[11];
    arr[12] += other.arr[12];
    arr[13] += other.arr[13];
    arr[14] += other.arr[14];
    arr[15] += other.arr[15];

    return *this;
}

template<typename T>
constexpr Matrix4<T> Matrix4<T>::operator-(const Matrix4<T>& other) const
{
    return Matrix4(
        arr[0]  - other.arr[0],  arr[1]  - other.arr[1],  arr[2]  - other.arr[2],  arr[3]  - other.arr[3],
        arr[4]  - other.arr[4],  arr[5]  - other.arr[5],  arr[6]  - other.arr[6],  arr[7]  - other.arr[7],
        arr[8]  - other.arr[8],  arr[9]  - other.arr[9],  arr[10] - other.arr[10], arr[11] - other.arr[11],
        arr[12] - other.arr[12], arr[13] - other.arr[13], arr[14] - other.arr[14], arr[15] - other.arr[15]
    );
}

template<typename T>
constexpr Matrix4<T>& Matrix4<T>::operator-=(const Matrix4<T>& other)
{
    arr[0]  -= other.arr[0];
    arr[1]  -= other.arr[1];
    arr[2]  -= other.arr[2];
    arr[3]  -= other.arr[3];
    arr[4]  -= other.arr[4];
    arr[5]  -= other.arr[5];
    arr[6]  -= other.arr[6];
    arr[7]  -= other.arr[7];
    arr[8]  -= other.arr[8];
    arr[9]  -= other.arr[9];
    arr[10] -= other.arr[10];
    arr[11] -= other.arr[11];
    arr[12] -= other.arr[12];
    arr[13] -= other.arr[13];
    arr[14] -= other.arr[14];
    arr[15] -= other.arr[15];

    return *this;
}

template<typename T>
constexpr Matrix4<T> Matrix4<T>::operator*(const T value) const
{
    return Matrix4(
        arr[0]  * value, arr[1]  * value, arr[2]  * value, arr[3]  * value,
        arr[4]  * value, arr[5]  * value, arr[6]  * value, arr[7]  * value,
        arr[8]  * value, arr[9]  * value, arr[10] * value, arr[11] * value,
        arr[12] * value, arr[13] * value, arr[14] * value, arr[15] * value
    );
}

template<typename T>
constexpr Matrix4<T>& Matrix4<T>::operator*=(const T value)
{
    arr[0]  *= value;
    arr[1]  *= value;
    arr[2]  *= value;
    arr[3]  *= value;
    arr[4]  *= value;
    arr[5]  *= value;
    arr[6]  *= value;
    arr[7]  *= value;
    arr[8]  *= value;
    arr[9]  *= value;
    arr[10] *= value;
    arr[11] *= value;
    arr[12] *= value;
    arr[13] *= value;
    arr[14] *= value;
    arr[15] *= value;

    return *this;
}

template<typename T>
constexpr Vector4<T> Matrix4<T>::operator*(const Vector4<T>& v) const
{
    return Vector4(
        arr[0] * v.x + arr[4] * v.y + arr[8]  * v.z + arr[12] * v.w,
        arr[1] * v.x + arr[5] * v.y + arr[9]  * v.z + arr[13] * v.w,
        arr[2] * v.x + arr[6] * v.y + arr[10] * v.z + arr[14] * v.w,
        arr[3] * v.x + arr[7] * v.y + arr[11] * v.z + arr[15] * v.w
    );
}


template<typename T>
constexpr Matrix4<T> Matrix4<T>::operator*(const Matrix4<T>& other) const
{
    return Matrix4(
        arr[0] * other.arr[0]  + arr[4] * other.arr[1]  + arr[8]  * other.arr[2]  + arr[12] * other.arr[3],
        arr[1] * other.arr[0]  + arr[5] * other.arr[1]  + arr[9]  * other.arr[2]  + arr[13] * other.arr[3],
        arr[2] * other.arr[0]  + arr[6] * other.arr[1]  + arr[10] * other.arr[2]  + arr[14] * other.arr[3],
        arr[3] * other.arr[0]  + arr[7] * other.arr[1]  + arr[11] * other.arr[2]  + arr[15] * other.arr[3],
        arr[0] * other.arr[4]  + arr[4] * other.arr[5]  + arr[8]  * other.arr[6]  + arr[12] * other.arr[7],
        arr[1] * other.arr[4]  + arr[5] * other.arr[5]  + arr[9]  * other.arr[6]  + arr[13] * other.arr[7],
        arr[2] * other.arr[4]  + arr[6] * other.arr[5]  + arr[10] * other.arr[6]  + arr[14] * other.arr[7],
        arr[3] * other.arr[4]  + arr[7] * other.arr[5]  + arr[11] * other.arr[6]  + arr[15] * other.arr[7],
        arr[0] * other.arr[8]  + arr[4] * other.arr[9]  + arr[8]  * other.arr[10] + arr[12] * other.arr[11],
        arr[1] * other.arr[8]  + arr[5] * other.arr[9]  + arr[9]  * other.arr[10] + arr[13] * other.arr[11],
        arr[2] * other.arr[8]  + arr[6] * other.arr[9]  + arr[10] * other.arr[10] + arr[14] * other.arr[11],
        arr[3] * other.arr[8]  + arr[7] * other.arr[9]  + arr[11] * other.arr[10] + arr[15] * other.arr[11],
        arr[0] * other.arr[12] + arr[4] * other.arr[13] + arr[8]  * other.arr[14] + arr[12] * other.arr[15],
        arr[1] * other.arr[12] + arr[5] * other.arr[13] + arr[9]  * other.arr[14] + arr[13] * other.arr[15],
        arr[2] * other.arr[12] + arr[6] * other.arr[13] + arr[10] * other.arr[14] + arr[14] * other.arr[15],
        arr[3] * other.arr[12] + arr[7] * other.arr[13] + arr[11] * other.arr[14] + arr[15] * other.arr[15]
    );
}

template<typename T>
constexpr Matrix4<T>& Matrix4<T>::operator*=(const Matrix4<T>& other)
{
    //Row 1
    T val1 = arr[0] * other.arr[0]  + arr[4] * other.arr[1]  + arr[8] * other.arr[2]  + arr[12] * other.arr[3];
    T val2 = arr[0] * other.arr[4]  + arr[4] * other.arr[5]  + arr[8] * other.arr[6]  + arr[12] * other.arr[7];
    T val3 = arr[0] * other.arr[8]  + arr[4] * other.arr[9]  + arr[8] * other.arr[10] + arr[12] * other.arr[11];
    T val4 = arr[0] * other.arr[12] + arr[4] * other.arr[13] + arr[8] * other.arr[14] + arr[12] * other.arr[15];

    arr[0]  = val1;
    arr[4]  = val2;
    arr[8]  = val3;
    arr[12] = val4;

    //Row 2
    val1 = arr[1] * other.arr[0]  + arr[5] * other.arr[1]  + arr[9] * other.arr[2]  + arr[13] * other.arr[3];
    val2 = arr[1] * other.arr[4]  + arr[5] * other.arr[5]  + arr[9] * other.arr[6]  + arr[13] * other.arr[7];
    val3 = arr[1] * other.arr[8]  + arr[5] * other.arr[9]  + arr[9] * other.arr[10] + arr[13] * other.arr[11];
    val4 = arr[1] * other.arr[12] + arr[5] * other.arr[13] + arr[9] * other.arr[14] + arr[13] * other.arr[15];

    arr[1]  = val1;
    arr[5]  = val2;
    arr[9]  = val3;
    arr[13] = val4;

    //Row 3
    val1 = arr[2] * other.arr[0]  + arr[6] * other.arr[1]  + arr[10] * other.arr[2]  + arr[14] * other.arr[3];
    val2 = arr[2] * other.arr[4]  + arr[6] * other.arr[5]  + arr[10] * other.arr[6]  + arr[14] * other.arr[7];
    val3 = arr[2] * other.arr[8]  + arr[6] * other.arr[9]  + arr[10] * other.arr[10] + arr[14] * other.arr[11];
    val4 = arr[2] * other.arr[12] + arr[6] * other.arr[13] + arr[10] * other.arr[14] + arr[14] * other.arr[15];

    arr[2]  = val1;
    arr[6]  = val2;
    arr[10] = val3;
    arr[14] = val4;

    //Row 1
    val1 = arr[3] * other.arr[0]  + arr[7] * other.arr[1]  + arr[11] * other.arr[2]  + arr[15] * other.arr[3];
    val2 = arr[3] * other.arr[4]  + arr[7] * other.arr[5]  + arr[11] * other.arr[6]  + arr[15] * other.arr[7];
    val3 = arr[3] * other.arr[8]  + arr[7] * other.arr[9]  + arr[11] * other.arr[10] + arr[15] * other.arr[11];
    val4 = arr[3] * other.arr[12] + arr[7] * other.arr[13] + arr[11] * other.arr[14] + arr[15] * other.arr[15];

    arr[3]  = val1;
    arr[7]  = val2;
    arr[11] = val3;
    arr[15] = val4;

    return *this;
}

template<typename T>
constexpr Matrix4<T> Matrix4<T>::operator/(const T value) const
{
    T invValue = 1 / value;

    return Matrix4(
        arr[0]  * invValue, arr[1]  * invValue, arr[2]  * invValue, arr[3]  * invValue,
        arr[4]  * invValue, arr[5]  * invValue, arr[6]  * invValue, arr[7]  * invValue,
        arr[8]  * invValue, arr[9]  * invValue, arr[10] * invValue, arr[11] * invValue,
        arr[12] * invValue, arr[13] * invValue, arr[14] * invValue, arr[15] * invValue
    );
}

template<typename T>
constexpr Matrix4<T>& Matrix4<T>::operator/=(const T value)
{
    T invValue = 1 / value;

    arr[0]  *= invValue;
    arr[1]  *= invValue;
    arr[2]  *= invValue;
    arr[3]  *= invValue;
    arr[4]  *= invValue;
    arr[5]  *= invValue;
    arr[6]  *= invValue;
    arr[7]  *= invValue;
    arr[8]  *= invValue;
    arr[9]  *= invValue;
    arr[10] *= invValue;
    arr[11] *= invValue;
    arr[12] *= invValue;
    arr[13] *= invValue;
    arr[14] *= invValue;
    arr[15] *= invValue;

    return *this;
}

template<typename T>
constexpr bool Matrix4<T>::operator==(const Matrix4<T>& other) const
{
    return arr[0]  == other.arr[0]  && 
           arr[1]  == other.arr[1]  && 
           arr[2]  == other.arr[2]  &&
           arr[3]  == other.arr[3]  &&
           arr[4]  == other.arr[4]  &&
           arr[5]  == other.arr[5]  &&
           arr[6]  == other.arr[6]  &&
           arr[7]  == other.arr[7]  &&
           arr[8]  == other.arr[8]  &&
           arr[9]  == other.arr[9]  &&
           arr[10] == other.arr[10] &&
           arr[11] == other.arr[11] &&
           arr[12] == other.arr[12] &&
           arr[13] == other.arr[13] &&
           arr[14] == other.arr[14] &&
           arr[15] == other.arr[15];
}

template<typename T>
constexpr bool Matrix4<T>::operator!=(const Matrix4<T>& other) const
{
    return arr[0]  != other.arr[0]  || 
           arr[1]  != other.arr[1]  || 
           arr[2]  != other.arr[2]  ||
           arr[3]  != other.arr[3]  ||
           arr[4]  != other.arr[4]  ||
           arr[5]  != other.arr[5]  ||
           arr[6]  != other.arr[6]  ||
           arr[7]  != other.arr[7]  ||
           arr[8]  != other.arr[8]  ||
           arr[9]  != other.arr[9]  ||
           arr[10] != other.arr[10] ||
           arr[11] != other.arr[11] ||
           arr[12] != other.arr[12] ||
           arr[13] != other.arr[13] ||
           arr[14] != other.arr[14] ||
           arr[15] != other.arr[15];
}

//! Operations
//Laplace Expansion Theorem (https://en.wikipedia.org/wiki/Laplace_expansion)
template<typename T>
constexpr T Matrix4<T>::Determinant() const
{
    T b12 = arr[0] * arr[5]  - arr[1] * arr[4];
    T b13 = arr[0] * arr[9]  - arr[1] * arr[8];
    T b14 = arr[0] * arr[13] - arr[1] * arr[12];
    T b23 = arr[4] * arr[9]  - arr[5] * arr[8];
    T b24 = arr[4] * arr[13] - arr[5] * arr[12];
    T b34 = arr[8] * arr[13] - arr[9] * arr[12];

    T c12 = arr[2]  * arr[7]  - arr[3]  * arr[6];
    T c13 = arr[2]  * arr[11] - arr[3]  * arr[10];
    T c14 = arr[2]  * arr[15] - arr[3]  * arr[14];
    T c23 = arr[6]  * arr[11] - arr[7]  * arr[10];
    T c24 = arr[6]  * arr[15] - arr[7]  * arr[14];
    T c34 = arr[10] * arr[15] - arr[11] * arr[14];

    return b12 * c34 - b13 * c24 + b14 * c23 + b23 * c14 - b24 * c13 + b34 * c12;
}

//Laplace Expansion Theorem (https://en.wikipedia.org/wiki/Laplace_expansion)
template<typename T>
constexpr Matrix4<T> Matrix4<T>::GetInverse() const
{
    T b12 = arr[0] * arr[5]  - arr[1] * arr[4];
    T b13 = arr[0] * arr[9]  - arr[1] * arr[8];
    T b14 = arr[0] * arr[13] - arr[1] * arr[12];
    T b23 = arr[4] * arr[9]  - arr[5] * arr[8];
    T b24 = arr[4] * arr[13] - arr[5] * arr[12];
    T b34 = arr[8] * arr[13] - arr[9] * arr[12];

    T c12 = arr[2]  * arr[7]  - arr[3]  * arr[6];
    T c13 = arr[2]  * arr[11] - arr[3]  * arr[10];
    T c14 = arr[2]  * arr[15] - arr[3]  * arr[14];
    T c23 = arr[6]  * arr[11] - arr[7]  * arr[10];
    T c24 = arr[6]  * arr[15] - arr[7]  * arr[14];
    T c34 = arr[10] * arr[15] - arr[11] * arr[14];

    T det    = b12 * c34 - b13 * c24 + b14 * c23 + b23 * c14 - b24 * c13 + b34 * c12;
    T invDet = 1.0 / det; 
        
    //Store the cofactors transposed
    return Matrix4(
         (arr[5] * c34 - arr[9] * c24 + arr[13] * c23) * invDet,
        -(arr[1] * c34 - arr[9] * c14 + arr[13] * c13) * invDet,
         (arr[1] * c24 - arr[5] * c14 + arr[13] * c12) * invDet,
        -(arr[1] * c23 - arr[5] * c13 + arr[9] * c12) * invDet,
        -(arr[4] * c34 - arr[8] * c24 + arr[12] * c23) * invDet,
         (arr[0] * c34 - arr[8] * c14 + arr[12] * c13) * invDet,
        -(arr[0] * c24 - arr[4] * c14 + arr[12] * c12) * invDet,
         (arr[0] * c23 - arr[4] * c13 + arr[8] * c12) * invDet,
         (arr[7] * b34 - arr[11] * b24 + arr[15] * b23) * invDet,
        -(arr[3] * b34 - arr[11] * b14 + arr[15] * b13) * invDet,
         (arr[3] * b24 - arr[7] * b14 + arr[15] * b12) * invDet,
        -(arr[3] * b23 - arr[7] * b13 + arr[11] * b12) * invDet,
        -(arr[6] * b34 - arr[10] * b24 + arr[14] * b23) * invDet,
         (arr[2] * b34 - arr[10] * b14 + arr[14] * b13) * invDet,
        -(arr[2] * b24 - arr[6] * b14 + arr[14] * b12) * invDet,
         (arr[2] * b23 - arr[6] * b13 + arr[10] * b12) * invDet
    );
}

template<typename T>
constexpr Matrix4<T> Matrix4<T>::GetTranspose() const
{
    return Matrix4(
        arr[0],
        arr[4],
        arr[8],
        arr[12],
        arr[1],
        arr[5],
        arr[9],
        arr[13],
        arr[2],
        arr[6],
        arr[10],
        arr[14],
        arr[3],
        arr[7],
        arr[11],
        arr[15]
    );
}

template<typename T>
constexpr Matrix4<T> Matrix4<T>::GetScaled(const Vector3<T>& scale) const
{
    return Matrix4(
        arr[0]  * scale.x,
        arr[1]  * scale.x,
        arr[2]  * scale.x,
        arr[3]  * scale.x,
        arr[4]  * scale.y,
        arr[5]  * scale.y,
        arr[6]  * scale.y,
        arr[7]  * scale.y,
        arr[8]  * scale.z,
        arr[9]  * scale.z,
        arr[10] * scale.z,
        arr[11] * scale.z,
        arr[12],
        arr[13],
        arr[14],
        arr[15]
    );
}

template<typename T>
constexpr Matrix4<T> Matrix4<T>::GetRotatedX(T radians) const
{
    T cos = std::cos(radians);
    T sin = std::sin(radians);

    return Matrix4(
        arr[0],
        arr[1],
        arr[2],
        arr[3],
        arr[4] *  cos + arr[8]  * sin,
        arr[5] *  cos + arr[9]  * sin,
        arr[6] *  cos + arr[10] * cos,
        arr[7] *  cos + arr[11] * cos,
        arr[4] * -sin + arr[8]  * cos,
        arr[5] * -sin + arr[9]  * cos,
        arr[6] * -sin + arr[10] * cos,
        arr[7] * -sin + arr[11] * cos,
        arr[12],
        arr[13],
        arr[14],
        arr[15]
    );
}

template<typename T>
constexpr Matrix4<T> Matrix4<T>::GetRotatedY(T radians) const
{
    T cos = std::cos(radians);
    T sin = std::sin(radians);

    return Matrix4(
        arr[0] * cos - arr[8]  * sin,
        arr[1] * cos - arr[9]  * sin,
        arr[2] * cos - arr[10] * sin,
        arr[3] * cos - arr[11] * sin,
        arr[4],
        arr[5],
        arr[6],
        arr[7],
        arr[0] * sin + arr[8]  * cos,
        arr[1] * sin + arr[9]  * cos,
        arr[2] * sin + arr[10] * cos,
        arr[3] * sin + arr[11] * cos,
        arr[12],
        arr[13],
        arr[14],
        arr[15]
    );
}

template<typename T>
constexpr Matrix4<T> Matrix4<T>::GetRotatedZ(T radians) const
{
    T cos = std::cos(radians);
    T sin = std::sin(radians);

    return Matrix4(
        arr[0] *  cos + arr[4] * sin,
        arr[1] *  cos + arr[5] * sin,
        arr[2] *  cos + arr[6] * sin,
        arr[3] *  cos + arr[7] * sin,
        arr[0] * -sin + arr[4] * cos,
        arr[1] * -sin + arr[5] * cos,
        arr[2] * -sin + arr[6] * cos,
        arr[3] * -sin + arr[7] * cos,
        arr[8],
        arr[9],
        arr[10],
        arr[11],
        arr[12],
        arr[13],
        arr[14],
        arr[15]
    );
}

template<typename T>
constexpr Matrix4<T> Matrix4<T>::GetTranslated(const Vector3<T>& translation) const
{
    return Matrix4(
        arr[0],
        arr[1],
        arr[2],
        arr[3],
        arr[4],
        arr[5],
        arr[6],
        arr[7],
        arr[8],
        arr[9],
        arr[10],
        arr[11],
        arr[0] * translation.x + arr[4] * translation.y + arr[8]  * translation.z + arr[12],
        arr[1] * translation.x + arr[5] * translation.y + arr[9]  * translation.z + arr[13],
        arr[2] * translation.x + arr[6] * translation.y + arr[10] * translation.z + arr[14],
        arr[3] * translation.x + arr[7] * translation.y + arr[11] * translation.z + arr[15]
    );
}

template<typename T>
constexpr Matrix4<T> Matrix4<T>::CreateScale(const Vector3<T>& scale)
{
    return Matrix4(
        scale.x, 0, 0, 0,
        0, scale.y, 0, 0,
        0, 0, scale.z, 0,
        0, 0, 0, 1
    );
}

template<typename T>
constexpr Matrix4<T> Matrix4<T>::CreateRotationX(T radians)
{
    T cos = std::cos(radians);
    T sin = std::sin(radians);

    return Matrix4(
        1,  0, 0, 0,
        0,  cos, sin, 0,
        0, -sin, cos, 0,
        0, 0, 0, 1
    );
}

template<typename T>
constexpr Matrix4<T> Matrix4<T>::CreateRotationY(T radians)
{
    T cos = std::cos(radians);
    T sin = std::sin(radians);

    return Matrix4(
        cos, 0, -sin, 0,
        0, 1, 0, 0,
        sin, 0, cos, 0,
        0, 0, 0, 1
    );
}

template<typename T>
constexpr Matrix4<T> Matrix4<T>::CreateRotationZ(T radians)
{
    T cos = std::cos(radians);
    T sin = std::sin(radians);

    return Matrix4(
        cos,  sin, 0, 0,
        -sin, cos, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    );
}

template<typename T>
constexpr Matrix4<T> Matrix4<T>::CreateTranslation(const Vector3<T>& translation)
{
    return Matrix4(
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        translation.x, translation.y, translation.z, 1
    );
}

template<typename T>
constexpr Matrix4<T> Matrix4<T>::CreateLookAt(const Vector3<T>& center, 
    const Vector3<T>& target, const Vector3<T>& up)
{
    Vector3<T> front = (center - target).GetNormalized();
    Vector3<T> right = up.Cross(front).GetNormalized();
    Vector3<T> newUp = front.Cross(right).GetNormalized();
    Vector3<T> pos   = -center;

    T px = right.x * pos.x + right.y * pos.y + right.z * pos.z;
    T py = newUp.x * pos.x + newUp.y * pos.y + newUp.z * pos.z;
    T pz = front.x * pos.x + front.y * pos.y + front.z * pos.z;

    return Matrix4(
        right.x, newUp.x, front.x, 0,
        right.y, newUp.y, front.y, 0,
        right.z, newUp.z, front.z, 0,
        px, py, pz, 1
    );
}

template<typename T>
constexpr Matrix4<T> Matrix4<T>::CreatePerspective(T near, T far, T fov, T aspect)
{
    T a   = 1 / std::tan(fov * 0.5);
    T div = 1 / (near - far);
    T c   = far * div;
    T d   = (far * near) * div;

    return Matrix4(
        a / aspect, 0, 0, 0,
        0, -a, 0,  0,
        0,  0, c, -1,
        0,  0, d,  0
    );
}

template<typename T>
constexpr Matrix4<T> Matrix4<T>::CreateTransform(const Vector3<T>& scale, 
    const Quaternion<T>& rotation, const Vector3<T>& translation)
{
    Matrix4<T> m = rotation.ToMatrix4();

    m.arr[12] = translation.x;
    m.arr[13] = translation.y;
    m.arr[14] = translation.z;

    m.arr[0]  *= scale.x;
    m.arr[4]  *= scale.y;
    m.arr[8]  *= scale.z;

    m.arr[1]  *= scale.x;
    m.arr[5]  *= scale.y;
    m.arr[9]  *= scale.z; 

    m.arr[2]  *= scale.x;
    m.arr[6]  *= scale.y;
    m.arr[10] *= scale.z; 

    m.arr[3]  *= scale.x;
    m.arr[7]  *= scale.y;
    m.arr[11] *= scale.z;

    return m;
}

} //namespace math