#include <cmath>

namespace Math
{

//! Constructors
template<typename T>
constexpr Matrix3<T>::Matrix3() : 
    Arr{1, 0, 0, 
        0, 1, 0, 
        0, 0, 1} { }

template<typename T>
constexpr Matrix3<T>::Matrix3(T value) : 
    Arr{value, 0, 0, 
        0, value, 0, 
        0, 0, value} { }

template<typename T>
constexpr Matrix3<T>::Matrix3(T m11, T m22, T m33) : 
    Arr{m11, 0, 0, 
        0, m22, 0, 
        0, 0, m33} { }

template<typename T>
constexpr Matrix3<T>::Matrix3(T m11, T m21, T m31, T m12, T m22, T m32, T m13, T m23, T m33) : 
    Arr{m11, m21, m31, 
        m12, m22, m32, 
        m13, m23, m33} { }

//! Operators
template<typename T>
constexpr T* Matrix3<T>::operator[](std::size_t index)
{
    return &Arr[index * NumColumns];
}

template<typename T>
constexpr const T* Matrix3<T>::operator[](std::size_t index) const
{
    return &Arr[index * NumColumns];
}

template<typename T>
constexpr Matrix3<T> Matrix3<T>::operator+(const Matrix3<T>& other) const
{
    return Matrix3(
        Arr[0] + other.Arr[0], Arr[1] + other.Arr[1], Arr[2] + other.Arr[2],
        Arr[3] + other.Arr[3], Arr[4] + other.Arr[4], Arr[5] + other.Arr[5],
        Arr[6] + other.Arr[6], Arr[7] + other.Arr[7], Arr[8] + other.Arr[8]
    );
}

template<typename T>
constexpr Matrix3<T>& Matrix3<T>::operator+=(const Matrix3<T>& other)
{
    Arr[0] += other.Arr[0];
    Arr[1] += other.Arr[1];
    Arr[2] += other.Arr[2];
    Arr[3] += other.Arr[3];
    Arr[4] += other.Arr[4];
    Arr[5] += other.Arr[5];
    Arr[6] += other.Arr[6];
    Arr[7] += other.Arr[7];
    Arr[8] += other.Arr[8];
    
    return *this;
}

template<typename T>
constexpr Matrix3<T> Matrix3<T>::operator-(const Matrix3<T>& other) const
{
    return Matrix3(
        Arr[0] - other.Arr[0], Arr[1] - other.Arr[1], Arr[2] - other.Arr[2],
        Arr[3] - other.Arr[3], Arr[4] - other.Arr[4], Arr[5] - other.Arr[5],
        Arr[6] - other.Arr[6], Arr[7] - other.Arr[7], Arr[8] - other.Arr[8]
    );
}

template<typename T>
constexpr Matrix3<T>& Matrix3<T>::operator-=(const Matrix3<T>& other)
{
    Arr[0] -= other.Arr[0];
    Arr[1] -= other.Arr[1];
    Arr[2] -= other.Arr[2];
    Arr[3] -= other.Arr[3];
    Arr[4] -= other.Arr[4];
    Arr[5] -= other.Arr[5];
    Arr[6] -= other.Arr[6];
    Arr[7] -= other.Arr[7];
    Arr[8] -= other.Arr[8];

    return *this;
}

template<typename T>
constexpr Matrix3<T> Matrix3<T>::operator*(const T value) const
{
    return Matrix3(
        Arr[0] * value, Arr[1] * value, Arr[2] * value,
        Arr[3] * value, Arr[4] * value, Arr[5] * value,
        Arr[6] * value, Arr[7] * value, Arr[8] * value
    );
}

template<typename T>
constexpr Matrix3<T>& Matrix3<T>::operator*=(const T value)
{
    Arr[0] *= value;
    Arr[1] *= value;
    Arr[2] *= value;
    Arr[3] *= value;
    Arr[4] *= value;
    Arr[5] *= value;
    Arr[6] *= value;
    Arr[7] *= value;
    Arr[8] *= value;

    return *this;
}

template<typename T>
constexpr Matrix3<T> Matrix3<T>::operator*(const Matrix3<T>& other) const
{
    return Matrix3(
        Arr[0] * other.Arr[0] + Arr[3] * other.Arr[1] + Arr[6] * other.Arr[2],
        Arr[1] * other.Arr[0] + Arr[4] * other.Arr[1] + Arr[7] * other.Arr[2],
        Arr[2] * other.Arr[0] + Arr[5] * other.Arr[1] + Arr[8] * other.Arr[2],
        Arr[0] * other.Arr[3] + Arr[3] * other.Arr[4] + Arr[6] * other.Arr[5],
        Arr[1] * other.Arr[3] + Arr[4] * other.Arr[4] + Arr[7] * other.Arr[5],
        Arr[2] * other.Arr[3] + Arr[5] * other.Arr[4] + Arr[8] * other.Arr[5],
        Arr[0] * other.Arr[6] + Arr[3] * other.Arr[7] + Arr[6] * other.Arr[8],
        Arr[1] * other.Arr[6] + Arr[4] * other.Arr[7] + Arr[7] * other.Arr[8],
        Arr[2] * other.Arr[6] + Arr[5] * other.Arr[7] + Arr[8] * other.Arr[8]
    );
}

template<typename T>
constexpr Matrix3<T>& Matrix3<T>::operator*=(const Matrix3<T>& other)
{
    //Row 1
    T val1 = Arr[0] * other.Arr[0] + Arr[3] * other.Arr[1] + Arr[6] * other.Arr[2];
    T val2 = Arr[0] * other.Arr[3] + Arr[3] * other.Arr[4] + Arr[6] * other.Arr[5];
    T val3 = Arr[0] * other.Arr[6] + Arr[3] * other.Arr[7] + Arr[6] * other.Arr[8];

    Arr[0] = val1;
    Arr[3] = val2;
    Arr[6] = val3;

    //Row 2
    val1 = Arr[1] * other.Arr[0] + Arr[4] * other.Arr[1] + Arr[7] * other.Arr[2];
    val2 = Arr[1] * other.Arr[3] + Arr[4] * other.Arr[4] + Arr[7] * other.Arr[5];
    val3 = Arr[1] * other.Arr[6] + Arr[4] * other.Arr[7] + Arr[7] * other.Arr[8];

    Arr[1] = val1;
    Arr[4] = val2;
    Arr[7] = val3;

    //Row 3
    val1 = Arr[2] * other.Arr[0] + Arr[5] * other.Arr[1] + Arr[8] * other.Arr[2];
    val2 = Arr[2] * other.Arr[3] + Arr[5] * other.Arr[4] + Arr[8] * other.Arr[5];
    val3 = Arr[2] * other.Arr[6] + Arr[5] * other.Arr[7] + Arr[8] * other.Arr[8];

    Arr[2] = val1;
    Arr[5] = val2;
    Arr[8] = val3;

    return *this;
}

template<typename T>
constexpr Matrix3<T> Matrix3<T>::operator/(const T value) const
{
    return Matrix3(
        Arr[0] / value, Arr[1] / value, Arr[2] / value, 
        Arr[3] / value, Arr[4] / value, Arr[5] / value,
        Arr[6] / value, Arr[7] / value, Arr[8] / value
    );
}

template<typename T>
constexpr Matrix3<T>& Matrix3<T>::operator/=(const T value)
{
    Arr[0] /= value;
    Arr[1] /= value;
    Arr[2] /= value;
    Arr[3] /= value;
    Arr[4] /= value;
    Arr[5] /= value;
    Arr[6] /= value;
    Arr[7] /= value;
    Arr[8] /= value;

    return *this;
}

template<typename T>
constexpr bool Matrix3<T>::operator==(const Matrix3<T>& other) const
{
    return Arr[0] == other.Arr[0] && 
           Arr[1] == other.Arr[1] && 
           Arr[2] == other.Arr[2] &&
           Arr[3] == other.Arr[3] &&
           Arr[4] == other.Arr[4] &&
           Arr[5] == other.Arr[5] &&
           Arr[6] == other.Arr[6] &&
           Arr[7] == other.Arr[7] &&
           Arr[8] == other.Arr[8];
}

template<typename T>
constexpr bool Matrix3<T>::operator!=(const Matrix3<T>& other) const
{
    return Arr[0] != other.Arr[0] || 
           Arr[1] != other.Arr[1] || 
           Arr[2] != other.Arr[2] ||
           Arr[3] != other.Arr[3] ||
           Arr[4] != other.Arr[4] ||
           Arr[5] != other.Arr[5] ||
           Arr[6] != other.Arr[6] ||
           Arr[7] != other.Arr[7] ||
           Arr[8] != other.Arr[8];
}

//! Operations
template<typename T>
constexpr T Matrix3<T>::Determinant() const
{
    return (Arr[0] * Arr[4] * Arr[8] + Arr[3] * Arr[7] * Arr[2] + Arr[1] * Arr[5] * Arr[6]) -
        (Arr[6] * Arr[4] * Arr[2] + Arr[1] * Arr[3] * Arr[8] + Arr[5] * Arr[7] * Arr[0]);
}

template<typename T>
constexpr Matrix3<T> Matrix3<T>::GetInverse() const
{
    T m0_4 = Arr[0] * Arr[4];
    T m3_7 = Arr[3] * Arr[7];
    T m1_5 = Arr[1] * Arr[5];
    T m6_4 = Arr[6] * Arr[4];
    T m3_1 = Arr[3] * Arr[1];
    T m7_5 = Arr[7] * Arr[5];

    //Cofactors
    T mc0    = (Arr[4] * Arr[8] - m7_5);
    T mc1    = (Arr[3] * Arr[8] - Arr[5] * Arr[6]);
    T mc2    = (m3_7   - m6_4);
    T mc3    = (Arr[1] * Arr[8] - Arr[2] * Arr[7]);
    T mc4    = (Arr[0] * Arr[8] - Arr[2] * Arr[6]);
    T mc5    = (Arr[0] * Arr[7] - Arr[1] * Arr[6]);
    T mc6    = (m1_5   - Arr[2] * Arr[4]);
    T mc7    = (Arr[0] * Arr[5] - Arr[2] * Arr[3]);
    T mc8    = (m0_4   - m3_1);
    T det    = Arr[0] * mc0 - Arr[3] * mc3 + Arr[6] * mc6;
    T invDet = 1.0 / det;

    return Matrix3(
         mc0 * invDet,
        -mc3 * invDet,
         mc6 * invDet,
        -mc1 * invDet,
         mc4 * invDet,
        -mc7 * invDet,
         mc2 * invDet,
        -mc5 * invDet,
         mc8 * invDet);
}

template<typename T>
constexpr Matrix3<T> Matrix3<T>::GetTranspose() const
{
    return Matrix3(
        Arr[0],
        Arr[3],
        Arr[6],
        Arr[1],
        Arr[4],
        Arr[7],
        Arr[2],
        Arr[5],
        Arr[8]
    );
}

template<typename T>
constexpr Matrix3<T> Matrix3<T>::GetScaled(const Vector3<T>& scale) const
{
    return Matrix3(
        Arr[0] * scale.X,
        Arr[1] * scale.X,
        Arr[2] * scale.X,
        Arr[3] * scale.Y,
        Arr[4] * scale.Y,
        Arr[5] * scale.Y,
        Arr[6] * scale.Z,
        Arr[7] * scale.Z,
        Arr[8] * scale.Z
    );
}

template<typename T>
constexpr Matrix3<T> Matrix3<T>::GetScaled2D(const Vector2<T> scale) const
{
    return Matrix3(
        Arr[0] * scale.X,
        Arr[1] * scale.X,
        Arr[2] * scale.X,
        Arr[3] * scale.Y,
        Arr[4] * scale.Y,
        Arr[5] * scale.Y,
        Arr[6],
        Arr[7],
        Arr[8]
    );
}

template<typename T>
constexpr Matrix3<T> Matrix3<T>::GetRotatedX(T radians) const
{
    T cos = std::cos(radians);
    T sin = std::sin(radians);

    return Matrix3(
        Arr[0],
        Arr[1],
        Arr[2],
        Arr[3] *  cos + Arr[6] * sin,
        Arr[4] *  cos + Arr[7] * sin,
        Arr[5] *  cos + Arr[8] * sin,
        Arr[3] * -sin + Arr[6] * cos,
        Arr[4] * -sin + Arr[7] * cos,
        Arr[5] * -sin + Arr[8] * cos
    );
}

template<typename T>
constexpr Matrix3<T> Matrix3<T>::GetRotatedY(T radians) const
{
    T cos = std::cos(radians);
    T sin = std::sin(radians);

    return Matrix3(
        Arr[0] * cos - Arr[6] * sin,
        Arr[1] * cos - Arr[7] * sin,
        Arr[2] * cos - Arr[8] * sin,
        Arr[3],
        Arr[4],
        Arr[5],
        Arr[0] * sin + Arr[6] * cos,
        Arr[1] * sin + Arr[7] * cos,
        Arr[2] * sin + Arr[8] * cos
    );
}

template<typename T>
constexpr Matrix3<T> Matrix3<T>::GetRotatedZ(T radians) const
{
    T cos = std::cos(radians);
    T sin = std::sin(radians);

    return Matrix3(
        Arr[0] *  cos + Arr[3] * sin,
        Arr[1] *  cos + Arr[4] * sin,
        Arr[2] *  cos + Arr[5] * sin,
        Arr[0] * -sin + Arr[3] * cos,
        Arr[1] * -sin + Arr[4] * cos,
        Arr[2] * -sin + Arr[5] * cos,
        Arr[6],
        Arr[7],
        Arr[8]
    );
}

template<typename T>
constexpr Matrix3<T> Matrix3<T>::GetTranslated2D(const Vector2<T> translation) const
{
    return Matrix3(
        Arr[0],
        Arr[1],
        Arr[2],
        Arr[3],
        Arr[4],
        Arr[5],
        Arr[0] * translation.X + Arr[3] * translation.Y + Arr[6],
        Arr[1] * translation.X + Arr[4] * translation.Y + Arr[7],
        Arr[2] * translation.X + Arr[5] * translation.Y + Arr[8]
    );
}

template<typename T>
constexpr Matrix3<T> Matrix3<T>::CreateScale(const Vector3<T>& scale)
{
    return Matrix3(
        scale.X, 0, 0,
        0, scale.Y, 0,
        0, 0, scale.Z
    );
}

template<typename T>
constexpr Matrix3<T> Matrix3<T>::CreateScale2D(const Vector2<T> scale)
{
    return Matrix3(
        scale.X, 0, 0,
        0, scale.Y, 0,
        0, 0, 1.0
    );
}

template<typename T>
constexpr Matrix3<T> Matrix3<T>::CreateRotationX(T radians)
{
    T cos = std::cos(radians);
    T sin = std::sin(radians);

    return Matrix3(
        1,  0, 0,
        0,  cos, sin,
        0, -sin, cos
    );
}

template<typename T>
constexpr Matrix3<T> Matrix3<T>::CreateRotationY(T radians)
{
    T cos = std::cos(radians);
    T sin = std::sin(radians);

    return Matrix3(
        cos, 0, -sin,
        0, 1, 0,
        sin, 0, cos
    );
}

template<typename T>
constexpr Matrix3<T> Matrix3<T>::CreateRotationZ(T radians)
{
    T cos = std::cos(radians);
    T sin = std::sin(radians);

    return Matrix3(
        cos,  sin, 0,
        -sin, cos, 0,
        0, 0, 1
    );
}

template<typename T>
constexpr Matrix3<T> Matrix3<T>::CreateTranslation2D(const Vector2<T> translation)
{
    return Matrix3(
        1, 0, 0,
        0, 1, 0,
        translation.X, translation.Y, 1
    );
}

template<typename T>
constexpr Matrix3<T> Matrix3<T>::CreateTransform2D(const Vector2<T> scale, 
    T radians, const Vector2<T> translation)
{
    T cos = std::cos(radians);
    T sin = std::sin(radians);

    return Matrix3(
        cos * scale.X, sin * scale.X, 0,
        -sin * scale.Y, cos * scale.Y, 0,
        translation.X, translation.Y, 1
    );
}

} //namespace Math