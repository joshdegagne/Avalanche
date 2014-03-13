////////////////////////////////////////////////////////////////////////////////
// Filename: KeyInput.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

////////////////////////////////////////////////////////////////////////////////
// ASCII Constants
////////////////////////////////////////////////////////////////////////////////
const int ascii_A = 65;
const int ascii_B = 66;
const int ascii_C = 67;
const int ascii_D = 68;
const int ascii_E = 69;
const int ascii_F = 70;
const int ascii_G = 71;
const int ascii_H = 72;
const int ascii_I = 73;
const int ascii_J = 74;
const int ascii_K = 75;
const int ascii_L = 76;
const int ascii_M = 77;
const int ascii_N = 78;
const int ascii_O = 79;
const int ascii_P = 80;
const int ascii_Q = 81;
const int ascii_R = 82;
const int ascii_S = 83;
const int ascii_T = 84;
const int ascii_U = 85;
const int ascii_V = 86;
const int ascii_W = 87;
const int ascii_X = 88;
const int ascii_Y = 89;
const int ascii_Z = 90;

////////////////////////////////////////////////////////////////////////////////
// Class Definition
////////////////////////////////////////////////////////////////////////////////
class KeyInput
{
public:
	KeyInput();
	KeyInput(const KeyInput&);
	~KeyInput();

	void KeyDown(unsigned int);
	void KeyUp(unsigned int);

	bool IsKeyDown(unsigned int);

private:
	bool keys[256];
};
