#include <iostream>
#include <engine/math/vector/vector2.hpp>
#include <engine/math/vector/vector3.hpp>
#include <engine/math/vector/vector4.hpp>
#include <engine/math/matrix/Matrix2.hpp>
#include <engine/math/matrix/Matrix3.hpp>

template<typename T>
std::ostream& operator<<(std::ostream& os, Math::Vector2<T> v)
{
    std::cout << '[' << v.X << ' ' << v.Y << ']';
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, Math::Vector3<T> v)
{
    std::cout << '[' << v.X << ' ' << v.Y << ' ' << v.Z << ']';
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, Math::Vector4<T> v)
{
    std::cout << '[' << v.X << ' ' << v.Y << ' ' << v.Z << ' ' << v.W << ']';
    return os;
}

int main()
{
    Math::Vec4 v1{1, 2, 3, 4};
    Math::Vec4 v2{1, 2, 3, 4};

    Math::Mat2 m = Math::Mat2::CreateRotation(0.1f).GetScaled({2.0f});
    std::cout << m[0][0] << ' ' << m[0][1] << '\n' << m[1][0] << ' ' << m[1][1] << '\n';
    
    std::cout << v1 + v2 << '\n';
    std::cout << v1 - v2 << '\n';
    std::cout << v1 * v2 << '\n';
    std::cout << v1 / v2 << '\n';
    std::cout << v1 + 1 << '\n';
    std::cout << v1 - 1 << '\n';
    std::cout << v1 * 2 << '\n';
    std::cout << v1 / 2 << '\n';
    std::cout << v1[0] << ' ' << v1[1] << ' ' << v1[2] << ' ' << v1[3] << '\n';
    std::cout << v1.Length() << '\n';
    std::cout << v1.LengthSquared() << '\n';
    std::cout << v1.GetNormalized().Length() << '\n';
    std::cout << v1.Dot(v2) << '\n';
}