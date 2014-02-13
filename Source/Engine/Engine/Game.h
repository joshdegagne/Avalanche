////////////////////////////////////////////////////////////////////////////////
// Filename: Game.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

#define WIN32_LEAN_AND_MEAN 
#include <windows.h> //needed to create and destroy windows and call Win32 functions

#include "KeyInput.h"
#include "ControllerInputManager.h"
#include "Graphics.h"
#include "GameModel.h"
#include "QuadModel.h"
#include "QuadTexturedModel.h"
#include "Arraylist.h"
#include "Camera.h"
#include "Playfield.h"
#include "Player.h"
#define  NUMPLAYERS 4

////////////////////////////////////////////////////////////////////////////////
// Class name: Game
////////////////////////////////////////////////////////////////////////////////
class Game
{
	friend class Playfield;

	public:
		Game(); 
		Game(const Game&);
		~Game();

		bool Initialize();
		void Shutdown();
		void Run();

		LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

	private:
		//Functions
		bool  Frame();
		void  InitializeWindows(int&, int&);
		void  ShutdownWindows();
		float getElapsedTime();

		//Member Variables
		LPCWSTR   applicationName;
		HINSTANCE hinstance;
		HWND      hwnd;  //handle to the Windows window (client window for the application)

		KeyInput*               keyInput; //out input class object from which to obtain user inputs
		ControllerInputManager* conInput; //Yay! Input from a controller!
		Graphics*               graphics; //our graphics class object that encapsulates the graphics pipeline
		Camera*					camera; //our encapsulation of where the camera is looking at our world
		Player** 				players;

		float previousTime;

		//Game World Items
		Playfield*		   playfield;
		QuadTexturedModel* pF;

		ArrayList<GameModel>* gameModels; //container to hold all our game world models


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
//System intialize is called.
static Game* ApplicationHandle = 0;
