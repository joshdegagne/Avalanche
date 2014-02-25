////////////////////////////////////////////////////////////////////////////////
// Filename: Graphics.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "D3D.h"
#include "Model.h"
#include "arraylist.h"
#include "gamemodel.h"
#include "XYZaxis.h"

class Camera;
class ColorShader;
class TextureShader;

////////////////////////////////////////////////////////////////////////////////
// Class name: Graphics
////////////////////////////////////////////////////////////////////////////////
class Graphics
{
public:
	Graphics();
	Graphics(const Graphics&);
	~Graphics();

	bool Initialize(int, int, HWND, Camera*, ArrayList<IViewModel> * viewModels);
	void Shutdown();
	bool Frame(); 



private:
	bool Render();

private:
	
	HWND	hwnd;
	D3D*	d3D;
	Camera*	camera;

	Model*   axisModel;
	XYZaxis* axis;

	ColorShader*   colorShader;
	TextureShader* textureShader;

	ArrayList<IViewModel> * viewModels;



};

////////////////////////////////////////////////////////////////////////////////
// CONSTANTS
////////////////////////////////////////////////////////////////////////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;