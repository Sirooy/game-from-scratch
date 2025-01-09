#pragma once
#include <glfw/glfw3.h>
#include "keyboard.hpp"
#include "mouse.hpp"
#include "gamepad.hpp"

namespace input
{

void Init(GLFWwindow* glfwWindow);
void Update();

} //namespace input

namespace inp = input;