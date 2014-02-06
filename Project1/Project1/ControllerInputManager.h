#ifndef CONTROLLERINPUT_H
#define CONTROLLERINPUT_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <XInput.h>
//#pragma comment(lib, "XInput.lib")

// XBOX Controller Class Definition
class ControllerInputManager
{
	public:	//For all public functions, the first integer is ALWAYS the controller number
		//Special functions
		bool isConnected(int);
		void vibrate(int, int leftVal = 0, int rightVal = 0);
		
		//Basic input functions
		bool  getButtonA(int);
		bool  getButtonB(int);
		bool  getButtonX(int);
		bool  getButtonY(int);
		bool  getButtonLB(int);
		bool  getButtonRB(int);
		bool  getButtonLS(int);
		bool  getButtonRS(int);
		bool  getButtonStart(int);
		bool  getButtonBack(int);
		short getLS_X(int);
		short getLS_Y(int);
		short getRS_X(int);
		short getRS_Y(int);

	private:
		XINPUT_STATE _controllerState[4];
		XINPUT_STATE getState(int);
};

#endif

////////////////////////////////////
///(SIMPLIFIED) EXTRA NOTATION FOR CLARITY
///See http://goo.gl/F8pBEc for more info
////////////////////////////////////
/*
struct XINPUT_STATE 
{
  DWORD          dwPacketNumber;	//Used for comparing two XINPUT_GAMEPADs for changes
  XINPUT_GAMEPAD Gamepad;			//See below
};

struct XINPUT_GAMEPAD 
{
  WORD  wButtons;		//All buttons are held in this bitmask. "this & BUTTON_BITMASK" to check if button is held down.
  BYTE  bLeftTrigger;	//Value from 0-255
  BYTE  bRightTrigger;  //Value from 0-255
  SHORT sThumbLX;		//Value from -32768 and 32767
  SHORT sThumbLY;		//Value from -32768 and 32767
  SHORT sThumbRX;		//Value from -32768 and 32767
  SHORT sThumbRY;		//Value from -32768 and 32767
};

BUTTON BITMASKS
---------------
XINPUT_GAMEPAD_DPAD_UP			 0x0001
XINPUT_GAMEPAD_DPAD_DOWN		 0x0002
XINPUT_GAMEPAD_DPAD_LEFT		 0x0004
XINPUT_GAMEPAD_DPAD_RIGHT		 0x0008
XINPUT_GAMEPAD_START			 0x0010
XINPUT_GAMEPAD_BACK				 0x0020
XINPUT_GAMEPAD_LEFT_THUMB		 0x0040
XINPUT_GAMEPAD_RIGHT_THUMB		 0x0080
XINPUT_GAMEPAD_LEFT_SHOULDER	 0x0100
XINPUT_GAMEPAD_RIGHT_SHOULDER	 0x0200
XINPUT_GAMEPAD_A				 0x1000
XINPUT_GAMEPAD_B				 0x2000
XINPUT_GAMEPAD_X				 0x4000
XINPUT_GAMEPAD_Y				 0x8000

*/