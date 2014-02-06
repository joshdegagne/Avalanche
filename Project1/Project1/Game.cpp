#include "Game.h"

Game::Game()
{
	//set pointers to our objects to null so if initialization of them
	//fails they will not mistakenly be used to clean up memory

	//m_Input = 0;  need to change this input to contollers
	graphics = 0;
	camera = 0;
	gameModels = new ArrayList<Model>();
}


Game::Game(const Game& other)
{
	//always implmement your own copy constructor even if it does nothing
}


Game::~Game()
{
	//Always implement your own destructor even if it does nothing.
	//If your class will ever have subclasses (through inheritance) then make the 
	//destructor virtual as in
	// virtual Game::~Game(){...}
	// otherwise you will likely have memory leaks
}
bool Game::Initialize()
{
	int screenWidth, screenHeight;
	bool result;


	// Initialize the width and height of the screen to zero before sending the variables into 
	// InitializeWindows() function which will cause them to get set.
	// They are passed in by reference so can be set from within the InitializeWindows() function

	screenWidth = 0;
	screenHeight = 0;

	// Initialize the windows api.
	// Create the actual window. This screenWidth and screenHeight variables will get set
	InitializeWindows(screenWidth, screenHeight);

	/*
	// Create the input object.  This object will be used to handle reading the keyboard input from the user.
	m_Input = new InputClass;
	if(!m_Input)
	{
		return false;
	}
		// Initialize the input object.
	m_Input->Initialize();
	*/

	// Create the Camera object.
	camera = new CineCamera(screenWidth,screenHeight);
	if(!camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	camera->SetPosition(0.0f, 0.0f, 20.0f); //10 units along Z in front of origin
	camera->SetDirection(0.0f, 0.0f, -1.0f); //look in positive Z direction
	camera->SetUpDirection(0.0f, 1.0f, 0.0f); //up points in positive Y direction
	/*IMPORTANT:  note camera direction and up must be orthogonal */



	
	//Create the game objects for our game
	XMFLOAT4 playFieldColor = XMFLOAT4(255.0f/255,255.0f/255,255.0f/255,1.0f);
	playField = new QuadModel(10.0f,10.0f,&playFieldColor);
	playField->orientRotateY(XM_PI);

	//Add the  gameModel objects to the GameModels collection
	//that will be rendered by the graphics system

	gameModels->add(playField);

	// Create the graphics object.  This object will handle rendering all the graphics for this application.
	graphics = new Graphics;
	if(!graphics)
	{
		return false;
	}

	// Initialize the graphics object. 	Engine.exe!WinMain(HINSTANCE__ * hInstance, HINSTANCE__ * hPrevInstance, char * pScmdline, int iCmdshow) Line 21	C++
	// The Graphics::Initialize will also call back into our game objects an initialize their ModelClass objects once the GraphicsClass has had
	// a chance to initialize

	result = graphics->Initialize(screenWidth, screenHeight, hwnd, camera, gameModels);
	if(!result)
	{
		return false;
	}
	
	return true;


}


void Game::Shutdown()
{
	//Shut down our game objects and release their memory

	if(playField)
	{
		delete playField;
		playField = 0;
	}

	//release the memory for the m_GameModels collection
	//all objects in it should have been released my the code immediately above
	if(gameModels)
	{
		delete gameModels;
		gameModels = 0;
	}

	//Shut down the graphics pipeline object and release its memory
	// Release the graphics object.
	if(graphics)
	{
		graphics->Shutdown();
		delete graphics;
		graphics = 0;
	}

	/*
	// Release the input object's memory.
	if(m_Input)
	{
		delete m_Input;
		m_Input = 0;
	}
	*/

    // Release the camera object's memory.
	if(camera)
	{
		delete camera;
		camera = 0;
	}



	// Shutdown the actual Window's window.
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
	So far it is fairly simple, we check the input object to see if the user has pressed escape and wants to quit. 
	If they don't want to quit then we call the graphics object to do its frame processing 
	which will render the graphics for that frame. 
	As the application grows we'll place more code here. 
	*/
	
	/*
	Apply transformations to the game objects
	*/

	//Handle user inputs
	bool result;

	const int ascii_A = 65;
	const int ascii_B = 66;
	const int ascii_C = 67;
	const int ascii_D = 68;
	const int ascii_E = 69;
	const int ascii_P = 80;
	const int ascii_R = 82;
	const int ascii_W = 87;
	const int ascii_X = 88;
	const int ascii_Y = 89;
	const int ascii_Z = 90;

	/*
	// Check if the user pressed escape and wants to exit the application.
	if(m_Input->IsKeyDown(VK_ESCAPE))
	{
		return false;
	}

	
	//Move camera or models based on input
	

	
	We will combinations for a key + arrow keys to control the camera
	
	if ( m_Input->IsKeyDown(VK_SHIFT) ){

	   if ( m_Input->IsKeyDown(VK_LEFT) ) //Move Camera Left
	      m_Camera->StrafeLeft();

	   if ( m_Input->IsKeyDown(VK_RIGHT) ) //Move Camera Right
	      m_Camera->StrafeRight();

	   if ( m_Input->IsKeyDown(VK_UP) ) //Camera Move Forward
		  m_Camera->MoveForward();

	   if ( m_Input->IsKeyDown(VK_DOWN) ) //Camera Pull Back
		  m_Camera->MoveBackward();

	
	}
	else if ( m_Input->IsKeyDown(VK_CONTROL) ){

	   if ( m_Input->IsKeyDown(VK_LEFT) ) //Pan Camera Left
	      m_Camera->PanLeft();

	   if ( m_Input->IsKeyDown(VK_RIGHT) ) //Pan Camera Right
	      m_Camera->PanRight();

	   if ( m_Input->IsKeyDown(VK_UP) ) //Tilt Camera Downward
		  m_Camera->TiltDown();

	   if ( m_Input->IsKeyDown(VK_DOWN) ) //Tilt Camera Upward
		  m_Camera->TiltUp();

	
	}
	else if ( m_Input->IsKeyDown(ascii_C) ){


	   if ( m_Input->IsKeyDown(VK_UP) ) //Crane Up
		  m_Camera->CraneUp();

	   if ( m_Input->IsKeyDown(VK_DOWN) ) //Crane Down
		  m_Camera->CraneDown();

	
	}
	else if ( m_Input->IsKeyDown(ascii_R) ){


	   if ( m_Input->IsKeyDown(VK_LEFT) ) //Roll Left
		  m_Camera->RollLeft();

	   if ( m_Input->IsKeyDown(VK_RIGHT) ) //Roll Right
		  m_Camera->RollRight();	
	}

		else if ( m_Input->IsKeyDown(ascii_Z) ){


	   if ( m_Input->IsKeyDown(VK_UP) ) //Zoom In
		  m_Camera->ZoomIn();

	   if ( m_Input->IsKeyDown(VK_DOWN) ) //Zoom Out
		  m_Camera->ZoomOut();

	
	}

    //MOVE GAME OBJECTS

	else if ( m_Input->IsKeyDown(ascii_B) ){
	   
		//Rotate m_backDrop background object about Y or X axis
	   //Just Arrow Keys
	   if ( m_Input->IsKeyDown(VK_LEFT))
		   m_backDrop->orientRotateY(XM_PIDIV2/70);

	   if ( m_Input->IsKeyDown(VK_RIGHT))
		   m_backDrop->orientRotateY(-XM_PIDIV2/70);

	   if ( m_Input->IsKeyDown(VK_UP))
		   m_backDrop->orientRotateX(XM_PIDIV2/70);

	   if ( m_Input->IsKeyDown(VK_DOWN))
		   m_backDrop->orientRotateX(-XM_PIDIV2/70);
	
	}

   else if ( m_Input->IsKeyDown(ascii_E) ){
	   
		//Move m_Enemy prism object
	   if ( m_Input->IsKeyDown(VK_LEFT))
		   m_Enemy->MoveLeft();

	   if ( m_Input->IsKeyDown(VK_RIGHT))
		   m_Enemy->MoveRight();

	   if ( m_Input->IsKeyDown(VK_UP))
		   m_Enemy->MoveUp();

	   if ( m_Input->IsKeyDown(VK_DOWN))
		   m_Enemy->MoveDown();
	
	}
      else {
	   
		//Just the arrow keys alone

	   if ( m_Input->IsKeyDown(VK_LEFT))
		   m_AirPlane->TurnLeft();

	   if ( m_Input->IsKeyDown(VK_RIGHT))
		   m_AirPlane->TurnRight();

	   if ( m_Input->IsKeyDown(VK_UP))
		   m_AirPlane->MoveForward();

	   if ( m_Input->IsKeyDown(VK_DOWN))
		   m_Player->MoveDown();
	
	}
	*/


	// Do the frame processing for the graphics object.
	result = graphics->Frame();
	if(!result)
	{
		return false;
	}

	return true;
}


LRESULT CALLBACK Game::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	/*
	The MessageHandler function is where windows system messages are directed into our application
	Here we can listen for certain information that we are interested in. 
	Currently we will just read if a key is pressed or if a key is released and pass that information on to the input object. 
	All other information we will pass back to the windows default message handler. 
	*/
	switch(umsg)
	{
		// Check if a key has been pressed on the keyboard.
		case WM_KEYDOWN:
		{
			// If a key is pressed send it to the input object so it can record that state.
			// The input object will be polled by our game logic

			//m_Input->KeyDown((unsigned int)wparam);                                                         INPUT HEY LOOK OVER HERE!
			return 0;
		}

		// Check if a key has been released on the keyboard.
		case WM_KEYUP:
		{
			// If a key is released then send it to the input object so it can unset the state for that key.
			//m_Input->KeyUp((unsigned int)wparam);                                                           INPUT HEY LOOK OVER HERE!
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