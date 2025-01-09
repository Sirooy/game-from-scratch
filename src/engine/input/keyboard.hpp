#pragma once
#include <cstring>
#include <glfw/glfw3.h>

namespace input
{

enum class KeyCode
{
    N0            = GLFW_KEY_0,
    N1            = GLFW_KEY_1,
    N2            = GLFW_KEY_2,
    N3            = GLFW_KEY_3,
    N4            = GLFW_KEY_4,
    N5            = GLFW_KEY_5,
    N6            = GLFW_KEY_6,
    N7            = GLFW_KEY_7,
    N8            = GLFW_KEY_8,
    N9            = GLFW_KEY_9,
    A             = GLFW_KEY_A,
    B             = GLFW_KEY_B,
    C             = GLFW_KEY_C,
    D             = GLFW_KEY_D,
    E             = GLFW_KEY_E,
    F             = GLFW_KEY_F,
    G             = GLFW_KEY_G,
    H             = GLFW_KEY_H,
    I             = GLFW_KEY_I,
    J             = GLFW_KEY_J,
    K             = GLFW_KEY_K,
    L             = GLFW_KEY_L,
    M             = GLFW_KEY_M,
    N             = GLFW_KEY_N,
    O             = GLFW_KEY_O,
    P             = GLFW_KEY_P,
    Q             = GLFW_KEY_Q,
    R             = GLFW_KEY_R,
    S             = GLFW_KEY_S,
    T             = GLFW_KEY_T,
    U             = GLFW_KEY_U,
    V             = GLFW_KEY_V,
    W             = GLFW_KEY_W,
    X             = GLFW_KEY_X,
    Y             = GLFW_KEY_Y,
    Z             = GLFW_KEY_Z,
    Space         = GLFW_KEY_SPACE,
    Up            = GLFW_KEY_UP,
    Right         = GLFW_KEY_RIGHT,
    Down          = GLFW_KEY_DOWN,
    Left          = GLFW_KEY_LEFT,
    RAlt          = GLFW_KEY_RIGHT_ALT,
    RControl      = GLFW_KEY_RIGHT_CONTROL,
    RShift        = GLFW_KEY_RIGHT_SHIFT,
    RSuper        = GLFW_KEY_RIGHT_SUPER,
    LAlt          = GLFW_KEY_LEFT_ALT,
    LControl      = GLFW_KEY_LEFT_CONTROL,
    LShift        = GLFW_KEY_LEFT_SHIFT,
    LSuper        = GLFW_KEY_LEFT_SUPER,
    Tab           = GLFW_KEY_TAB,
    Escape        = GLFW_KEY_ESCAPE,
    Enter         = GLFW_KEY_ENTER,
    Back          = GLFW_KEY_BACKSLASH,
    Comma         = GLFW_KEY_COMMA,
    Period        = GLFW_KEY_PERIOD,
    Minus         = GLFW_KEY_MINUS,
    F1            = GLFW_KEY_F1,
    F2            = GLFW_KEY_F2,
    F3            = GLFW_KEY_F3,
    F4            = GLFW_KEY_F4,
    F5            = GLFW_KEY_F5,
    F6            = GLFW_KEY_F6,
    F7            = GLFW_KEY_F7,
    F8            = GLFW_KEY_F8,
    F9            = GLFW_KEY_F9,
    F10           = GLFW_KEY_F10,
    F11           = GLFW_KEY_F11,
    F12           = GLFW_KEY_F12,
    F13           = GLFW_KEY_F13,
    F14           = GLFW_KEY_F14,
    F15           = GLFW_KEY_F15,
    F16           = GLFW_KEY_F16,
    F17           = GLFW_KEY_F17,
    F18           = GLFW_KEY_F18,
    F19           = GLFW_KEY_F19,
    F20           = GLFW_KEY_F20,
    F21           = GLFW_KEY_F21,
    F22           = GLFW_KEY_F22,
    F23           = GLFW_KEY_F23,
    F24           = GLFW_KEY_F24,
    Numpad0       = GLFW_KEY_KP_0,
    Numpad1       = GLFW_KEY_KP_1,
    Numpad2       = GLFW_KEY_KP_2,
    Numpad3       = GLFW_KEY_KP_3,
    Numpad4       = GLFW_KEY_KP_4,
    Numpad5       = GLFW_KEY_KP_5,
    Numpad6       = GLFW_KEY_KP_6,
    Numpad7       = GLFW_KEY_KP_7,
    Numpad8       = GLFW_KEY_KP_8,
    Numpad9       = GLFW_KEY_KP_9,
    NumpadAdd     = GLFW_KEY_KP_ADD,
    NumpadSub     = GLFW_KEY_KP_SUBTRACT,
    NumpadMult    = GLFW_KEY_KP_MULTIPLY,
    NumpadDiv     = GLFW_KEY_KP_DIVIDE,
    NumpadDecimal = GLFW_KEY_KP_DECIMAL
};

class Keyboard
{
public:
    Keyboard() = delete;

    static void Init(GLFWwindow* window)
    {
        glfwSetKeyCallback(window, [](GLFWwindow* glfwWindow, int32_t key, 
            int32_t scancode, int32_t action, int32_t mods)
        {
            if(key != GLFW_KEY_UNKNOWN)
            {
                m_KeyStates[key] = static_cast<bool>(action);
            }
        });
    }

    static void Update()
    {
        std::memcpy(m_LastKeyStates, m_KeyStates, m_KeyCount);
    }

    static bool IsKeyDown(KeyCode key)
    {
        return m_KeyStates[static_cast<int>(key)];
    }

    static bool IsKeyUp(KeyCode key)
    {
        return !m_KeyStates[static_cast<int>(key)];
    }

    static bool IsKeyPressed(KeyCode key)
    {
        return !m_LastKeyStates[static_cast<int>(key)] && 
            m_KeyStates[static_cast<int>(key)];
    }

    static bool IsKeyReleased(KeyCode key)
    {
        return m_LastKeyStates[static_cast<int>(key)] && 
            !m_KeyStates[static_cast<int>(key)];
    }
    
private:
    inline static constexpr uint32_t m_KeyCount = GLFW_KEY_LAST + 1;

    inline static bool m_KeyStates[m_KeyCount]     { };
    inline static bool m_LastKeyStates[m_KeyCount] { };
};

} //namespace input