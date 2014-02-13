////////////////////////////////////////////////////////////////////////////////
// Filename: Game.cpp
////////////////////////////////////////////////////////////////////////////////
#include <sstream>
#include <vector>
#include "Game.h"

Game::Game()
{
	keyInput  = 0; 
	conInput  = 0;
	graphics  = 0;
	camera    = 0;
	players	  = 0;
	playfield = 0;
	pF		  = 0;

	gameModels = new ArrayList<GameModel>();
}


Game::Game(const Game& other)
{
}


Game::~Game()
{
}

ControllerInputManager* Game::getControllerManager() { return conInput; }


bool Game::Initialize()
{

	/////////////////
	//Window/Screen//
	/////////////////
	int screenWidth, screenHeight;
	screenWidth = 0;
	screenHeight = 0;
	InitializeWindows(screenWidth, screenHeight);


	/////////////////
	//Input Devices//
	/////////////////
	keyInput = new KeyInput;
	if(!keyInput)
		return false;

	conInput = new ControllerInputManager;
	if(!conInput)
		return false;


	//////////
	//Camera//
	//////////
	camera = new Camera(screenWidth,screenHeight);
	if(!camera)
		return false;
	/*
	camera->SetPosition(26.4438f, 11.6168f, 5.04668f); //10 units along Z in front of origin
	camera->SetDirection(-1.0f, 0.0f, -1.0f); //look in positive Z direction
	camera->SetUpDirection(0.0f, -1.f, 0.0f); //up points in positive Y direction
	for(int i=0; i < 100; ++i) camera->TiltUp();
	for(int i=0; i < 125; ++i) camera->RollLeft();
	for(int i=0; i < 10; ++i) camera->TiltUp();
	for(int i=0; i < 15; ++i) camera->PanLeft();
	for(int i=0; i < 10; ++i) camera->RollLeft();
	for(int i=0; i < 10; ++i) camera->PanLeft();
	for(int i=0; i < 10; ++i) camera->RollLeft();
	IMPORTANT:  note camera direction and up must be orthogonal 
	*/
	camera->SetPosition(24.0f, 5.0f, 15.0f);
	camera->SetTarget(9.0f, 3.0f, 0.0f);
	camera->SetUpDirection(0.0f, 0.0f, 1.0f);


	/////////////////////
	//Players/Playfield//
	/////////////////////
	players = new Player*[NUMPLAYERS];
    Player** activePlayers = new Player*[NUMPLAYERS];
	int activeCounter = 0;
	for (int i = 0; i < NUMPLAYERS; i++)
	{
		players[i] = new Player(*this, i);
		if (conInput->isConnected(i))
			activePlayers[activeCounter++] = players[i];
	}

	playfield = new Playfield(activePlayers, activeCounter);
	if (!playfield)
		return false;


	///////////////
	//Game Models//
	///////////////
	WCHAR* fieldTexture = L"textures/graph_paper.dds";
	pF = new QuadTexturedModel (18.0f,6.0f,fieldTexture);
	pF->worldTranslate(9.0f,3.0f,-0.1f);

	gameModels->add(pF);


	////////////
	//Graphics//
	////////////
	graphics = new Graphics;
	if(!graphics)
	{
		return false;
	}

	bool result = graphics->Initialize(screenWidth, screenHeight, hwnd, camera, gameModels);
	if(!result)
	{
		return false;
	}
	
	return true;
}


void Game::Shutdown()
{
	if(pF)
	{
		pF->Shutdown();
		delete pF;
		pF = 0;
	}

	if(gameModels)
	{
		delete gameModels;
		gameModels = 0;
	}

	if(graphics)
	{
		graphics->Shutdown();
		delete graphics;
		graphics = 0;
	}

	if(keyInput)
	{
		delete keyInput;
		keyInput = 0;
	}

	if(conInput)
	{
		delete conInput;
		conInput = 0;
	}

	if(camera)
	{
		delete camera;
		camera = 0;
	}

	ShutdownWindows();
	
	return;
}


