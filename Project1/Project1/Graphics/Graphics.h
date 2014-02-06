////////////////////////////////////////////////////////////////////////////////
// Filename: Graphics.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_



///////////////////////
// MY CLASS INCLUDES //
///////////////////////


#include "D3D.h"
#include "CineCamera.h"
#include "../modelUtil.h"
#include "../arraylist.h"
#include "../Model.h"
#include "../XYZaxis.h"



#include "ColorShader.h"



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

	bool Initialize(int, int, HWND, CineCamera*, ArrayList<Model> * gameModels);
	void Shutdown();
	bool Frame(); 



private:
	bool Render();

private:
	
	XYZaxis* axis;
	ModelUtil* axisModel;

	HWND m_hwnd;
	D3D* m_D3D;
	CineCamera* m_Camera;

	//Model* m_AxisModel;
	//XYZaxis* m_axis;

	ColorShader* m_ColorShader;

	//ArrayList<GameModel> * m_GameWorldModels;



};

#endif