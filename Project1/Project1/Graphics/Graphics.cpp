////////////////////////////////////////////////////////////////////////////////
// Filename: Graphics.cpp
////////////////////////////////////////////////////////////////////////////////

//#include <iostream>
#include <sstream>   // for wostringstream

#include "Graphics.h"


Graphics::Graphics()
{

	//Set all member pointers to zero for safety
	m_D3D = 0;
	m_Camera = 0;
	m_ColorShader = 0;
}


Graphics::Graphics(const Graphics& other)
{
}


Graphics::~Graphics()
{
}

//////////////////////////////////////////////////////////////////
// To-Do: Replace error'd parameter with our own list of entities
//////////////////////////////////////////////////////////////////
bool Graphics::Initialize(int screenWidth, int screenHeight, HWND hwnd, CineCamera* camera, ArrayList<Model>* gameModels)
{
	bool result;

	m_hwnd = hwnd; //handle to the windows window

	// Create the Direct3D object.
	m_D3D = new D3D;
	if(!m_D3D)
	{
		return false;
	}


	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}




	// keep a local pointer to the camera object.
	m_Camera = camera;
	if(!m_Camera)
	{
		return false;
	}


	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 0.0f, -10.0f); 
	
	axis = new XYZaxis; //create orgin axis object to display co-ord system (mostly for debug)
	if(!axis)
	{
		return false;
	}
	axis->Initialize();
	// Create A model for the axis
	axisModel = new ModelUtil(axis->GetVertices(), 
										axis->GetVertexCount(), 
										axis->GetIndices(), 
										axis->GetIndexCount(), 
										D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	result = axisModel->Initialize(m_D3D->GetDevice());
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the axis model object.", L"Error", MB_OK);
		return false;
	}

	/////////////////////////////
	//Initializes Game Models
	/////////////////////////////
	
	
	gameWorldModels = gameModels;

	if(gameWorldModels && !gameWorldModels->isEmpty()){
		for(int i=0; i< gameWorldModels->size(); i++){
			Model* gameModel = gameWorldModels->elementAt(i);
			result = gameModel->GetVertexModel()->Initialize(m_D3D->GetDevice());
	        if(!result)
	        {
		       //MessageBox(hwnd, L"Could not initialize the game model object.", L"Error", MB_OK);
		       return false;
	        }

		}
	}
	
	

	// Create the color shader object.
	m_ColorShader = new ColorShader;
	if(!m_ColorShader)
	{
		return false;
	}

	// Initialize the color shader object.
	result = m_ColorShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the color shader object.", L"Error", MB_OK);
		return false;
	}

	return true;
}


void Graphics::Shutdown()
{
	// Release the color shader object.
	if(m_ColorShader)
	{
		m_ColorShader->Shutdown();
		delete m_ColorShader;
		m_ColorShader = 0;
	}

	// Release the D3D object.
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
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

	return;
}


bool Graphics::Frame()
{
	bool result;


	// Render the graphics scene.
	result = Render();
	if(!result)
	{
		return false;
	}

	return true;
}


bool Graphics::Render()
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
        SetWindowText( m_hwnd, captionStrm.str().c_str() ); //use FPS stats as title caption to windows window.
		

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
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f); //R,G,B,A values for background (Opaque Black)

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the view and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_Camera->GetProjectionMatrix(projectionMatrix);

	m_D3D->GetWorldMatrix(axisWorld); //set to identity matrix



	//////////////////////////////////////////////////////////////////
	// Game Model render process. Use as reference
	//////////////////////////////////////////////////////////////////
	if(gameWorldModels && !gameWorldModels->isEmpty()){
		for(int i=0; i< gameWorldModels->size(); i++){
			Model* gameModel = gameWorldModels->elementAt(i);

		   // Put the cube model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	       gameModel->GetVertexModel()->Render(m_D3D->GetDeviceContext());

	      //Render The Game Model
	       result = m_ColorShader->Render(m_D3D->GetDeviceContext(), 
		                                  gameModel->GetVertexModel()->GetIndexCount(), 
								          gameModel->GetWorldMatrix(), 
								          viewMatrix, 
								          projectionMatrix);
	
	      if(!result) {return false;}


		}
	}

    // Present the rendered scene to the screen.
	m_D3D->EndScene();


	return true;
}

