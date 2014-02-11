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
#include "arraylist.h"
#include "CineCamera.h"
#include "Playfield.h"

////////////////////////////////////////////////////////////////////////////////
// Class name: Game
////////////////////////////////////////////////////////////////////////////////
class Game
{
public:
	Game(); //default constructor
	Game(const Game&); //copy constructor
	~Game(); //destructor

	bool Initialize();
	void Shutdown();
	void Run();

	//This method is used to intercept the windows messages
	//This is how windows messages or events get into out application
	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

private:
	bool  Frame();
	void  InitializeWindows(int&, int&);
	void  ShutdownWindows();
	float getElapsedTime();

private:
	LPCWSTR   applicationName;
	HINSTANCE hinstance;
	HWND      hwnd;  //handle to the Windows window (client window for the application)

	KeyInput*               keyInput; //out input class object from which to obtain user inputs
	ControllerInputManager* conInput; //Yay! Input from a controller!
	Graphics*               graphics; //our graphics class object that encapsulates the graphics pipeline
	CineCamera*             camera; //our encapsulation of where the camera is looking at our world

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
