////////////////////////////////////////////////////////////////////////////////
// Filename: KeyInput.cpp
////////////////////////////////////////////////////////////////////////////////
#include "KeyInput.h"


KeyInput::KeyInput()
{
	for(int i=0; i<256; i++)
		keys[i] = false;
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