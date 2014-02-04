#include "Game.h"

static bool use_debug_console = false; //set to true to get the "side car" console window for writing debug info to

static void writeToDebugConsole(const wchar_t* theString){
	if(use_debug_console)
		WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), theString, wcslen(theString), NULL, NULL);
}

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

	Game* mainGame; //system class encapsulates our overall app
	bool result; //Checks for failed set-up returns

	//Debug Console setup (using global variable)
	if(use_debug_console) AllocConsole();
	writeToDebugConsole(L"Hello World\n");
	
	// Create the system object.
	mainGame = new Game;
	if(!mainGame)
	{
		return 0; //our system object did not construct properly
	}


	// Initialize our system object, which returns true if the initialization completed successfully
	//result = mainGame->Initialize(); 

	if(result)
	{
		//mainGame->Run();
	}

	// Shutdown and release the system object.
	//mainGame->Shutdown(); //give system a chance to clean up
	delete mainGame;  //release the system object's memory
	mainGame = 0;     //set system pointer to 0 so it is no longer valid

	return 0;
	
	
}