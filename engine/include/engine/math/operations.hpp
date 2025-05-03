#pragma once
#include "vector/Vector2.hpp"
#include "vector/Vector3.hpp"
#include "vector/Vector4.hpp"
#include "matrix/Matrix2.hpp"
#include "matrix/Matrix3.hpp"
#include "matrix/Matrix4.hpp"
#include "quat/Quaternion.hpp"

namespace math
{

template<typename T>
Vector2<T> operator*(const Matrix2<T>& m, const Vector2<T> v);
template<typename T>
Vector2<T> operator*(const Matrix3<T>& m, const Vector3<T> v);
template<typename T>
Vector2<T> operator*(const Matrix4<T>& m, const Vector4<T> v);
template<typename T>
Vector3<T> operator*(const Quaternion<T>& q, const Vector3<T> v);

} //namespace math

#include "operations.inl"