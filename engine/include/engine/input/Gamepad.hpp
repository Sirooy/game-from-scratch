#pragma once
#include <cstring>
#include <GLFW/glfw3.h>
#include "../math/vector/vector2.hpp"

namespace input
{

enum class GamepadButton
{
    //Xbox buttons
    A           = GLFW_GAMEPAD_BUTTON_A,
    B           = GLFW_GAMEPAD_BUTTON_B,
    X           = GLFW_GAMEPAD_BUTTON_X,
    Y           = GLFW_GAMEPAD_BUTTON_Y,
    LeftBumper  = GLFW_GAMEPAD_BUTTON_LEFT_BUMPER,
    RightBumper = GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER,
    Back        = GLFW_GAMEPAD_BUTTON_BACK,
    Start       = GLFW_GAMEPAD_BUTTON_START,
    Guide       = GLFW_GAMEPAD_BUTTON_GUIDE,
    LeftStick   = GLFW_GAMEPAD_BUTTON_LEFT_THUMB,
    RightStick  = GLFW_GAMEPAD_BUTTON_RIGHT_THUMB,
    DPadUp      = GLFW_GAMEPAD_BUTTON_DPAD_UP,
    DPadRight   = GLFW_GAMEPAD_BUTTON_DPAD_RIGHT,
    DPadDown    = GLFW_GAMEPAD_BUTTON_DPAD_DOWN,
    DPadLeft    = GLFW_GAMEPAD_BUTTON_DPAD_LEFT,
    //Playstation buttons
    Cross       = A,
    Circle      = B,
    Square      = X,
    Triangle    = Y,
    L1          = LeftBumper,
    R1          = RightBumper,
    Select      = Back,
    PS          = Guide
};

enum class GamepadTrigger
{
    Left  = GLFW_GAMEPAD_AXIS_LEFT_TRIGGER,
    Right = GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER
};

enum class GamepadAxis
{
    Left  = GLFW_GAMEPAD_AXIS_LEFT_X,
    Right = GLFW_GAMEPAD_AXIS_RIGHT_X
};

class Gamepad
{
public:
    inline static constexpr int32_t MaxGamepads = GLFW_JOYSTICK_LAST + 1;

    Gamepad() = delete;

    static void Init()
    {
        //Count the number of gamepads connected on initialization in case
        //the gamepads were already connected before starting the application
        GLFWgamepadstate state;
        for(int32_t i = 0;i < MaxGamepads; ++i)
        {
            if(glfwGetGamepadState(GLFW_JOYSTICK_1 + i, &state) == GLFW_TRUE)
            {
                m_NumConnected++;
                m_Data[i].isConnected = true;
                m_LastConnectedId  = GLFW_JOYSTICK_1 + i;
            }
        }

        glfwSetJoystickCallback([](int id, int event)
        {
            if(event == GLFW_CONNECTED)
                OnConnectGamepad(id);
            else if(event == GLFW_DISCONNECTED)
                OnDisconnectGamepad(id);
        });
    }

    static void Update()
    {
        std::memcpy(m_LastData, m_Data, sizeof(GamepadData) * MaxGamepads);

        for(int32_t i = 0;i < m_LastConnectedId + 1; ++i)
        {
            glfwGetGamepadState(GLFW_JOYSTICK_1 + i, &m_Data[i].state);
        }
    }

    static bool IsButtonDown(int32_t index, GamepadButton button)
    {
        return m_Data[index].state.buttons[static_cast<int>(button)] == 1;
    }

    static bool IsButtonUp(int32_t index, GamepadButton button)
    {
        return m_Data[index].state.buttons[static_cast<int>(button)] == 0;
    }

    static bool IsButtonPressed(int32_t index, GamepadButton button)
    {
        return m_LastData[index].state.buttons[static_cast<int>(button)] == 0 && 
            m_Data[index].state.buttons[static_cast<int>(button)] == 1;
    }

    static bool IsButtonReleased(int32_t index, GamepadButton button)
    {
        return m_LastData[index].state.buttons[static_cast<int>(button)] == 1 && 
            m_Data[index].state.buttons[static_cast<int>(button)] == 0;
    }

    static math::Vec2 GetAxis(int32_t index, GamepadAxis axis)
    {
        
        return math::Vec2(m_Data[index].state.axes[static_cast<int>(axis) + 0],
                          m_Data[index].state.axes[static_cast<int>(axis) + 1]);
    }

    static float GetTrigger(int32_t index, GamepadTrigger trigger)
    {
        return m_Data[index].state.axes[static_cast<int>(trigger)];
    }

    static bool IsConnected(int32_t index)
    {
        return m_Data[index].isConnected;
    }

    static bool HasBeenConnected(int32_t index)
    {
        return !m_LastData[index].isConnected && 
            m_Data[index].isConnected;
    }

    static bool HasBeenDisconnected(int32_t index) 
    { 
        return m_LastData[index].isConnected && 
            !m_Data[index].isConnected;
    }

    static int32_t GetNumConnected() { return m_NumConnected; }

private:
    static void OnConnectGamepad(int32_t id)
    {
        m_NumConnected = std::min(m_NumConnected + 1, 
            MaxGamepads);
        m_Data[id].isConnected = true;

        if(id > m_LastConnectedId)
            m_LastConnectedId = id;
    }

    static void OnDisconnectGamepad(int32_t id)
    {
        m_NumConnected = std::max(m_NumConnected - 1, 0);
        m_Data[id].isConnected = false;
        m_Data[id].state       = { };
        
        //Reset the last connected gamepad index when there are no gamepads connected
        if(m_NumConnected == 0)
            m_LastConnectedId = -1;
        else if(m_LastConnectedId == id)
        {
            //If the gamepad disconnected had the last id, 
            //search for the new connected gamepad with the last id
            int32_t index = m_LastConnectedId - 1;
            while(index > -1 && !m_Data[index].isConnected)
                index--;
            m_LastConnectedId = index;
        }
    }
    
private:
    struct GamepadData
    {
        GamepadData() { } //Empty constructor needs to be declared due to a compiler bug

        bool isConnected       { false };
        GLFWgamepadstate state { };
    };

    inline static GamepadData m_Data[MaxGamepads]     { };
    inline static GamepadData m_LastData[MaxGamepads] { };
    inline static int32_t m_NumConnected              { 0 };
    inline static int32_t m_LastConnectedId           {-1 };
};

} //namespace input