#include <iostream>
#include <engine/math/vector2.hpp>

template<typename T>
std::ostream& operator<<(std::ostream& os, Math::Vector2<T> v)
{
    std::cout << '[' << v.X << ' ' << v.Y << ']';
    return os;
}

int main()
{
    Math::Vec2 v1{1, 2};
    Math::Vec2 v2{1, 2};
    
    std::cout << v1 + v2 << '\n';
    std::cout << v1 - v2 << '\n';
    std::cout << v1 * v2 << '\n';
    std::cout << v1 / v2 << '\n';
    std::cout << v1 + 1 << '\n';
    std::cout << v1 - 1 << '\n';
    std::cout << v1 * 2 << '\n';
    std::cout << v1 / 2 << '\n';
    std::cout << v1[0] << ' ' << v1[1] << '\n';
    std::cout << v1.Length() << '\n';
    std::cout << v1.LengthSquared() << '\n';
    std::cout << v1.GetNormalized().Length() << '\n';
    std::cout << v1.Dot(v2) << '\n';
}