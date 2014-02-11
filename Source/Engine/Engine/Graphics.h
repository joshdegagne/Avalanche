////////////////////////////////////////////////////////////////////////////////
// Filename: Graphics.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_



///////////////////////
// MY CLASS INCLUDES //
///////////////////////


#include "D3D.h"
#include "cinecamera.h"
#include "Model.h"
#include "arraylist.h"
#include "gamemodel.h"
#include "XYZaxis.h"

#include "ColorShader.h"
#include "TextureShader.h"


/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;


////////////////////////////////////////////////////////////////////////////////
// Class name: Graphics
////////////////////////////////////////////////////////////////////////////////
class Graphics
{
public:
	Graphics();
	Graphics(const Graphics&);
	~Graphics();

	bool Initialize(int, int, HWND, CineCamera*, ArrayList<GameModel> * gameModels);
	void Shutdown();
	bool Frame(); 



private:
	bool Render();

private:
	
	HWND        hwnd;
	D3D*        d3D;
	CineCamera* camera;

	Model*   axisModel;
	XYZaxis* axis;

	ColorShader*   colorShader;
	TextureShader* textureShader;

	ArrayList<GameModel> * gameWorldModels;



};

#endif