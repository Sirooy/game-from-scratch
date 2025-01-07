#pragma once
#include <glfw/glfw3.h>
#include "keyboard.hpp"
#include "mouse.hpp"
#include "gamepad.hpp"

namespace Input
{

void Init(GLFWwindow* glfwWindow);
void Update();

} //namespace Input

namespace Inp = Input;