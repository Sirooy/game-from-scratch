#include <cmath>

namespace Math
{

//! Constructors
template<typename T>
constexpr Matrix4<T>::Matrix4() : 
    Arr{1, 0, 0, 0, 
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1} { }

template<typename T>
constexpr Matrix4<T>::Matrix4(T value) : 
    Arr{value, 0, 0, 0,
        0, value, 0, 0,
        0, 0, value, 0,
        0, 0, 0, value} { }

template<typename T>
constexpr Matrix4<T>::Matrix4(T m11, T m22, T m33, T m44) : 
    Arr{m11, 0, 0, 0, 
        0, m22, 0, 0, 
        0, 0, m33, 0,
        0, 0, 0, m44} { }

template<typename T>
constexpr Matrix4<T>::Matrix4(T m11, T m21, T m31, T m41, T m12, T m22, T m32, T m42, 
        T m13, T m23, T m33, T m43, T m14, T m24, T m34, T m44) : 
    Arr{m11, m21, m31, m41,
        m12, m22, m32, m42,
        m13, m23, m33, m43,
        m14, m24, m34, m44} { }

//! Operators
template<typename T>
constexpr T* Matrix4<T>::operator[](std::size_t index)
{
    return &Arr[index * NumColumns];
}

template<typename T>
constexpr const T* Matrix4<T>::operator[](std::size_t index) const
{
    return &Arr[index * NumColumns];
}

template<typename T>
constexpr Matrix4<T> Matrix4<T>::operator+(const Matrix4<T>& other) const
{
    return Matrix4(
        Arr[0]  + other.Arr[0],  Arr[1]  + other.Arr[1],  Arr[2]  + other.Arr[2],  Arr[3]  + other.Arr[3],
        Arr[4]  + other.Arr[4],  Arr[5]  + other.Arr[5],  Arr[6]  + other.Arr[6],  Arr[7]  + other.Arr[7],
        Arr[8]  + other.Arr[8],  Arr[9]  + other.Arr[9],  Arr[10] + other.Arr[10], Arr[11] + other.Arr[11],
        Arr[12] + other.Arr[12], Arr[13] + other.Arr[13], Arr[14] + other.Arr[14], Arr[15] + other.Arr[15]
    );
}

template<typename T>
constexpr Matrix4<T>& Matrix4<T>::operator+=(const Matrix4<T>& other)
{
    Arr[0]  += other.Arr[0];
    Arr[1]  += other.Arr[1];
    Arr[2]  += other.Arr[2];
    Arr[3]  += other.Arr[3];
    Arr[4]  += other.Arr[4];
    Arr[5]  += other.Arr[5];
    Arr[6]  += other.Arr[6];
    Arr[7]  += other.Arr[7];
    Arr[8]  += other.Arr[8];
    Arr[9]  += other.Arr[9];
    Arr[10] += other.Arr[10];
    Arr[11] += other.Arr[11];
    Arr[12] += other.Arr[12];
    Arr[13] += other.Arr[13];
    Arr[14] += other.Arr[14];
    Arr[15] += other.Arr[15];

    return *this;
}

template<typename T>
constexpr Matrix4<T> Matrix4<T>::operator-(const Matrix4<T>& other) const
{
    return Matrix4(
        Arr[0]  - other.Arr[0],  Arr[1]  - other.Arr[1],  Arr[2]  - other.Arr[2],  Arr[3]  - other.Arr[3],
        Arr[4]  - other.Arr[4],  Arr[5]  - other.Arr[5],  Arr[6]  - other.Arr[6],  Arr[7]  - other.Arr[7],
        Arr[8]  - other.Arr[8],  Arr[9]  - other.Arr[9],  Arr[10] - other.Arr[10], Arr[11] - other.Arr[11],
        Arr[12] - other.Arr[12], Arr[13] - other.Arr[13], Arr[14] - other.Arr[14], Arr[15] - other.Arr[15]
    );
}

template<typename T>
constexpr Matrix4<T>& Matrix4<T>::operator-=(const Matrix4<T>& other)
{
    Arr[0]  -= other.Arr[0];
    Arr[1]  -= other.Arr[1];
    Arr[2]  -= other.Arr[2];
    Arr[3]  -= other.Arr[3];
    Arr[4]  -= other.Arr[4];
    Arr[5]  -= other.Arr[5];
    Arr[6]  -= other.Arr[6];
    Arr[7]  -= other.Arr[7];
    Arr[8]  -= other.Arr[8];
    Arr[9]  -= other.Arr[9];
    Arr[10] -= other.Arr[10];
    Arr[11] -= other.Arr[11];
    Arr[12] -= other.Arr[12];
    Arr[13] -= other.Arr[13];
    Arr[14] -= other.Arr[14];
    Arr[15] -= other.Arr[15];

    return *this;
}

template<typename T>
constexpr Matrix4<T> Matrix4<T>::operator*(const T value) const
{
    return Matrix4(
        Arr[0]  * value, Arr[1]  * value, Arr[2]  * value, Arr[3]  * value,
        Arr[4]  * value, Arr[5]  * value, Arr[6]  * value, Arr[7]  * value,
        Arr[8]  * value, Arr[9]  * value, Arr[10] * value, Arr[11] * value,
        Arr[12] * value, Arr[13] * value, Arr[14] * value, Arr[15] * value
    );
}

template<typename T>
constexpr Matrix4<T>& Matrix4<T>::operator*=(const T value)
{
    Arr[0]  *= value;
    Arr[1]  *= value;
    Arr[2]  *= value;
    Arr[3]  *= value;
    Arr[4]  *= value;
    Arr[5]  *= value;
    Arr[6]  *= value;
    Arr[7]  *= value;
    Arr[8]  *= value;
    Arr[9]  *= value;
    Arr[10] *= value;
    Arr[11] *= value;
    Arr[12] *= value;
    Arr[13] *= value;
    Arr[14] *= value;
    Arr[15] *= value;

    return *this;
}

template<typename T>
constexpr Vector4<T> Matrix4<T>::operator*(const Vector4<T>& v) const
{
    return Vector4(
        Arr[0] * v.X + Arr[4] * v.Y + Arr[8]  * v.Z + Arr[12] * v.W,
        Arr[1] * v.X + Arr[5] * v.Y + Arr[9]  * v.Z + Arr[13] * v.W,
        Arr[2] * v.X + Arr[6] * v.Y + Arr[10] * v.Z + Arr[14] * v.W,
        Arr[3] * v.X + Arr[7] * v.Y + Arr[11] * v.Z + Arr[15] * v.W
    );
}


template<typename T>
constexpr Matrix4<T> Matrix4<T>::operator*(const Matrix4<T>& other) const
{
    return Matrix4(
        Arr[0] * other.Arr[0]  + Arr[4] * other.Arr[1]  + Arr[8]  * other.Arr[2]  + Arr[12] * other.Arr[3],
        Arr[1] * other.Arr[0]  + Arr[5] * other.Arr[1]  + Arr[9]  * other.Arr[2]  + Arr[13] * other.Arr[3],
        Arr[2] * other.Arr[0]  + Arr[6] * other.Arr[1]  + Arr[10] * other.Arr[2]  + Arr[14] * other.Arr[3],
        Arr[3] * other.Arr[0]  + Arr[7] * other.Arr[1]  + Arr[11] * other.Arr[2]  + Arr[15] * other.Arr[3],
        Arr[0] * other.Arr[4]  + Arr[4] * other.Arr[5]  + Arr[8]  * other.Arr[6]  + Arr[12] * other.Arr[7],
        Arr[1] * other.Arr[4]  + Arr[5] * other.Arr[5]  + Arr[9]  * other.Arr[6]  + Arr[13] * other.Arr[7],
        Arr[2] * other.Arr[4]  + Arr[6] * other.Arr[5]  + Arr[10] * other.Arr[6]  + Arr[14] * other.Arr[7],
        Arr[3] * other.Arr[4]  + Arr[7] * other.Arr[5]  + Arr[11] * other.Arr[6]  + Arr[15] * other.Arr[7],
        Arr[0] * other.Arr[8]  + Arr[4] * other.Arr[9]  + Arr[8]  * other.Arr[10] + Arr[12] * other.Arr[11],
        Arr[1] * other.Arr[8]  + Arr[5] * other.Arr[9]  + Arr[9]  * other.Arr[10] + Arr[13] * other.Arr[11],
        Arr[2] * other.Arr[8]  + Arr[6] * other.Arr[9]  + Arr[10] * other.Arr[10] + Arr[14] * other.Arr[11],
        Arr[3] * other.Arr[8]  + Arr[7] * other.Arr[9]  + Arr[11] * other.Arr[10] + Arr[15] * other.Arr[11],
        Arr[0] * other.Arr[12] + Arr[4] * other.Arr[13] + Arr[8]  * other.Arr[14] + Arr[12] * other.Arr[15],
        Arr[1] * other.Arr[12] + Arr[5] * other.Arr[13] + Arr[9]  * other.Arr[14] + Arr[13] * other.Arr[15],
        Arr[2] * other.Arr[12] + Arr[6] * other.Arr[13] + Arr[10] * other.Arr[14] + Arr[14] * other.Arr[15],
        Arr[3] * other.Arr[12] + Arr[7] * other.Arr[13] + Arr[11] * other.Arr[14] + Arr[15] * other.Arr[15]
    );
}

template<typename T>
constexpr Matrix4<T>& Matrix4<T>::operator*=(const Matrix4<T>& other)
{
    //Row 1
    T val1 = Arr[0] * other.Arr[0]  + Arr[4] * other.Arr[1]  + Arr[8] * other.Arr[2]  + Arr[12] * other.Arr[3];
    T val2 = Arr[0] * other.Arr[4]  + Arr[4] * other.Arr[5]  + Arr[8] * other.Arr[6]  + Arr[12] * other.Arr[7];
    T val3 = Arr[0] * other.Arr[8]  + Arr[4] * other.Arr[9]  + Arr[8] * other.Arr[10] + Arr[12] * other.Arr[11];
    T val4 = Arr[0] * other.Arr[12] + Arr[4] * other.Arr[13] + Arr[8] * other.Arr[14] + Arr[12] * other.Arr[15];

    Arr[0]  = val1;
    Arr[4]  = val2;
    Arr[8]  = val3;
    Arr[12] = val4;

    //Row 2
    val1 = Arr[1] * other.Arr[0]  + Arr[5] * other.Arr[1]  + Arr[9] * other.Arr[2]  + Arr[13] * other.Arr[3];
    val2 = Arr[1] * other.Arr[4]  + Arr[5] * other.Arr[5]  + Arr[9] * other.Arr[6]  + Arr[13] * other.Arr[7];
    val3 = Arr[1] * other.Arr[8]  + Arr[5] * other.Arr[9]  + Arr[9] * other.Arr[10] + Arr[13] * other.Arr[11];
    val4 = Arr[1] * other.Arr[12] + Arr[5] * other.Arr[13] + Arr[9] * other.Arr[14] + Arr[13] * other.Arr[15];

    Arr[1]  = val1;
    Arr[5]  = val2;
    Arr[9]  = val3;
    Arr[13] = val4;

    //Row 3
    val1 = Arr[2] * other.Arr[0]  + Arr[6] * other.Arr[1]  + Arr[10] * other.Arr[2]  + Arr[14] * other.Arr[3];
    val2 = Arr[2] * other.Arr[4]  + Arr[6] * other.Arr[5]  + Arr[10] * other.Arr[6]  + Arr[14] * other.Arr[7];
    val3 = Arr[2] * other.Arr[8]  + Arr[6] * other.Arr[9]  + Arr[10] * other.Arr[10] + Arr[14] * other.Arr[11];
    val4 = Arr[2] * other.Arr[12] + Arr[6] * other.Arr[13] + Arr[10] * other.Arr[14] + Arr[14] * other.Arr[15];

    Arr[2]  = val1;
    Arr[6]  = val2;
    Arr[10] = val3;
    Arr[14] = val4;

    //Row 1
    val1 = Arr[3] * other.Arr[0]  + Arr[7] * other.Arr[1]  + Arr[11] * other.Arr[2]  + Arr[15] * other.Arr[3];
    val2 = Arr[3] * other.Arr[4]  + Arr[7] * other.Arr[5]  + Arr[11] * other.Arr[6]  + Arr[15] * other.Arr[7];
    val3 = Arr[3] * other.Arr[8]  + Arr[7] * other.Arr[9]  + Arr[11] * other.Arr[10] + Arr[15] * other.Arr[11];
    val4 = Arr[3] * other.Arr[12] + Arr[7] * other.Arr[13] + Arr[11] * other.Arr[14] + Arr[15] * other.Arr[15];

    Arr[3]  = val1;
    Arr[7]  = val2;
    Arr[11] = val3;
    Arr[15] = val4;

    return *this;
}

template<typename T>
constexpr Matrix4<T> Matrix4<T>::operator/(const T value) const
{
    return Matrix4(
        Arr[0]  / value, Arr[1]  / value, Arr[2]  / value, Arr[3]  / value,
        Arr[4]  / value, Arr[5]  / value, Arr[6]  / value, Arr[7]  / value,
        Arr[8]  / value, Arr[9]  / value, Arr[10] / value, Arr[11] / value,
        Arr[12] / value, Arr[13] / value, Arr[14] / value, Arr[15] / value
    );
}

template<typename T>
constexpr Matrix4<T>& Matrix4<T>::operator/=(const T value)
{
    Arr[0]  /= value;
    Arr[1]  /= value;
    Arr[2]  /= value;
    Arr[3]  /= value;
    Arr[4]  /= value;
    Arr[5]  /= value;
    Arr[6]  /= value;
    Arr[7]  /= value;
    Arr[8]  /= value;
    Arr[9]  /= value;
    Arr[10] /= value;
    Arr[11] /= value;
    Arr[12] /= value;
    Arr[13] /= value;
    Arr[14] /= value;
    Arr[15] /= value;

    return *this;
}

template<typename T>
constexpr bool Matrix4<T>::operator==(const Matrix4<T>& other) const
{
    return Arr[0]  == other.Arr[0]  && 
           Arr[1]  == other.Arr[1]  && 
           Arr[2]  == other.Arr[2]  &&
           Arr[3]  == other.Arr[3]  &&
           Arr[4]  == other.Arr[4]  &&
           Arr[5]  == other.Arr[5]  &&
           Arr[6]  == other.Arr[6]  &&
           Arr[7]  == other.Arr[7]  &&
           Arr[8]  == other.Arr[8]  &&
           Arr[9]  == other.Arr[9]  &&
           Arr[10] == other.Arr[10] &&
           Arr[11] == other.Arr[11] &&
           Arr[12] == other.Arr[12] &&
           Arr[13] == other.Arr[13] &&
           Arr[14] == other.Arr[14] &&
           Arr[15] == other.Arr[15];
}

template<typename T>
constexpr bool Matrix4<T>::operator!=(const Matrix4<T>& other) const
{
    return Arr[0]  != other.Arr[0]  || 
           Arr[1]  != other.Arr[1]  || 
           Arr[2]  != other.Arr[2]  ||
           Arr[3]  != other.Arr[3]  ||
           Arr[4]  != other.Arr[4]  ||
           Arr[5]  != other.Arr[5]  ||
           Arr[6]  != other.Arr[6]  ||
           Arr[7]  != other.Arr[7]  ||
           Arr[8]  != other.Arr[8]  ||
           Arr[9]  != other.Arr[9]  ||
           Arr[10] != other.Arr[10] ||
           Arr[11] != other.Arr[11] ||
           Arr[12] != other.Arr[12] ||
           Arr[13] != other.Arr[13] ||
           Arr[14] != other.Arr[14] ||
           Arr[15] != other.Arr[15];
}

//! Operations
//Laplace Expansion Theorem (https://en.wikipedia.org/wiki/Laplace_expansion)
template<typename T>
constexpr T Matrix4<T>::Determinant() const
{
    T b12 = Arr[0] * Arr[5]  - Arr[1] * Arr[4];
    T b13 = Arr[0] * Arr[9]  - Arr[1] * Arr[8];
    T b14 = Arr[0] * Arr[13] - Arr[1] * Arr[12];
    T b23 = Arr[4] * Arr[9]  - Arr[5] * Arr[8];
    T b24 = Arr[4] * Arr[13] - Arr[5] * Arr[12];
    T b34 = Arr[8] * Arr[13] - Arr[9] * Arr[12];

    T c12 = Arr[2]  * Arr[7]  - Arr[3]  * Arr[6];
    T c13 = Arr[2]  * Arr[11] - Arr[3]  * Arr[10];
    T c14 = Arr[2]  * Arr[15] - Arr[3]  * Arr[14];
    T c23 = Arr[6]  * Arr[11] - Arr[7]  * Arr[10];
    T c24 = Arr[6]  * Arr[15] - Arr[7]  * Arr[14];
    T c34 = Arr[10] * Arr[15] - Arr[11] * Arr[14];

    return b12 * c34 - b13 * c24 + b14 * c23 + b23 * c14 - b24 * c13 + b34 * c12;
}

//Laplace Expansion Theorem (https://en.wikipedia.org/wiki/Laplace_expansion)
template<typename T>
constexpr Matrix4<T> Matrix4<T>::GetInverse() const
{
    T b12 = Arr[0] * Arr[5]  - Arr[1] * Arr[4];
    T b13 = Arr[0] * Arr[9]  - Arr[1] * Arr[8];
    T b14 = Arr[0] * Arr[13] - Arr[1] * Arr[12];
    T b23 = Arr[4] * Arr[9]  - Arr[5] * Arr[8];
    T b24 = Arr[4] * Arr[13] - Arr[5] * Arr[12];
    T b34 = Arr[8] * Arr[13] - Arr[9] * Arr[12];

    T c12 = Arr[2]  * Arr[7]  - Arr[3]  * Arr[6];
    T c13 = Arr[2]  * Arr[11] - Arr[3]  * Arr[10];
    T c14 = Arr[2]  * Arr[15] - Arr[3]  * Arr[14];
    T c23 = Arr[6]  * Arr[11] - Arr[7]  * Arr[10];
    T c24 = Arr[6]  * Arr[15] - Arr[7]  * Arr[14];
    T c34 = Arr[10] * Arr[15] - Arr[11] * Arr[14];

    T det    = b12 * c34 - b13 * c24 + b14 * c23 + b23 * c14 - b24 * c13 + b34 * c12;
    T invDet = 1.0 / det; 
        
    //Store the cofactors transposed
    return Matrix4(
         (Arr[5] * c34 - Arr[9] * c24 + Arr[13] * c23) * invDet,
        -(Arr[1] * c34 - Arr[9] * c14 + Arr[13] * c13) * invDet,
         (Arr[1] * c24 - Arr[5] * c14 + Arr[13] * c12) * invDet,
        -(Arr[1] * c23 - Arr[5] * c13 + Arr[9] * c12) * invDet,
        -(Arr[4] * c34 - Arr[8] * c24 + Arr[12] * c23) * invDet,
         (Arr[0] * c34 - Arr[8] * c14 + Arr[12] * c13) * invDet,
        -(Arr[0] * c24 - Arr[4] * c14 + Arr[12] * c12) * invDet,
         (Arr[0] * c23 - Arr[4] * c13 + Arr[8] * c12) * invDet,
         (Arr[7] * b34 - Arr[11] * b24 + Arr[15] * b23) * invDet,
        -(Arr[3] * b34 - Arr[11] * b14 + Arr[15] * b13) * invDet,
         (Arr[3] * b24 - Arr[7] * b14 + Arr[15] * b12) * invDet,
        -(Arr[3] * b23 - Arr[7] * b13 + Arr[11] * b12) * invDet,
        -(Arr[6] * b34 - Arr[10] * b24 + Arr[14] * b23) * invDet,
         (Arr[2] * b34 - Arr[10] * b14 + Arr[14] * b13) * invDet,
        -(Arr[2] * b24 - Arr[6] * b14 + Arr[14] * b12) * invDet,
         (Arr[2] * b23 - Arr[6] * b13 + Arr[10] * b12) * invDet
    );
}

template<typename T>
constexpr Matrix4<T> Matrix4<T>::GetTranspose() const
{
    return Matrix4(
        Arr[0],
        Arr[4],
        Arr[8],
        Arr[12],
        Arr[1],
        Arr[5],
        Arr[9],
        Arr[13],
        Arr[2],
        Arr[6],
        Arr[10],
        Arr[14],
        Arr[3],
        Arr[7],
        Arr[11],
        Arr[15]
    );
}

//TODO:###############
template<typename T>
constexpr Matrix4<T> Matrix4<T>::GetScaled(const Vector3<T>& scale) const
{
    return Matrix4(
        Arr[0]  * scale.X,
        Arr[1]  * scale.X,
        Arr[2]  * scale.X,
        Arr[3]  * scale.X,
        Arr[4]  * scale.Y,
        Arr[5]  * scale.Y,
        Arr[6]  * scale.Y,
        Arr[7]  * scale.Y,
        Arr[8]  * scale.Z,
        Arr[9]  * scale.Z,
        Arr[10] * scale.Z,
        Arr[11] * scale.Z,
        Arr[12],
        Arr[13],
        Arr[14],
        Arr[15]
    );
}

template<typename T>
constexpr Matrix4<T> Matrix4<T>::GetRotatedX(T radians) const
{
    T cos = std::cos(radians);
    T sin = std::sin(radians);

    return Matrix4(
        Arr[0],
        Arr[1],
        Arr[2],
        Arr[3],
        Arr[4] *  cos + Arr[8]  * sin,
        Arr[5] *  cos + Arr[9]  * sin,
        Arr[6] *  cos + Arr[10] * cos,
        Arr[7] *  cos + Arr[11] * cos,
        Arr[4] * -sin + Arr[8]  * cos,
        Arr[5] * -sin + Arr[9]  * cos,
        Arr[6] * -sin + Arr[10] * cos,
        Arr[7] * -sin + Arr[11] * cos,
        Arr[12],
        Arr[13],
        Arr[14],
        Arr[15]
    );
}

template<typename T>
constexpr Matrix4<T> Matrix4<T>::GetRotatedY(T radians) const
{
    T cos = std::cos(radians);
    T sin = std::sin(radians);

    return Matrix4(
        Arr[0] * cos - Arr[8]  * sin,
        Arr[1] * cos - Arr[9]  * sin,
        Arr[2] * cos - Arr[10] * sin,
        Arr[3] * cos - Arr[11] * sin,
        Arr[4],
        Arr[5],
        Arr[6],
        Arr[7],
        Arr[0] * sin + Arr[8]  * cos,
        Arr[1] * sin + Arr[9]  * cos,
        Arr[2] * sin + Arr[10] * cos,
        Arr[3] * sin + Arr[11] * cos,
        Arr[12],
        Arr[13],
        Arr[14],
        Arr[15]
    );
}

template<typename T>
constexpr Matrix4<T> Matrix4<T>::GetRotatedZ(T radians) const
{
    T cos = std::cos(radians);
    T sin = std::sin(radians);

    return Matrix4(
        Arr[0] *  cos + Arr[4] * sin,
        Arr[1] *  cos + Arr[5] * sin,
        Arr[2] *  cos + Arr[6] * sin,
        Arr[3] *  cos + Arr[7] * sin,
        Arr[0] * -sin + Arr[4] * cos,
        Arr[1] * -sin + Arr[5] * cos,
        Arr[2] * -sin + Arr[6] * cos,
        Arr[3] * -sin + Arr[7] * cos,
        Arr[8],
        Arr[9],
        Arr[10],
        Arr[11],
        Arr[12],
        Arr[13],
        Arr[14],
        Arr[15]
    );
}

template<typename T>
constexpr Matrix4<T> Matrix4<T>::GetTranslated(const Vector3<T>& translation) const
{
    return Matrix4(
        Arr[0],
        Arr[1],
        Arr[2],
        Arr[3],
        Arr[4],
        Arr[5],
        Arr[6],
        Arr[7],
        Arr[8],
        Arr[9],
        Arr[10],
        Arr[11],
        Arr[0] * translation.X + Arr[4] * translation.Y + Arr[8]  * translation.Z + Arr[12],
        Arr[1] * translation.X + Arr[5] * translation.Y + Arr[9]  * translation.Z + Arr[13],
        Arr[2] * translation.X + Arr[6] * translation.Y + Arr[10] * translation.Z + Arr[14],
        Arr[3] * translation.X + Arr[7] * translation.Y + Arr[11] * translation.Z + Arr[15]
    );
}

template<typename T>
constexpr Matrix4<T> Matrix4<T>::CreateScale(const Vector3<T>& scale)
{
    return Matrix4(
        scale.X, 0, 0, 0,
        0, scale.Y, 0, 0,
        0, 0, scale.Z, 0,
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
        translation.X, translation.Y, translation.Z, 1
    );
}

/*
template<typename T>
constexpr Matrix4<T> Matrix4<T>::CreateTransform(const Vector3<T>& scale, 
    const Quaternion<T>& rotation, const Vector3<T>& translation)
{
    throw "Unimplemented method Matrix4::CreateTransform";
    return Matrix4();
}
*/

} //namespace Math