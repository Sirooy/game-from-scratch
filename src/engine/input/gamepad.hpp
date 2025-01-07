#pragma once
#include <cstring>
#include <glfw/glfw3.h>
#include "../math/vector/vector2.hpp"

namespace Input
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
    Gamepad() = delete;

    static void Init()
    {
        //Count the number of gamepads connected on initialization in case
        //the gamepads were already connected before starting the application
        GLFWgamepadstate state;
        for(int32_t i = 0;i < MAX_GAMEPADS_CONNECTED; ++i)
        {
            if(glfwGetGamepadState(GLFW_JOYSTICK_1 + i, &state) == GLFW_TRUE)
            {
                NumConnected++;
                Data[i].IsConnected = true;
                LastConnectedId  = GLFW_JOYSTICK_1 + i;
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
        std::memcpy(LastData, Data, sizeof(GamepadData) * MAX_GAMEPADS_CONNECTED);

        for(int32_t i = 0;i < LastConnectedId + 1; ++i)
        {
            glfwGetGamepadState(GLFW_JOYSTICK_1 + i, &Data[i].State);
        }
    }

    static bool IsButtonDown(int32_t index, GamepadButton button)
    {
        return Data[index].State.buttons[static_cast<int>(button)] == 1;
    }

    static bool IsButtonUp(int32_t index, GamepadButton button)
    {
        return Data[index].State.buttons[static_cast<int>(button)] == 0;
    }

    static bool IsButtonPressed(int32_t index, GamepadButton button)
    {
        return LastData[index].State.buttons[static_cast<int>(button)] == 0 && 
            Data[index].State.buttons[static_cast<int>(button)] == 1;
    }

    static bool IsButtonReleased(int32_t index, GamepadButton button)
    {
        return LastData[index].State.buttons[static_cast<int>(button)] == 1 && 
            Data[index].State.buttons[static_cast<int>(button)] == 0;
    }

    static Math::Vec2 GetAxis(int32_t index, GamepadAxis axis)
    {
        
        return Math::Vec2(Data[index].State.axes[static_cast<int>(axis) + 0],
                          Data[index].State.axes[static_cast<int>(axis) + 1]);
    }

    static float GetTrigger(int32_t index, GamepadTrigger trigger)
    {
        return Data[index].State.axes[static_cast<int>(trigger)];
    }

    static bool IsConnected(int32_t index)
    {
        return Data[index].IsConnected;
    }

    static bool HasBeenConnected(int32_t index)
    {
        return !LastData[index].IsConnected && 
            Data[index].IsConnected;
    }

    static bool HasBeenDisconnected(int32_t index) 
    { 
        return LastData[index].IsConnected && 
            !Data[index].IsConnected;
    }

    static int32_t GetNumConnected() { return NumConnected; }

private:
    static void OnConnectGamepad(int32_t id)
    {
        NumConnected = std::min(NumConnected + 1, 
            MAX_GAMEPADS_CONNECTED);
        Data[id].IsConnected = true;

        if(id > LastConnectedId)
            LastConnectedId = id;
    }

    static void OnDisconnectGamepad(int32_t id)
    {
        NumConnected = std::max(NumConnected - 1, 0);
        Data[id].IsConnected = false;
        Data[id].State       = { };
        
        //Reset the last connected gamepad index when there are no gamepads connected
        if(NumConnected == 0)
            LastConnectedId = -1;
        else if(LastConnectedId == id)
        {
            //If the gamepad disconnected had the last id, 
            //search for the new connected gamepad with the last id
            int32_t index = LastConnectedId - 1;
            while(index > -1 && !Data[index].IsConnected)
                index--;
            LastConnectedId = index;
        }
    }
    
private:
    struct GamepadData
    {
        GamepadData() { } //Empty constructor needs to be declared due to a compiler bug

        bool IsConnected       { false };
        GLFWgamepadstate State { };
    };

    inline static constexpr int32_t MAX_GAMEPADS_CONNECTED = GLFW_JOYSTICK_LAST + 1;

    inline static GamepadData Data[MAX_GAMEPADS_CONNECTED]     { };
    inline static GamepadData LastData[MAX_GAMEPADS_CONNECTED] { };
    inline static int32_t NumConnected                         { 0 };
    inline static int32_t LastConnectedId                      {-1 };
};

} //namespace Input