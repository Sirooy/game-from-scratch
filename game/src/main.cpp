#include <iostream>
#include <engine/math/vector/Vector2.hpp>
#include <engine/math/vector/Vector3.hpp>
#include <engine/math/vector/Vector4.hpp>
#include <engine/math/matrix/Matrix2.hpp>
#include <engine/math/matrix/Matrix3.hpp>
#include <engine/math/matrix/Matrix4.hpp>
#include <engine/math/quat/Quaternion.hpp>
#include <engine/input/Input.hpp>
#include <GLFW/glfw3.h>
#include <numbers>

template<typename T>
std::ostream& operator<<(std::ostream& os, math::Vector2<T> v)
{
    std::cout << '[' << v.x << ' ' << v.y << ']';
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, math::Vector3<T> v)
{
    std::cout << '[' << v.x << ' ' << v.y << ' ' << v.z << ']';
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, math::Vector4<T> v)
{
    std::cout << '[' << v.x << ' ' << v.y << ' ' << v.z << ' ' << v.w << ']';
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
    input::Init(window);

    while (!glfwWindowShouldClose(window))
    {
        
        glfwSwapBuffers(window);
        input::Update();
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}