void Game::Run()
{
	/*
	The Run function is where our application will loop and do all the application processing until we decide to quit. 
	The application processing is done in the Frame() function which is called each loop. 
	This is an important concept to understand as now the rest of our application must be written with this in mind. 
	The pseudo code looks like the following: 

	while not done {
        check for windows system messages
        process system messages
        process application loop
        check if user wanted to quit during the frame processing
		}


	*/
	MSG msg;
	bool done, result;


	// Initialize the message structure.
	ZeroMemory(&msg, sizeof(MSG));
	
	// Loop until there is a quit message from the window or the user.
	done = false;
	while(!done)
	{
		// Handle the windows messages.
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// If windows signals to end the application then exit out.
		if(msg.message == WM_QUIT)
		{
			done = true;
		}
		else
		{
			// Otherwise do the frame processing.
			result = Frame();
			if(!result)
			{
				done = true;
			}
		}

	}

	return;
}


bool Game::Frame()
{
	/*
	The following Frame function is where all the processing for our application is done. 
	So far it is fairly simple, we check the keyInput object to see if the user has pressed escape and wants to quit. 
	If they don't want to quit then we call the graphics object to do its frame processing 
	which will render the graphics for that frame. 
	As the application grows we'll place more code here. 
	*/
	
	/*
	Apply transformations to the game objects
	*/

	//Rotate the object a bit around some axis

	//Handle user inputs
	bool result;

	const int ascii_A = 65;
	const int ascii_B = 66;
	const int ascii_C = 67;
	const int ascii_D = 68;
	const int ascii_E = 69;
	const int ascii_J = 74;
	const int ascii_P = 80;
	const int ascii_R = 82;
	const int ascii_U = 85;
	const int ascii_V = 86;
	const int ascii_W = 87;
	const int ascii_X = 88;
	const int ascii_Y = 89;
	const int ascii_Z = 90;


	// Check if the user pressed escape and wants to exit the application.
	if(keyInput->IsKeyDown(VK_ESCAPE))
	{
		return false;
	}
	// Check if the user pressed the back button and wants to exit the application.
	if (conInput->getButtonBack(0))
	{
		return false;
	}

	/*
	//Move camera or models based on input
	//We will combinations for a key + arrow keys to control the camera
	if ( keyInput->IsKeyDown(VK_SHIFT) ){

	   if ( keyInput->IsKeyDown(VK_LEFT) ) //Move camera Left
	      camera->StrafeLeft();

	   if ( keyInput->IsKeyDown(VK_RIGHT) ) //Move camera Right
	      camera->StrafeRight();

	   if ( keyInput->IsKeyDown(VK_UP) ) //camera Move Forward
		  camera->MoveForward();

	   if ( keyInput->IsKeyDown(VK_DOWN) ) //camera Pull Back
		  camera->MoveBackward();

	
	}
	else if ( keyInput->IsKeyDown(VK_CONTROL) ){

	   if ( keyInput->IsKeyDown(VK_LEFT) ) //Pan camera Left
	      camera->PanLeft();

	   if ( keyInput->IsKeyDown(VK_RIGHT) ) //Pan camera Right
	      camera->PanRight();

	   if ( keyInput->IsKeyDown(VK_UP) ) //Tilt camera Downward
		  camera->TiltDown();

	   if ( keyInput->IsKeyDown(VK_DOWN) ) //Tilt camera Upward
		  camera->TiltUp();

	
	}
	else if ( keyInput->IsKeyDown(ascii_C) ){


	   if ( keyInput->IsKeyDown(VK_UP) ) //Crane Up
		  camera->CraneUp();

	   if ( keyInput->IsKeyDown(VK_DOWN) ) //Crane Down
		  camera->CraneDown();

	
	}
	else if ( keyInput->IsKeyDown(ascii_R) ){


	   if ( keyInput->IsKeyDown(VK_LEFT) ) //Roll Left
		  camera->RollLeft();

	   if ( keyInput->IsKeyDown(VK_RIGHT) ) //Roll Right
		  camera->RollRight();	
	}

		else if ( keyInput->IsKeyDown(ascii_Z) ){


	   if ( keyInput->IsKeyDown(VK_UP) ) //Zoom In
		  camera->ZoomIn();

	   if ( keyInput->IsKeyDown(VK_DOWN) ) //Zoom Out
		  camera->ZoomOut();

	
	}
	else if ( keyInput->IsKeyDown(ascii_P) ){
		
		//print camera position
		//I'm sorry.

		///////////////////////////////////////////////////////////////////////////
		//DEBUGCONSOLE HEADERFILE HAS MADE THIS OUT OF DATE. PLEASE FIX OR REMOVE//
		///////////////////////////////////////////////////////////////////////////
		
		You need:
		std::wostringstream oss;
		std::wstring ws;
		const wchar_t* cwp;
		int i = whatever;

		oss<<i;
		ws = oss.str();
		cwp = ws.c_str(); // const wchar_t*
		std::vector<wchar_t> buf( cwp , cwp + (ws.size() + 1) );
		wchar_t* result = &buf[0];  // wchar_t*
		std::wstring ourString(result);
		WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), ourString.c_str(), wcslen(ourString.c_str()), NULL, NULL);

		std::wostringstream osspx;
		std::wostringstream osspy;
		std::wostringstream osspz;
		std::wostringstream ossdx;
		std::wostringstream ossdy;
		std::wostringstream ossdz;
		std::wostringstream ossux;
		std::wostringstream ossuy;
		std::wostringstream ossuz;
		std::wstring wspx;
		std::wstring wspy;
		std::wstring wspz;
		std::wstring wsdx;
		std::wstring wsdy;
		std::wstring wsdz;
		std::wstring wsux;
		std::wstring wsuy;
		std::wstring wsuz;
		const wchar_t* cwppx;
		const wchar_t* cwppy;
		const wchar_t* cwppz;
		const wchar_t* cwpdx;
		const wchar_t* cwpdy;
		const wchar_t* cwpdz;
		const wchar_t* cwpux;
		const wchar_t* cwpuy;
		const wchar_t* cwpuz;

		float px = camera->GetPosition().x;
		float py = camera->GetPosition().y;
		float pz = camera->GetPosition().z;
		float dx = camera->GetDirection().x;
		float dy = camera->GetDirection().y;
		float dz = camera->GetDirection().z;
		float ux = camera->GetUpDirection().x;
		float uy = camera->GetUpDirection().y;
		float uz = camera->GetUpDirection().z;

		osspx<<px;
		wspx = osspx.str();
		cwppx = wspx.c_str(); // const wchar_t*
		std::vector<wchar_t> bufpx( cwppx , cwppx + (wspx.size() + 1) );
		wchar_t* posx = &bufpx[0];  // wchar_t*
		std::wstring posString(posx);
		posString += std::wstring(L" ");
		osspy<<py;
		wspy = osspy.str();
		cwppy = wspy.c_str(); // const wchar_t*
		std::vector<wchar_t> bufpy( cwppy , cwppy + (wspy.size() + 1) );
		wchar_t* posy = &bufpy[0];  // wchar_t*
		posString += std::wstring(posy);
		posString += std::wstring(L" ");
		osspz<<pz;
		wspz = osspz.str();
		cwppz = wspz.c_str(); // const wchar_t*
		std::vector<wchar_t> bufpz( cwppz , cwppz + (wspz.size() + 1) );
		wchar_t* posz = &bufpz[0];  // wchar_t*
		posString += std::wstring(posz);
		posString += std::wstring(L"\n");
		WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), posString.c_str(), wcslen(posString.c_str()), NULL, NULL);

		ossdx<<dx;
		wsdx = ossdx.str();
		cwpdx = wsdx.c_str(); // const wchar_t*
		std::vector<wchar_t> bufdx( cwpdx , cwpdx + (wsdx.size() + 1) );
		wchar_t* dirx = &bufdx[0];  // wchar_t*
		std::wstring dirString(dirx);
		dirString += std::wstring(L" ");
		ossdy<<dy;
		wsdy = ossdy.str();
		cwpdy = wsdy.c_str(); // const wchar_t*
		std::vector<wchar_t> bufdy( cwpdy , cwpdy + (wsdy.size() + 1) );
		wchar_t* diry = &bufdy[0];  // wchar_t*
		dirString += std::wstring(diry);
		dirString += std::wstring(L" ");
		ossdz<<dz;
		wsdz = ossdz.str();
		cwpdz = wsdz.c_str(); // const wchar_t*
		std::vector<wchar_t> bufdz( cwpdz , cwpdz + (wsdz.size() + 1) );
		wchar_t* dirz = &bufdz[0];  // wchar_t*
		dirString += std::wstring(dirz);
		dirString += std::wstring(L"\n");
		WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), dirString.c_str(), wcslen(dirString.c_str()), NULL, NULL);

		ossux<<ux;
		wsux = ossux.str();
		cwpux = wsux.c_str(); // const wchar_t*
		std::vector<wchar_t> bufux( cwpux , cwpux + (wsux.size() + 1) );
		wchar_t* upx = &bufux[0];  // wchar_t*
		std::wstring upString(dirx);
		upString += std::wstring(L" ");
		ossuy<<uy;
		wsuy = ossuy.str();
		cwpuy = wsuy.c_str(); // const wchar_t*
		std::vector<wchar_t> bufuy( cwpuy , cwpuy + (wsuy.size() + 1) );
		wchar_t* upy = &bufuy[0];  // wchar_t*
		upString += std::wstring(upy);
		upString += std::wstring(L" ");
		ossuz<<uz;
		wsuz = ossuz.str();
		cwpuz = wsuz.c_str(); // const wchar_t*
		std::vector<wchar_t> bufuz( cwpuz , cwpuz + (wsuz.size() + 1) );
		wchar_t* upz = &bufuz[0];  // wchar_t*
		upString += std::wstring(upz);
		upString += std::wstring(L"\n");
		WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), upString.c_str(), wcslen(upString.c_str()), NULL, NULL);
		
	}
	*/
	
    float elapsedTime = getElapsedTime();



	// Do the frame processing for the graphics object.
	result = graphics->Frame();
	if(!result)
	{
		return false;
	}

	return true;
}

