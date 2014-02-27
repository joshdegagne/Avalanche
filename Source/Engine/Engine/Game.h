////////////////////////////////////////////////////////////////////////////////
// Filename: Game.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

#define WIN32_LEAN_AND_MEAN 
#include <windows.h> //needed to create and destroy windows and call Win32 functions

#include "KeyInput.h"
#include "ControllerInputManager.h"
#include "Graphics.h"
#include "IViewModel.h"
#include "QuadModel.h"
#include "QuadTexturedModel.h"
#include "Arraylist.h"
#include "Camera.h"
#include "Playfield.h"
#include "Player.h"
#include "LogModel.h"
#include "BoundingBox.h"
#define  NUMPLAYERS 4 //USED FOR POTENTIAL PLAYER LOOPS ONLY

class Player; //Forward declaration

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

		KeyInput*               getKeyInput();
		ControllerInputManager* getControllerManager();

		ArrayList<Player>* GetPlayers();
		ArrayList<IViewModel>* GetViewModels();
		

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

		ArrayList<Player>* players;
		KeyInput*               keyInput; //keyboard input object from which to obtain user inputs
		ArrayList<KeyInput>*    playerKeys;
		ControllerInputManager* conInput; //Yay! Input from a controller!
		Graphics*               graphics; //our graphics object that encapsulates the graphics pipeline
		Camera*					camera; //our encapsulation of where the camera is looking at our world

		float previousTime;

		//Game World Items
		Playfield*		   playfield;
		QuadTexturedModel* pF;

		ArrayList<IViewModel>* gameModels; //container to hold all our game world models - change to be in modelmanager class?


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
