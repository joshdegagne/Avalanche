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

///////////////////////////////////////
///VIBRATION FUNCTION
///SET BOTH TO 0 TO STOP VIBRATION
///////////////////////////////////////
void ControllerInputManager::vibrate(int controllerNum, int leftVal, int rightVal)
{
	if (!controllerIsValid(controllerNum))
		return;

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
	if (!controllerIsValid(controllerNum))
		return false;

	return !!(getState(controllerNum).Gamepad.wButtons & XINPUT_GAMEPAD_A);
}
bool ControllerInputManager::getButtonB(int controllerNum)
{
	if (!controllerIsValid(controllerNum))
		return false;

	return !!(getState(controllerNum).Gamepad.wButtons & XINPUT_GAMEPAD_B);
}
bool ControllerInputManager::getButtonX(int controllerNum)
{
	if (!controllerIsValid(controllerNum))
		return false;

	return !!(getState(controllerNum).Gamepad.wButtons & XINPUT_GAMEPAD_X);
}
bool ControllerInputManager::getButtonY(int controllerNum)
{
	if (!controllerIsValid(controllerNum))
		return false;

	return !!(getState(controllerNum).Gamepad.wButtons & XINPUT_GAMEPAD_Y);
}
bool ControllerInputManager::getButtonLB(int controllerNum)
{
	if (!controllerIsValid(controllerNum))
		return false;

	return !!(getState(controllerNum).Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER);
}
bool ControllerInputManager::getButtonRB(int controllerNum)
{
	if (!controllerIsValid(controllerNum))
		return false;

	return !!(getState(controllerNum).Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER);
}
bool ControllerInputManager::getButtonLS(int controllerNum)
{
	if (!controllerIsValid(controllerNum))
		return false;

	return !!(getState(controllerNum).Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB);
}
bool ControllerInputManager::getButtonRS(int controllerNum)
{
	if (!controllerIsValid(controllerNum))
		return false;

	return !!(getState(controllerNum).Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB);
}
bool ControllerInputManager::getButtonStart(int controllerNum)
{
	if (!controllerIsValid(controllerNum))
		return false;

	return !!(getState(controllerNum).Gamepad.wButtons & XINPUT_GAMEPAD_START);
}
bool ControllerInputManager::getButtonBack(int controllerNum)
{
	if (!controllerIsValid(controllerNum))
		return false;

	return !!(getState(controllerNum).Gamepad.wButtons & XINPUT_GAMEPAD_BACK);
}

