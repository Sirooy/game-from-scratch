#pragma once
#include <cstring>
#include <glfw/glfw3.h>
#include "../math/vector/vector2.hpp"

namespace Input
{

enum class MouseButton
{
    Left   = GLFW_MOUSE_BUTTON_LEFT,
    Right  = GLFW_MOUSE_BUTTON_RIGHT,
    Middle = GLFW_MOUSE_BUTTON_MIDDLE,
    B4     = GLFW_MOUSE_BUTTON_4,
    B5     = GLFW_MOUSE_BUTTON_5,
    B6     = GLFW_MOUSE_BUTTON_6,
    B7     = GLFW_MOUSE_BUTTON_7,
    B8     = GLFW_MOUSE_BUTTON_8,
};

enum class MouseState
{
    Default = GLFW_CURSOR_NORMAL, 
    Hidden  = GLFW_CURSOR_HIDDEN,
    Locked  = GLFW_CURSOR_DISABLED
};

class Mouse
{
public:
    Mouse() = delete;

    static void Init(GLFWwindow* window)
    {
        GlfwWindow = window;

        glfwSetMouseButtonCallback(window, [](GLFWwindow* glfwWindow, int button, int action, int mods)
        {
            ButtonStates[button] = static_cast<bool>(action);
        });

        glfwSetCursorPosCallback(window, [](GLFWwindow* glfwWindow, double xPos, double yPos)
        {
            Position = Math::Vec2(
                static_cast<float>(xPos),
                static_cast<float>(yPos));
        });

        glfwSetScrollCallback(window, [](GLFWwindow* glfwWindow, double xOffset, double yOffset)
        {
            Scroll += Math::Vec2(
                static_cast<float>(xOffset),
                static_cast<float>(yOffset));
        });
    }

    static void Update()
    {
        LastPosition = Position;
        std::memcpy(LastButtonStates, ButtonStates, BUTTON_COUNT);
    }

    static bool IsButtonDown(MouseButton button)
    {
        return ButtonStates[static_cast<int>(button)];
    }

    static bool IsButtonUp(MouseButton button)
    {
        return !ButtonStates[static_cast<int>(button)];
    }

    static bool IsButtonPressed(MouseButton button)
    {
        return ButtonStates[static_cast<int>(button)] && 
            !LastButtonStates[static_cast<int>(button)];
    }

    static bool IsButtonReleased(MouseButton button)
    {
        return !ButtonStates[static_cast<int>(button)] && 
            LastButtonStates[static_cast<int>(button)];
    }

    static void SetPosition(Math::Vec2 position)
    {
        Position = position;
        glfwSetCursorPos(GlfwWindow, position.X, position.Y);
    }

    static void SetState(MouseState state)
    {
        glfwSetInputMode(GlfwWindow, GLFW_CURSOR, static_cast<int32_t>(state));

        //Reset the mouse position if the mouse has been unlocked
        //to avoid a 
        if(Mouse::State == MouseState::Locked && state != MouseState::Locked)
        {
            double x, y;
            glfwGetCursorPos(GlfwWindow, &x, &y);

            Math::Vec2 newPosition(static_cast<float>(x), static_cast<float>(y));
            Position     = newPosition;
            LastPosition = newPosition; 
        }

        Mouse::State = state;
    }

    static bool PositionHasChanged()    { return Position != LastPosition; }
    static bool PositionXHasChanged()   { return Position.X != LastPosition.X; }
    static bool PositionYHasChanged()   { return Position.Y != LastPosition.Y; }
    static Math::Vec2 GetPosition()     { return Position; }
    static float GetX()                 { return Position.X; }
    static float GetY()                 { return Position.Y; }
    static Math::Vec2 GetLastPosition() { return LastPosition; }
    static float GetLastX()             { return LastPosition.X; }
    static float GetLastY()             { return LastPosition.Y; }
    static Math::Vec2 GetPositionDiff() { return Position - LastPosition; }
    static float GetPositionXDiff()     { return Position.X - LastPosition.X; }
    static float GetPositionYDiff()     { return Position.Y - LastPosition.Y; }
    static bool ScrollHasChanged()      { return Scroll != LastScroll; }
    static bool ScrollXHasChanged()     { return Scroll.X != LastScroll.X; }
    static bool ScrollYHasChanged()     { return Scroll.Y != LastScroll.Y; }
    static Math::Vec2 GetScroll()       { return Scroll; }
    static float GetScrollX()           { return Scroll.X; }
    static float GetScrollY()           { return Scroll.Y; }
    static Math::Vec2 GetScrollDiff()   { return Scroll - LastScroll; }
    static float GetScrollXDiff()       { return Scroll.X - LastScroll.X; }
    static float GetScrollYDiff()       { return Scroll.Y - LastScroll.Y; }
    static MouseState GetState()        { return State; }
    
private:
    inline static constexpr uint32_t BUTTON_COUNT = GLFW_MOUSE_BUTTON_LAST + 1;

    inline static bool ButtonStates[BUTTON_COUNT]     { };
    inline static bool LastButtonStates[BUTTON_COUNT] { };
    inline static MouseState State                    { MouseState::Default };
    inline static Math::Vec2 Position                 { 0.0f, 0.0f };
    inline static Math::Vec2 LastPosition             { 0.0f, 0.0f };
    inline static Math::Vec2 Scroll                   { 0.0f, 0.0f };
    inline static Math::Vec2 LastScroll               { 0.0f, 0.0f };
    inline static GLFWwindow* GlfwWindow              { nullptr };
};

} //namespace Input