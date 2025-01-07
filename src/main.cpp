#include <iostream>
#include <engine/math/vector/vector2.hpp>
#include <engine/math/vector/vector3.hpp>
#include <engine/math/vector/vector4.hpp>
#include <engine/math/matrix/Matrix2.hpp>
#include <engine/math/matrix/Matrix3.hpp>
#include <engine/math/matrix/Matrix4.hpp>
#include <engine/math/quat/quaternion.hpp>
#include <engine/input/input.hpp>
#include <glfw/glfw3.h>
#include <numbers>

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
    if(!glfwInit())
    {
        throw std::runtime_error("Could not init glfw");
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(640, 480, "Window title", nullptr, nullptr);
    if (!window)
    {
        throw std::runtime_error("Could not create the window");
    }
    glfwSwapInterval(1);
    Input::Init(window);

    while (!glfwWindowShouldClose(window))
    {
        
        glfwSwapBuffers(window);
        Input::Update();
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}