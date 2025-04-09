#include <cmath>

namespace math
{

//! Constructors
template<typename T>
constexpr Matrix3<T>::Matrix3() : 
    arr{1, 0, 0, 
        0, 1, 0, 
        0, 0, 1} { }

template<typename T>
constexpr Matrix3<T>::Matrix3(T value) : 
    arr{value, 0, 0, 
        0, value, 0, 
        0, 0, value} { }

template<typename T>
constexpr Matrix3<T>::Matrix3(T m11, T m22, T m33) : 
    arr{m11, 0, 0, 
        0, m22, 0, 
        0, 0, m33} { }

template<typename T>
constexpr Matrix3<T>::Matrix3(T m11, T m21, T m31, T m12, T m22, T m32, T m13, T m23, T m33) : 
    arr{m11, m21, m31, 
        m12, m22, m32, 
        m13, m23, m33} { }

//! Operators
template<typename T>
constexpr T* Matrix3<T>::operator[](std::size_t index)
{
    return &arr[index * NumColumns];
}

template<typename T>
constexpr const T* Matrix3<T>::operator[](std::size_t index) const
{
    return &arr[index * NumColumns];
}

template<typename T>
constexpr Matrix3<T> Matrix3<T>::operator+(const Matrix3<T>& other) const
{
    return Matrix3(
        arr[0] + other.arr[0], arr[1] + other.arr[1], arr[2] + other.arr[2],
        arr[3] + other.arr[3], arr[4] + other.arr[4], arr[5] + other.arr[5],
        arr[6] + other.arr[6], arr[7] + other.arr[7], arr[8] + other.arr[8]
    );
}

template<typename T>
constexpr Matrix3<T>& Matrix3<T>::operator+=(const Matrix3<T>& other)
{
    arr[0] += other.arr[0];
    arr[1] += other.arr[1];
    arr[2] += other.arr[2];
    arr[3] += other.arr[3];
    arr[4] += other.arr[4];
    arr[5] += other.arr[5];
    arr[6] += other.arr[6];
    arr[7] += other.arr[7];
    arr[8] += other.arr[8];
    
    return *this;
}

template<typename T>
constexpr Matrix3<T> Matrix3<T>::operator-(const Matrix3<T>& other) const
{
    return Matrix3(
        arr[0] - other.arr[0], arr[1] - other.arr[1], arr[2] - other.arr[2],
        arr[3] - other.arr[3], arr[4] - other.arr[4], arr[5] - other.arr[5],
        arr[6] - other.arr[6], arr[7] - other.arr[7], arr[8] - other.arr[8]
    );
}

template<typename T>
constexpr Matrix3<T>& Matrix3<T>::operator-=(const Matrix3<T>& other)
{
    arr[0] -= other.arr[0];
    arr[1] -= other.arr[1];
    arr[2] -= other.arr[2];
    arr[3] -= other.arr[3];
    arr[4] -= other.arr[4];
    arr[5] -= other.arr[5];
    arr[6] -= other.arr[6];
    arr[7] -= other.arr[7];
    arr[8] -= other.arr[8];

    return *this;
}

template<typename T>
constexpr Matrix3<T> Matrix3<T>::operator*(const T value) const
{
    return Matrix3(
        arr[0] * value, arr[1] * value, arr[2] * value,
        arr[3] * value, arr[4] * value, arr[5] * value,
        arr[6] * value, arr[7] * value, arr[8] * value
    );
}

template<typename T>
constexpr Matrix3<T>& Matrix3<T>::operator*=(const T value)
{
    arr[0] *= value;
    arr[1] *= value;
    arr[2] *= value;
    arr[3] *= value;
    arr[4] *= value;
    arr[5] *= value;
    arr[6] *= value;
    arr[7] *= value;
    arr[8] *= value;

    return *this;
}

template<typename T>
constexpr Matrix3<T> Matrix3<T>::operator*(const Matrix3<T>& other) const
{
    return Matrix3(
        arr[0] * other.arr[0] + arr[3] * other.arr[1] + arr[6] * other.arr[2],
        arr[1] * other.arr[0] + arr[4] * other.arr[1] + arr[7] * other.arr[2],
        arr[2] * other.arr[0] + arr[5] * other.arr[1] + arr[8] * other.arr[2],
        arr[0] * other.arr[3] + arr[3] * other.arr[4] + arr[6] * other.arr[5],
        arr[1] * other.arr[3] + arr[4] * other.arr[4] + arr[7] * other.arr[5],
        arr[2] * other.arr[3] + arr[5] * other.arr[4] + arr[8] * other.arr[5],
        arr[0] * other.arr[6] + arr[3] * other.arr[7] + arr[6] * other.arr[8],
        arr[1] * other.arr[6] + arr[4] * other.arr[7] + arr[7] * other.arr[8],
        arr[2] * other.arr[6] + arr[5] * other.arr[7] + arr[8] * other.arr[8]
    );
}

template<typename T>
constexpr Matrix3<T>& Matrix3<T>::operator*=(const Matrix3<T>& other)
{
    //Row 1
    T val1 = arr[0] * other.arr[0] + arr[3] * other.arr[1] + arr[6] * other.arr[2];
    T val2 = arr[0] * other.arr[3] + arr[3] * other.arr[4] + arr[6] * other.arr[5];
    T val3 = arr[0] * other.arr[6] + arr[3] * other.arr[7] + arr[6] * other.arr[8];

    arr[0] = val1;
    arr[3] = val2;
    arr[6] = val3;

    //Row 2
    val1 = arr[1] * other.arr[0] + arr[4] * other.arr[1] + arr[7] * other.arr[2];
    val2 = arr[1] * other.arr[3] + arr[4] * other.arr[4] + arr[7] * other.arr[5];
    val3 = arr[1] * other.arr[6] + arr[4] * other.arr[7] + arr[7] * other.arr[8];

    arr[1] = val1;
    arr[4] = val2;
    arr[7] = val3;

    //Row 3
    val1 = arr[2] * other.arr[0] + arr[5] * other.arr[1] + arr[8] * other.arr[2];
    val2 = arr[2] * other.arr[3] + arr[5] * other.arr[4] + arr[8] * other.arr[5];
    val3 = arr[2] * other.arr[6] + arr[5] * other.arr[7] + arr[8] * other.arr[8];

    arr[2] = val1;
    arr[5] = val2;
    arr[8] = val3;

    return *this;
}

template<typename T>
constexpr Matrix3<T> Matrix3<T>::operator/(const T value) const
{
    return Matrix3(
        arr[0] / value, arr[1] / value, arr[2] / value, 
        arr[3] / value, arr[4] / value, arr[5] / value,
        arr[6] / value, arr[7] / value, arr[8] / value
    );
}

template<typename T>
constexpr Matrix3<T>& Matrix3<T>::operator/=(const T value)
{
    arr[0] /= value;
    arr[1] /= value;
    arr[2] /= value;
    arr[3] /= value;
    arr[4] /= value;
    arr[5] /= value;
    arr[6] /= value;
    arr[7] /= value;
    arr[8] /= value;

    return *this;
}

template<typename T>
constexpr bool Matrix3<T>::operator==(const Matrix3<T>& other) const
{
    return arr[0] == other.arr[0] && 
           arr[1] == other.arr[1] && 
           arr[2] == other.arr[2] &&
           arr[3] == other.arr[3] &&
           arr[4] == other.arr[4] &&
           arr[5] == other.arr[5] &&
           arr[6] == other.arr[6] &&
           arr[7] == other.arr[7] &&
           arr[8] == other.arr[8];
}

template<typename T>
constexpr bool Matrix3<T>::operator!=(const Matrix3<T>& other) const
{
    return arr[0] != other.arr[0] || 
           arr[1] != other.arr[1] || 
           arr[2] != other.arr[2] ||
           arr[3] != other.arr[3] ||
           arr[4] != other.arr[4] ||
           arr[5] != other.arr[5] ||
           arr[6] != other.arr[6] ||
           arr[7] != other.arr[7] ||
           arr[8] != other.arr[8];
}

//! Operations
template<typename T>
constexpr T Matrix3<T>::Determinant() const
{
    return (arr[0] * arr[4] * arr[8] + arr[3] * arr[7] * arr[2] + arr[1] * arr[5] * arr[6]) -
        (arr[6] * arr[4] * arr[2] + arr[1] * arr[3] * arr[8] + arr[5] * arr[7] * arr[0]);
}

template<typename T>
constexpr Matrix3<T> Matrix3<T>::GetInverse() const
{
    T m0_4 = arr[0] * arr[4];
    T m3_7 = arr[3] * arr[7];
    T m1_5 = arr[1] * arr[5];
    T m6_4 = arr[6] * arr[4];
    T m3_1 = arr[3] * arr[1];
    T m7_5 = arr[7] * arr[5];

    //Cofactors
    T mc0    = (arr[4] * arr[8] - m7_5);
    T mc1    = (arr[3] * arr[8] - arr[5] * arr[6]);
    T mc2    = (m3_7   - m6_4);
    T mc3    = (arr[1] * arr[8] - arr[2] * arr[7]);
    T mc4    = (arr[0] * arr[8] - arr[2] * arr[6]);
    T mc5    = (arr[0] * arr[7] - arr[1] * arr[6]);
    T mc6    = (m1_5   - arr[2] * arr[4]);
    T mc7    = (arr[0] * arr[5] - arr[2] * arr[3]);
    T mc8    = (m0_4   - m3_1);
    T det    = arr[0] * mc0 - arr[3] * mc3 + arr[6] * mc6;
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
        arr[0],
        arr[3],
        arr[6],
        arr[1],
        arr[4],
        arr[7],
        arr[2],
        arr[5],
        arr[8]
    );
}

