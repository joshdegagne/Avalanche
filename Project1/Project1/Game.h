#ifndef GAME_H
#define GAME_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <iostream>
#include <string>

#include "Graphics/Graphics.h"
#include "quadModel.h"
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

		bool Initialize();
		void Shutdown();
		void Run();

		//This method is used to intercept the windows messages
		//This is how windows messages or events get into out application
		LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);
	private:
		bool Frame();
		void InitializeWindows(int&, int&);
		void ShutdownWindows();
		float getElapsedTime();

	private:
		LPCWSTR applicationName;
		HINSTANCE hinstance;
		HWND hwnd;  //handle to the Windows window (client window for the application)
		float previousTime;

		//InputClass* m_Input; //out input class object from which to obtain user inputs
		Graphics* graphics; //our graphics class object that encapsulates the graphics pipeline
		CineCamera* camera; //our encapsulation of where the camera is looking at our world

		ArrayList<Model>* gameModels; //container to hold all our game world models

		//Object Variables
		QuadModel* playField;

};

/////////////////////////
// FUNCTION PROTOTYPES //
/////////////////////////
static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

/////////////
// GLOBALS //
/////////////

//This is where windows will direct messages to.
//This will get set to our Game object when 
//Game intialize is called.
static Game* ApplicationHandle = 0;


#endif
