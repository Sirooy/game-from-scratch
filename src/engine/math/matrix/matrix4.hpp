#pragma once
#include <cstdint>
#include <cstddef>
#include "../vector/vector3.hpp"
#include "../vector/vector4.hpp"
//#include "../quat/quaternion.hpp"

namespace Math
{

//Column based 4x4 matrix
template<typename T>
struct Matrix4
{
public:
    using Type = T;
    constexpr static int32_t Size        = 4 * 4;
    constexpr static int32_t SizeInBytes = sizeof(T) * Size;
    constexpr static int32_t NumColumns  = 4;

    //! Constructors
    constexpr Matrix4();
    constexpr Matrix4(T value);
    constexpr Matrix4(T m11, T m22, T m33, T m44);
    constexpr Matrix4(T m11, T m21, T m31, T m41, T m12, T m22, T m32, T m42, 
        T m13, T m23, T m33, T m43, T m14, T m24, T m34, T m44);

    //! Operators
    constexpr T*       operator[](std::size_t index);
    constexpr const T* operator[](std::size_t index) const;
    constexpr Matrix4  operator+(const Matrix4& other) const;
    constexpr Matrix4& operator+=(const Matrix4& other);
    constexpr Matrix4  operator-(const Matrix4& other) const;
    constexpr Matrix4& operator-=(const Matrix4& other);
    constexpr Matrix4  operator*(const T value) const;
    constexpr Matrix4& operator*=(const T value);
    constexpr Matrix4  operator*(const Matrix4& other) const;
    constexpr Matrix4& operator*=(const Matrix4& other);
    constexpr Vector4<T> operator*(const Vector4<T>& v) const;
    constexpr Matrix4  operator/(const T value) const;
    constexpr Matrix4& operator/=(const T value);
    constexpr bool     operator==(const Matrix4& other) const;
    constexpr bool     operator!=(const Matrix4& other) const;

    //! Operations
    constexpr T              Determinant() const;
    constexpr Matrix4        GetInverse() const;
    constexpr Matrix4        GetTranspose() const;
    constexpr Matrix4        GetScaled(const Vector3<T>& scale) const;
    constexpr Matrix4        GetRotatedX(T radians) const;
    constexpr Matrix4        GetRotatedY(T radians) const;
    constexpr Matrix4        GetRotatedZ(T radians) const;
    constexpr Matrix4        GetTranslated(const Vector3<T>& translation) const;
    constexpr static Matrix4 CreateScale(const Vector3<T>& scale);
    constexpr static Matrix4 CreateRotationX(T radians);
    constexpr static Matrix4 CreateRotationY(T radians);
    constexpr static Matrix4 CreateRotationZ(T radians);
    constexpr static Matrix4 CreateTranslation(const Vector3<T>& v);
    //constexpr static Matrix4 CreateTransform(const Vector3<T>& scale, 
    //    const Quaternion<T>& rotation, const Vector3<T>& translation);
private:
    T Arr[Size];
};

template struct Matrix4<float>;
template struct Matrix4<double>;

using Mat4  = Matrix4<float>;
using Mat4d = Matrix4<double>;

} //namespace Math

#include "matrix4.inl"