template<typename T>
constexpr Matrix3<T> Matrix3<T>::GetScaled(const Vector3<T>& scale) const
{
    return Matrix3(
        arr[0] * scale.x,
        arr[1] * scale.x,
        arr[2] * scale.x,
        arr[3] * scale.y,
        arr[4] * scale.y,
        arr[5] * scale.y,
        arr[6] * scale.z,
        arr[7] * scale.z,
        arr[8] * scale.z
    );
}

template<typename T>
constexpr Matrix3<T> Matrix3<T>::GetScaled2D(const Vector2<T> scale) const
{
    return Matrix3(
        arr[0] * scale.x,
        arr[1] * scale.x,
        arr[2] * scale.x,
        arr[3] * scale.y,
        arr[4] * scale.y,
        arr[5] * scale.y,
        arr[6],
        arr[7],
        arr[8]
    );
}

template<typename T>
constexpr Matrix3<T> Matrix3<T>::GetRotatedX(T radians) const
{
    T cos = std::cos(radians);
    T sin = std::sin(radians);

    return Matrix3(
        arr[0],
        arr[1],
        arr[2],
        arr[3] *  cos + arr[6] * sin,
        arr[4] *  cos + arr[7] * sin,
        arr[5] *  cos + arr[8] * sin,
        arr[3] * -sin + arr[6] * cos,
        arr[4] * -sin + arr[7] * cos,
        arr[5] * -sin + arr[8] * cos
    );
}

