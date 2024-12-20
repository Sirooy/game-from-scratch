#include <iostream>
#include <engine/math/vector/vector2.hpp>
#include <engine/math/vector/vector3.hpp>

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


int main()
{
    Math::Vec3 v1{1, 2, 3};
    Math::Vec3 v2{1, 2, 3};
    
    std::cout << v1 + v2 << '\n';
    std::cout << v1 - v2 << '\n';
    std::cout << v1 * v2 << '\n';
    std::cout << v1 / v2 << '\n';
    std::cout << v1 + 1 << '\n';
    std::cout << v1 - 1 << '\n';
    std::cout << v1 * 2 << '\n';
    std::cout << v1 / 2 << '\n';
    std::cout << v1[0] << ' ' << v1[1] << ' ' << v1[2] << '\n';
    std::cout << v1.Length() << '\n';
    std::cout << v1.LengthSquared() << '\n';
    std::cout << v1.GetNormalized().Length() << '\n';
    std::cout << v1.Dot(v2) << '\n';
}