#pragma once
#include <cstring>
#include <GLFW/glfw3.h>
#include "../math/vector/vector2.hpp"

namespace input
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
        m_GlfwWindow = window;

        glfwSetMouseButtonCallback(window, [](GLFWwindow* /*glfwWindow*/, int button, int action, int /*mods*/)
        {
            m_ButtonStates[button] = static_cast<bool>(action);
        });

        glfwSetCursorPosCallback(window, [](GLFWwindow* /*glfwWindow*/, double xPos, double yPos)
        {
            m_Position = math::Vec2(
                static_cast<float>(xPos),
                static_cast<float>(yPos));
        });

        glfwSetScrollCallback(window, [](GLFWwindow* /*glfwWindow*/, double xOffset, double yOffset)
        {
            m_Scroll += math::Vec2(
                static_cast<float>(xOffset),
                static_cast<float>(yOffset));
        });
    }

    static void Update()
    {
        m_LastPosition = m_Position;
        std::memcpy(m_LastButtonStates, m_ButtonStates, m_ButtonCount);
    }

    static bool IsButtonDown(MouseButton button)
    {
        return m_ButtonStates[static_cast<int>(button)];
    }

    static bool IsButtonUp(MouseButton button)
    {
        return !m_ButtonStates[static_cast<int>(button)];
    }

    static bool IsButtonPressed(MouseButton button)
    {
        return m_ButtonStates[static_cast<int>(button)] && 
            !m_LastButtonStates[static_cast<int>(button)];
    }

    static bool IsButtonReleased(MouseButton button)
    {
        return !m_ButtonStates[static_cast<int>(button)] && 
            m_LastButtonStates[static_cast<int>(button)];
    }

    static void SetPosition(math::Vec2 position)
    {
        m_Position = position;
        glfwSetCursorPos(m_GlfwWindow, position.x, position.y);
    }

    static void SetState(MouseState state)
    {
        glfwSetInputMode(m_GlfwWindow, GLFW_CURSOR, static_cast<int32_t>(state));

        //Reset the mouse position if the mouse has been unlocked
        //to avoid a 
        if(Mouse::m_State == MouseState::Locked && state != MouseState::Locked)
        {
            double x, y;
            glfwGetCursorPos(m_GlfwWindow, &x, &y);

            math::Vec2 newPosition(static_cast<float>(x), static_cast<float>(y));
            m_Position     = newPosition;
            m_LastPosition = newPosition; 
        }

        Mouse::m_State = state;
    }

    static bool PositionHasChanged()    { return m_Position != m_LastPosition; }
    static bool PositionXHasChanged()   { return m_Position.x != m_LastPosition.x; }
    static bool PositionYHasChanged()   { return m_Position.y != m_LastPosition.y; }
    static math::Vec2 GetPosition()     { return m_Position; }
    static float GetX()                 { return m_Position.x; }
    static float GetY()                 { return m_Position.y; }
    static math::Vec2 GetLastPosition() { return m_LastPosition; }
    static float GetLastX()             { return m_LastPosition.x; }
    static float GetLastY()             { return m_LastPosition.y; }
    static math::Vec2 GetPositionDiff() { return m_Position - m_LastPosition; }
    static float GetPositionXDiff()     { return m_Position.x - m_LastPosition.x; }
    static float GetPositionYDiff()     { return m_Position.y - m_LastPosition.y; }
    static bool ScrollHasChanged()      { return m_Scroll != m_LastScroll; }
    static bool ScrollXHasChanged()     { return m_Scroll.x != m_LastScroll.x; }
    static bool ScrollYHasChanged()     { return m_Scroll.y != m_LastScroll.y; }
    static math::Vec2 GetScroll()       { return m_Scroll; }
    static float GetScrollX()           { return m_Scroll.x; }
    static float GetScrollY()           { return m_Scroll.y; }
    static math::Vec2 GetScrollDiff()   { return m_Scroll - m_LastScroll; }
    static float GetScrollXDiff()       { return m_Scroll.x - m_LastScroll.x; }
    static float GetScrollYDiff()       { return m_Scroll.y - m_LastScroll.y; }
    static MouseState GetState()        { return m_State; }
    
private:
    inline static constexpr uint32_t m_ButtonCount = GLFW_MOUSE_BUTTON_LAST + 1;

    inline static bool m_ButtonStates[m_ButtonCount]     { };
    inline static bool m_LastButtonStates[m_ButtonCount] { };
    inline static MouseState m_State                     { MouseState::Default };
    inline static math::Vec2 m_Position                  { 0.0f, 0.0f };
    inline static math::Vec2 m_LastPosition              { 0.0f, 0.0f };
    inline static math::Vec2 m_Scroll                    { 0.0f, 0.0f };
    inline static math::Vec2 m_LastScroll                { 0.0f, 0.0f };
    inline static GLFWwindow* m_GlfwWindow               { nullptr };
};

} //namespace input