template<typename T>
constexpr Matrix3<T> Matrix3<T>::GetRotatedY(T radians) const
{
    T cos = std::cos(radians);
    T sin = std::sin(radians);

    return Matrix3(
        arr[0] * cos - arr[6] * sin,
        arr[1] * cos - arr[7] * sin,
        arr[2] * cos - arr[8] * sin,
        arr[3],
        arr[4],
        arr[5],
        arr[0] * sin + arr[6] * cos,
        arr[1] * sin + arr[7] * cos,
        arr[2] * sin + arr[8] * cos
    );
}

template<typename T>
constexpr Matrix3<T> Matrix3<T>::GetRotatedZ(T radians) const
{
    T cos = std::cos(radians);
    T sin = std::sin(radians);

    return Matrix3(
        arr[0] *  cos + arr[3] * sin,
        arr[1] *  cos + arr[4] * sin,
        arr[2] *  cos + arr[5] * sin,
        arr[0] * -sin + arr[3] * cos,
        arr[1] * -sin + arr[4] * cos,
        arr[2] * -sin + arr[5] * cos,
        arr[6],
        arr[7],
        arr[8]
    );
}

template<typename T>
constexpr Matrix3<T> Matrix3<T>::GetTranslated2D(const Vector2<T> translation) const
{
    return Matrix3(
        arr[0],
        arr[1],
        arr[2],
        arr[3],
        arr[4],
        arr[5],
        arr[0] * translation.x + arr[3] * translation.y + arr[6],
        arr[1] * translation.x + arr[4] * translation.y + arr[7],
        arr[2] * translation.x + arr[5] * translation.y + arr[8]
    );
}

template<typename T>
constexpr Matrix3<T> Matrix3<T>::CreateScale(const Vector3<T>& scale)
{
    return Matrix3(
        scale.x, 0, 0,
        0, scale.y, 0,
        0, 0, scale.z
    );
}

template<typename T>
constexpr Matrix3<T> Matrix3<T>::CreateScale2D(const Vector2<T> scale)
{
    return Matrix3(
        scale.x, 0, 0,
        0, scale.y, 0,
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
        translation.x, translation.y, 1
    );
}

template<typename T>
constexpr Matrix3<T> Matrix3<T>::CreateTransform2D(const Vector2<T> scale, 
    T radians, const Vector2<T> translation)
{
    T cos = std::cos(radians);
    T sin = std::sin(radians);

    return Matrix3(
        cos * scale.x, sin * scale.x, 0,
        -sin * scale.y, cos * scale.y, 0,
        translation.x, translation.y, 1
    );
}

} //namespace math