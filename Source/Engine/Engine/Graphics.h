////////////////////////////////////////////////////////////////////////////////
// Filename: Graphics.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "D3D.h"
#include "Model.h"
#include "arraylist.h"
#include "XYZaxis.h"

class Camera;
class ColorShader;
class TextureShader;
class IViewModel;

////////////////////////////////////////////////////////////////////////////////
// Class name: Graphics
////////////////////////////////////////////////////////////////////////////////
class Graphics
{
public:
	Graphics();
	Graphics(const Graphics&);
	~Graphics();

	ID3D11Device*        getDevice()     { return d3D->GetDevice(); }
	ID3D11DeviceContext* getContext()    { return d3D->GetContext();}
	ID3D11BlendState*    getBlendState() { return d3D->GetBlendState(); }

	bool Initialize(int, int, HWND, Camera*);
	void Shutdown();
	bool Render(ArrayList<IViewModel>* viewModels);

private:
	
	HWND	hwnd;
	D3D*	d3D;
	Camera*	camera;

	Model*   axisModel;
	XYZaxis* axis;

	ColorShader*   colorShader;
	TextureShader* textureShader;
};

////////////////////////////////////////////////////////////////////////////////
// CONSTANTS
////////////////////////////////////////////////////////////////////////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;