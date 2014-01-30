#ifndef GAME_H
#define GAME_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <iostream>
#include <string>

#include "Graphics/Graphics.h"
#include "Entity.h"
#include "Player.h"
#include "DirectXHelper.h"

using namespace std;

class Game {
	public:
		//Constructors
		Game();
		Game(const Game&);
		~Game();

		//This method is used to intercept the windows messages
		//This is how windows messages or events get into out application
		LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

	private:
		LPCWSTR m_applicationName;
		HINSTANCE m_hinstance;
		HWND m_hwnd;  //handle to the Windows window (client window for the application)

		Graphics* m_Graphics; //our graphics class object that encapsulates the graphics pipeline
		//CineCamera* m_Camera; //our encapsulation of where the camera is looking at our world
};

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
static Game* ApplicationHandle = 0;


#endif