///////////////////////////////////////
///STICK INPUT
///////////////////////////////////////
float ControllerInputManager::getLS_X(int controllerNum)
{
	if (!controllerIsValid(controllerNum))
		return -2;

	short thumbValue = getState(controllerNum).Gamepad.sThumbLX;

	if (thumbValue > XINPUT_GAMEPAD_THUMB_DEADZONE || thumbValue < (0-XINPUT_GAMEPAD_THUMB_DEADZONE))
	{
		if (thumbValue >= 0)
			thumbValue -= (XINPUT_GAMEPAD_THUMB_DEADZONE-1); //Changes range to 0 - 24576  (NO DEADZONE)
		else
			thumbValue += XINPUT_GAMEPAD_THUMB_DEADZONE; //Changes range to -24576 - 0 (NO DEADZONE)

		return ((float)thumbValue/(32768 - XINPUT_GAMEPAD_THUMB_DEADZONE));
	}
	else
		return 0;
		
}
float ControllerInputManager::getLS_Y(int controllerNum)
{
	if (!controllerIsValid(controllerNum))
		return -2;

	short thumbValue = getState(controllerNum).Gamepad.sThumbLY;

	if (thumbValue > XINPUT_GAMEPAD_THUMB_DEADZONE || thumbValue < (0-XINPUT_GAMEPAD_THUMB_DEADZONE))
	{
		if (thumbValue >= 0)
			thumbValue -= (XINPUT_GAMEPAD_THUMB_DEADZONE-1); //Changes range to 0 - 24576  (NO DEADZONE)
		else
			thumbValue += XINPUT_GAMEPAD_THUMB_DEADZONE; //Changes range to -24576 - 0 (NO DEADZONE)
		
		return ((float)thumbValue/(32768 - XINPUT_GAMEPAD_THUMB_DEADZONE));
	}
	else
		return 0;
}
float ControllerInputManager::getRS_X(int controllerNum)
{
	if (!controllerIsValid(controllerNum))
		return -2;

	short thumbValue = getState(controllerNum).Gamepad.sThumbRX;

	if (thumbValue > XINPUT_GAMEPAD_THUMB_DEADZONE || thumbValue < (0-XINPUT_GAMEPAD_THUMB_DEADZONE))
	{
		if (thumbValue >= 0)
			thumbValue -= (XINPUT_GAMEPAD_THUMB_DEADZONE-1); //Changes range to 0 - 24576  (NO DEADZONE)
		else
			thumbValue += XINPUT_GAMEPAD_THUMB_DEADZONE; //Changes range to -24576 - 0 (NO DEADZONE)
		
		return ((float)thumbValue/(32768 - XINPUT_GAMEPAD_THUMB_DEADZONE));
	}
	else
		return 0;
}
float ControllerInputManager::getRS_Y(int controllerNum)
{
	if (!controllerIsValid(controllerNum))
		return -2;

	short thumbValue = getState(controllerNum).Gamepad.sThumbRY;

	if (thumbValue > XINPUT_GAMEPAD_THUMB_DEADZONE || thumbValue < (0-XINPUT_GAMEPAD_THUMB_DEADZONE))
	{
		if (thumbValue >= 0)
			thumbValue -= (XINPUT_GAMEPAD_THUMB_DEADZONE-1); //Changes range to 0 - 24576  (NO DEADZONE)
		else
			thumbValue += XINPUT_GAMEPAD_THUMB_DEADZONE; //Changes range to -24576 - 0 (NO DEADZONE)
		
		return ((float)thumbValue/(32768 - XINPUT_GAMEPAD_THUMB_DEADZONE));
	}
	else
		return 0;
}

XMFLOAT2 ControllerInputManager::getLS(int controllerNum)
{
	XMFLOAT2 temp;
	temp.x = getLS_X(controllerNum);
	temp.y = getLS_Y(controllerNum);
	return temp;
}
XMFLOAT2 ControllerInputManager::getRS(int controllerNum)
{
	XMFLOAT2 temp;
	temp.x = getRS_X(controllerNum);
	temp.y = getRS_Y(controllerNum);
	return temp;
}

///////////////////////////////////////
///TRIGGER INPUT
///////////////////////////////////////
float ControllerInputManager::getLT(int controllerNum)
{
	if (!controllerIsValid(controllerNum))
		return -2;

	short triggerValue = getState(controllerNum).Gamepad.bLeftTrigger - XINPUT_GAMEPAD_TRIGGER_THRESHOLD; //Changes range to 0 - 225 (NO DEADZONE)
	
	if (triggerValue < 0)
		triggerValue = 0;

	return ((float)triggerValue/(255 - XINPUT_GAMEPAD_TRIGGER_THRESHOLD));
}
float ControllerInputManager::getRT(int controllerNum)
{
	if (!controllerIsValid(controllerNum))
		return -2;

	short triggerValue = getState(controllerNum).Gamepad.bRightTrigger - XINPUT_GAMEPAD_TRIGGER_THRESHOLD; //Changes range to 0 - 225 (NO DEADZONE)
	
	if (triggerValue < 0)
		triggerValue = 0;

	return ((float)triggerValue/(255 - XINPUT_GAMEPAD_TRIGGER_THRESHOLD));
}


///////////////////////////////////////
///HELPER FUNCTION
///////////////////////////////////////
XINPUT_STATE ControllerInputManager::getState(int controllerNum)
{
    // Zeroise the state
    ZeroMemory(&_controllerState, sizeof(XINPUT_STATE));

    // Get the state
    XInputGetState(controllerNum, &_controllerState[controllerNum]);

    return _controllerState[controllerNum];
}

bool ControllerInputManager::controllerIsValid(int controllerNum)
{
	return ( (controllerNum >=0 && controllerNum < 4) && (isConnected(controllerNum)) );
}