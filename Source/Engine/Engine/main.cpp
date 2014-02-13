////////////////////////////////////////////////////////////////////////////////
// Filename: main.cpp
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include "Game.h"
#include "DebugConsole.h"


/*
The following demonstration code contains a lot of comments on what the various parts do
It is intended as an introductory overview of both a windows application and
DirectX pipeline is set up and used to render an object made up of
vertex triangles.

The game-loop architecture is that introduced in the Rastertek tutorials.
The demo code provides keyboard input to control a game object and
also the camera position. See the systemclass.frame() method to see which
inputs are responded to and how. When the shift key is down inputs will
control the camera position, otherwise a game character is being controlled.


The sources of the comments are:
1) Rastertek tutorial 2: Creating a Framework and Window
2) Beginning DirectX 11 Game Programming book
3) Our own observations

*/
/*WinMain is the entry point. Like main() on a simple C++ or java console application
*/


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	/*
     HINSTANCE hInstance  : handle of the applications current instance
	 HINSTANCE hPrevInstance : handle of the applications previous instance (should be NULL according to MSDN) 
	 PSTR pScmdline : commandline arguments invoked with main (we won't use this)
	 int iCmdshow : An ID that specifies how the window should be shown

	 There is also a wWinMain(...) version with the same arguments that passes unicode characters for
	 the pScmdline argument rather than ANSI as WinMain does
	*/

	Game* game; //system class encapsulates our overall app
	bool result;

	/*
	Allocate a "side car" console so we can write some debug information out to it
	*/
	AllocConsole();
	writeTextToConsole(L"Hello World\n");
	
	// Create the system object.
	game = new Game;
	if(!game)
	{
		return 0; //our system object did not construct properly
	}


	// Initialize our system object and run the application by asking 
	// the system object to run.
	result = game->Initialize(); 
	if(result)
	{
		game->Run();
	}

	// Shutdown and release the system object.
	game->Shutdown(); //give system a chance to clean up
	delete game;  //release the system object's memory
	game = 0;     //set system pointer to 0 so it is no longer valid

	return 0;
}