////////////////////////////////////////////////////////////////////////////////
// Filename: KeyInput.cpp
////////////////////////////////////////////////////////////////////////////////
#include "KeyInput.h"
#include "Game.h"


KeyInput::KeyInput()
{
	for(int i=0; i<256; i++)
		keys[i] = false;

	playerKeys[0][0] = ascii_A;
	playerKeys[0][1] = ascii_D;
	playerKeys[0][2] = ascii_W;
	playerKeys[0][3] = ascii_S;
	playerKeys[0][4] = ascii_Z;
	playerKeys[0][5] = ascii_Q;
	playerKeys[0][6] = ascii_E;

	playerKeys[1][0] = ascii_F;
	playerKeys[1][1] = ascii_H;
	playerKeys[1][2] = ascii_T;
	playerKeys[1][3] = ascii_G;
	playerKeys[1][4] = VK_SPACE;
	playerKeys[1][5] = ascii_R;
	playerKeys[1][6] = ascii_Y;

	playerKeys[2][0] = ascii_J;
	playerKeys[2][1] = ascii_L;
	playerKeys[2][2] = ascii_I;
	playerKeys[2][3] = ascii_K;
	playerKeys[2][4] = ascii_M;
	playerKeys[2][5] = ascii_U;
	playerKeys[2][6] = ascii_O;

	playerKeys[3][0] = VK_LEFT;		//Left
	playerKeys[3][1] = VK_RIGHT;	//Right
	playerKeys[3][2] = VK_UP;		//Up
	playerKeys[3][3] = VK_DOWN;		//Down
	playerKeys[3][4] = 0;			//A
	playerKeys[3][5] = 0;			//Left Trigger
	playerKeys[3][6] = 0;			//Right Trigger
}


KeyInput::KeyInput(const KeyInput& other)
{
}


KeyInput::~KeyInput()
{
}


void KeyInput::KeyDown(unsigned int input)
{
	// If a key is pressed then save that state in the key array.
	keys[input] = true;
	return;
}


void KeyInput::KeyUp(unsigned int input)
{
	// If a key is released then clear that state in the key array.
	keys[input] = false;
	return;
}


bool KeyInput::IsKeyDown(unsigned int key)
{
	// Return what state the key is in (pressed/not pressed).
	return keys[key];
}