float Game::getElapsedTime()
{
	
	float currentTime = (float) GetTickCount();
	float elapsedTime = currentTime - previousTime;
	previousTime = currentTime;
	return elapsedTime;
}

LRESULT CALLBACK Game::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	/*
	The MessageHandler function is where windows system messages are directed into our application
	Here we can listen for certain information that we are interested in. 
	Currently we will just read if a key is pressed or if a key is released and pass that information on to the keyInput object. 
	All other information we will pass back to the windows default message handler. 
	*/
	switch(umsg)
	{
		// Check if a key has been pressed on the keyboard.
		case WM_KEYDOWN:
		{
			// If a key is pressed send it to the keyInput object so it can record that state.
			// The keyInput object will be polled by our game logic

			keyInput->KeyDown((unsigned int)wparam);
			return 0;
		}

		// Check if a key has been released on the keyboard.
		case WM_KEYUP:
		{
			// If a key is released then send it to the keyInput object so it can unset the state for that key.
			keyInput->KeyUp((unsigned int)wparam);
			return 0;
		}

		// Any other messages send to the default message handler as our application won't make use of them.
		default:
		{
			return DefWindowProc(hwnd, umsg, wparam, lparam);
		}
	}
}


void Game::InitializeWindows(int& screenWidth, int& screenHeight)
{
	/*
	The InitializeWindows will build the actual Windows window we will render to. 
	It sets (returns)  screenWidth and screenHeight back to the calling function
	so these values can be used throughout the application. 
	
	We create the window using some default settings to initialize a plain black window with no borders. 
	The function will make either a small window or make a full screen window depending on 
	the true or false setting of the global variable called FULL_SCREEN. 
	If this is set to true then we make the screen cover the entire users desktop window. 
	If it is set to false we just make a 800x600 window in the middle of the screen. 
	The FULL_SCREEN global variable at the top of the graphicsclass.h file in case you want to modify it. 
	
	It will make sense later why it is placed in that file instead of the header for this file.
	*/
	WNDCLASSEX wc; //struct which describes the window class (properties of the window)

	DEVMODE dmScreenSettings;
	int posX, posY;


	// Set an external static pointer to this object.	
	ApplicationHandle = this;

	// Get the instance of this application.
	hinstance = GetModuleHandle(NULL);

	// Give the application a name.
	applicationName = L"Engine"; //Long-character, or wchar, string

	// Setup the windows class with default settings.
	wc.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC; //http://msdn.microsoft.com/en-us/library/windows/desktop/ff729176(v=vs.85).aspx
	wc.lpfnWndProc   = WndProc; //our procedure to call back on window events
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = hinstance; //set window's application to this application
	wc.hIcon		 = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm       = wc.hIcon;
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW); //use standard arrow cursor for window (when shown)
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH); //brush for painting background colour
	wc.lpszMenuName  = NULL; //we have no menus with our window
	wc.lpszClassName = applicationName; //name of our application
	wc.cbSize        = sizeof(WNDCLASSEX);  //size of this structure in bytes
	
	// Register the window class.
	// The window class must be registered with Window's OS before the window
	// can actually be created.
	RegisterClassEx(&wc);

	// Determine the resolution of the clients desktop screen.
	screenWidth  = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);

	// Setup the screen settings depending on whether it is running in full screen or in windowed mode.
	if(FULL_SCREEN)
	{
		// If full screen set the screen to maximum size of the users desktop and 32bit.
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize       = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth  = (unsigned long)screenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;			
		dmScreenSettings.dmFields     = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Change the display settings to full screen.
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		// Set the position of the window to the top left corner.
		posX = posY = 0;
	}
	else
	{
		// If windowed then set it to 800x600 resolution.
		screenWidth  = 800;
		screenHeight = 600;

		// Place the window in the middle of the screen.
		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth)  / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
	}

	// Create the window with the screen settings and get the handle to it.
	//http://msdn.microsoft.com/en-us/library/windows/desktop/ms632679(v=vs.85).aspx

	hwnd = CreateWindowEx(WS_EX_APPWINDOW, 
		                    applicationName, 
							applicationName, 
						    WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP | WS_CAPTION, //WS_CAPTION for border with title
						    posX,  //screen X of window's top left corner
							posY, //creen Y of windowns's top left corner
							screenWidth,  //width of screen
							screenHeight, //height of screen
							NULL, 
							NULL, 
							hinstance, //the application instance
							NULL);

	// Bring the window up on the screen and set it as main focus.
	ShowWindow(hwnd, SW_SHOW); //show  the window
	SetForegroundWindow(hwnd); //make window the foreground window
	SetFocus(hwnd);            //give window input focus

	// Hide the mouse cursor if you don't want it over your game window.
	//ShowCursor(false);

	return;
}


void Game::ShutdownWindows()
{
	// Show the mouse cursor again.
	ShowCursor(true);

	// Fix the display settings if leaving full screen mode.
	if(FULL_SCREEN)
	{
		ChangeDisplaySettings(NULL, 0);
	}

	// Remove the window.
	DestroyWindow(hwnd);
	hwnd = NULL;

	// Remove the application instance.
	UnregisterClass(applicationName, hinstance);
	hinstance = NULL;

	// Release the pointer to this class.
	ApplicationHandle = NULL;

	return;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch(umessage)
	{
		// Check if the window is being destroyed.
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}

		// Check if the window is being closed.
		case WM_CLOSE:
		{
			PostQuitMessage(0);		
			return 0;
		}

		// All other messages pass to the message handler in the system class.
		default:
		{
			return ApplicationHandle->MessageHandler(hwnd, umessage, wparam, lparam);
		}
	}
}