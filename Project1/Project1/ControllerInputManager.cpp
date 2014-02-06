#include "ControllerInputManager.h"

bool ControllerInputManager::isConnected(int controllerNum)
{
    // Zeroise the state
    ZeroMemory(&_controllerState, sizeof(XINPUT_STATE));

    // Get the state
    DWORD Result = XInputGetState(controllerNum, &_controllerState[controllerNum]);

    if(Result == ERROR_SUCCESS)
        return true;
    else
        return false;
}

void ControllerInputManager::vibrate(int controllerNum, int leftVal, int rightVal)
{
    // Create a Vibraton State
    XINPUT_VIBRATION Vibration;

    // Zeroise the Vibration
    ZeroMemory(&Vibration, sizeof(XINPUT_VIBRATION));

    // Set the Vibration Values
    Vibration.wLeftMotorSpeed = leftVal;
    Vibration.wRightMotorSpeed = rightVal;

    // Vibrate the controller
    XInputSetState(controllerNum, &Vibration);
}

///////////////////////////////////////
///BASIC INPUT FUNCTIONS
///////////////////////////////////////
bool ControllerInputManager::getButtonA(int controllerNum)
{
	return !!(getState(controllerNum).Gamepad.wButtons & XINPUT_GAMEPAD_A);
}
bool ControllerInputManager::getButtonB(int controllerNum)
{
	return !!(getState(controllerNum).Gamepad.wButtons & XINPUT_GAMEPAD_B);
}
bool ControllerInputManager::getButtonX(int controllerNum)
{
	return !!(getState(controllerNum).Gamepad.wButtons & XINPUT_GAMEPAD_X);
}
bool ControllerInputManager::getButtonY(int controllerNum)
{
	return !!(getState(controllerNum).Gamepad.wButtons & XINPUT_GAMEPAD_Y);
}
bool ControllerInputManager::getButtonLB(int controllerNum)
{
	return !!(getState(controllerNum).Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER);
}
bool ControllerInputManager::getButtonRB(int controllerNum)
{
	return !!(getState(controllerNum).Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER);
}
bool ControllerInputManager::getButtonLS(int controllerNum)
{
	return !!(getState(controllerNum).Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB);
}
bool ControllerInputManager::getButtonRS(int controllerNum)
{
	return !!(getState(controllerNum).Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB);
}
bool ControllerInputManager::getButtonStart(int controllerNum)
{
	return !!(getState(controllerNum).Gamepad.wButtons & XINPUT_GAMEPAD_START);
}
bool ControllerInputManager::getButtonBack(int controllerNum)
{
	return !!(getState(controllerNum).Gamepad.wButtons & XINPUT_GAMEPAD_BACK);
}

float ControllerInputManager::getLS_X(int controllerNum)
{
	short thumbValue = getState(controllerNum).Gamepad.sThumbLX;
	if (thumbValue >= 0)
		thumbValue -= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE; //Changes range to 0 - 24576
	else
		thumbValue += XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE; //Changes range to -24576 - 0
		
	return (float)(thumbValue/24576);
}
float ControllerInputManager::getLS_Y(int controllerNum)
{
	short thumbValue = getState(controllerNum).Gamepad.sThumbLY;
	if (thumbValue >= 0)
		thumbValue -= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE; //Changes range to 0 - 24576
	else
		thumbValue += XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE; //Changes range to -24576 - 0
		
	return (float)(thumbValue/24576);
}
float ControllerInputManager::getRS_X(int controllerNum)
{
	return 0;
}
float ControllerInputManager::getRS_Y(int controllerNum)
{
	return 0;
}

/////

XINPUT_STATE ControllerInputManager::getState(int controllerNum)
{
    // Zeroise the state
    ZeroMemory(&_controllerState, sizeof(XINPUT_STATE));

    // Get the state
    XInputGetState(controllerNum, &_controllerState[controllerNum]);

    return _controllerState[controllerNum];
}