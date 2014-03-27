////////////////////////////////////////////////////////////////////////////////
// Filename: KeyInput.cpp
////////////////////////////////////////////////////////////////////////////////
#include "KeyInput.h"
#include "Game.h"


KeyInput::KeyInput()
{
	for(int i=0; i<256; i++)
		keys[i] = false;

	playerKeys[0][0] = VK_LEFT;
	playerKeys[0][1] = VK_RIGHT;
	playerKeys[0][2] = VK_UP;
	playerKeys[0][3] = VK_DOWN;
	playerKeys[0][4] = 0;
	playerKeys[0][5] = 0;
	playerKeys[0][6] = 0;

	playerKeys[1][0] = ascii_A;
	playerKeys[1][1] = ascii_D;
	playerKeys[1][2] = ascii_W;
	playerKeys[1][3] = ascii_S;
	playerKeys[1][4] = ascii_Z;
	playerKeys[1][5] = ascii_Q;
	playerKeys[1][6] = ascii_E;

	playerKeys[2][0] = ascii_F;
	playerKeys[2][1] = ascii_H;
	playerKeys[2][2] = ascii_T;
	playerKeys[2][3] = ascii_G;
	playerKeys[2][4] = VK_SPACE;
	playerKeys[2][5] = ascii_R;
	playerKeys[2][6] = ascii_Y;

	playerKeys[3][0] = ascii_J;
	playerKeys[3][1] = ascii_L;
	playerKeys[3][2] = ascii_I;
	playerKeys[3][3] = ascii_K;
	playerKeys[3][4] = ascii_M;
	playerKeys[3][5] = ascii_U;
	playerKeys[3][6] = ascii_O;
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