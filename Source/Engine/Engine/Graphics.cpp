////////////////////////////////////////////////////////////////////////////////
// Filename: Graphics.cpp
////////////////////////////////////////////////////////////////////////////////

//#include <iostream>
#include <sstream>   // for wostringstream

#include "camera.h"
#include "ColorShader.h"
#include "TextureShader.h"
#include "IViewModel.h"
#include "Graphics.h"
#include "SpriteBatch.h"
#include "SpriteFont.h"
#include "Effects.h"

#include "DebugDefinitions.h"


Graphics::Graphics()
{

	//Set all member pointers to zero for safety
	d3D = 0;
	camera = 0;

	axis = 0;
    axisModel = 0;

	colorShader = 0;
	textureShader = 0;
}


Graphics::Graphics(const Graphics& other)
{
}


Graphics::~Graphics()
{
	#ifdef ALL_DEBUG
	delete axis;
	#endif
}



bool Graphics::Initialize(int screenWidth, int screenHeight, HWND hwnd, Camera* initCamera)
{
	bool result;

	hwnd = hwnd; //handle to the windows window

	// Create the Direct3D object.
	d3D = new D3D;
	if(!d3D)
	{
		return false;
	}


	// Initialize the Direct3D object.
	result = d3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}




	// keep a local pointer to the camera object.
	camera = initCamera;
	if(!camera)
	{
		return false;
	}

	#ifdef ALL_DEBUG
	axis = new XYZaxis; //create orgin axis object to display co-ord system (mostly for debug)
	if(!axis)
	{
		return false;
	}
	axis->Initialize();


	// Set the initial position of the camera.
	//m_Camera->SetPosition(0.0f, 0.0f, -10.0f); 
	
    // Create A model for the axis
	axisModel = new Model(axis->GetVertices(), 
										axis->GetVertexCount(), 
										axis->GetIndices(), 
										axis->GetIndexCount(), 
										D3D11_PRIMITIVE_TOPOLOGY_LINELIST);


	result = axisModel->Initialize(d3D->GetDevice());
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the axis model object.", L"Error", MB_OK);
		return false;
	}
	#endif

	// Create the color shader object.
	colorShader = new ColorShader;
	if(!colorShader)
		return false;

	// Initialize the color shader object.
	result = colorShader->Initialize(d3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the color shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the texture shader object.
	textureShader = new TextureShader;
	if(!textureShader)
	{
		return false;
	}

	// Initialize the texture shader object.
	result = textureShader->Initialize(d3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
		return false;
	}

	spriteBatch = new SpriteBatch(getContext());
	spriteFontBig.reset(new SpriteFont(getDevice(), L"tempesta7_title.spritefont"));
	spriteFontNormal.reset(new SpriteFont(getDevice(), L"tempesta7_menu.spritefont"));

	if (!spriteBatch || !spriteFontBig || !spriteFontNormal) return false;

	return true;
}


void Graphics::Shutdown()
{
	// Release the color shader object.
	if(colorShader)
	{
		colorShader->Shutdown();
		delete colorShader;
		colorShader = 0;
	}

	// Release the texture shader object.
	if(textureShader)
	{
		textureShader->Shutdown();
		delete textureShader;
		textureShader = 0;
	}

	// Release the axis object.
	if(axis)
	{
		axis->Shutdown();
		delete axis;
		axis = 0;
	}

	if(axisModel){
	    axisModel->Shutdown();
		delete axisModel;
		axisModel = 0;

	}


	// Release the D3D object.
	if(d3D)
	{
		d3D->Shutdown();
		delete d3D;
		d3D = 0;
	}

	if (spriteBatch)
	{
		delete spriteBatch;
		spriteBatch = 0;
	}

	if (spriteFontBig)
	{
		spriteFontBig.release();
		spriteBatch = 0;
	}

	if (spriteFontNormal)
	{
		spriteFontNormal.release();
		spriteBatch = 0;
	}

	return;
}


bool Graphics::Render(ArrayList<IViewModel>* viewModels)
{
	// Update our time	
	static float t = 0.0f;
	static float previous_t = 0.0f;
	static int sampleCount = 0;
	static float sampleStartTime = 0.0f;
	 //std::wostringstream temp;

    static DWORD dwTimeStart = 0;

    DWORD dwTimeCur = GetTickCount();
    if( dwTimeStart == 0 ) dwTimeStart = dwTimeCur;
	previous_t = t;
	t = ( dwTimeCur - dwTimeStart ) / 1000.0f; //elapsed time in seconds
	if(t -sampleStartTime > 1.0){
		//produce FPS stats every second
		sampleCount++;
		float averageFramePeriod = (t-sampleStartTime)/sampleCount;
		sampleCount = 0;
		sampleStartTime = t;


		//Write Framestats on Window title caption
		std::wostringstream captionStrm;
		captionStrm << L"FPS: " << (int)(1.0f/averageFramePeriod) << L" ";
        SetWindowText( hwnd, captionStrm.str().c_str() ); //use FPS stats as title caption to windows window.

	}
	else{
		sampleCount++;
	}



	// Matrices
	XMFLOAT4X4 axisWorld;
	XMFLOAT4X4 viewMatrix, projectionMatrix;

	// Initialize matrices to Identity matrices
	
	bool result;

	// Clear the buffers to begin the scene.
	//d3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f); //R,G,B,A values for background (Opaque Black)
	d3D->BeginScene(100.0f, 30.0f, 100.0f, 0.5f); //R,G,B,A values for background 
	//d3D->BeginScene(216.0f, 191.0f, 216.0f, 1.0f); //R,G,B,A values for background (Purple?)

	// Generate the view matrix based on the camera's position.
	camera->Render();

	// Get the view and projection matrices from the camera and d3d objects.
	camera->GetViewMatrix(viewMatrix);
	camera->GetProjectionMatrix(projectionMatrix);

	d3D->GetWorldMatrix(axisWorld); //set to identity matrix


	if(viewModels && !viewModels->isEmpty())

		for(int i=0; i< viewModels->size(); i++){
			IViewModel* viewModel = viewModels->elementAt(i);

		   // Provide the game models with a graphics device context,
		   // view and projection matrices, and
		   // shaders and ask them to render themselves

		  result = viewModel->Render(d3D->GetContext(), 
								          viewMatrix, 
								          projectionMatrix,
										  colorShader,
										  textureShader); 
	
	       if(!result) {return false;}
 

	}
 

	// Set up the model for axis scale
	#ifdef ALL_DEBUG
	axisModel->Render(d3D->GetContext());
	result = colorShader->Render(d3D->GetContext(), axisModel->GetIndexCount(), axisWorld, viewMatrix, projectionMatrix);
	
	if(!result)
	{
		return false;
	}
	#endif ALL_DEBUG


    // Present the rendered scene to the screen.
	d3D->EndScene();


	return true;
}

