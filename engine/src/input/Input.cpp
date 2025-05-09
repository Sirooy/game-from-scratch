#include <engine/input/Input.hpp>

namespace input
{

void Init(GLFWwindow* glfwWindow)
{
    Keyboard::Init(glfwWindow);
    Mouse::Init(glfwWindow);
    Gamepad::Init();
}

void Update()
{
    Keyboard::Update();
    Mouse::Update();
    Gamepad::Update();
}

} //namespace input