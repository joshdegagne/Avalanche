////////////////////////////////////////////////////////////////////////////////
// Filename: Graphics.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "D3D.h"
#include "Model.h"
#include "arraylist.h"
#include "XYZaxis.h"
#include "SpriteBatch.h"
#include "SpriteFont.h"
#include "Effects.h"

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
	D3D*				 getD3D()		 { return d3D; }
	SpriteFont* getSpriteFontBig() { return spriteFontBig.get(); }
	SpriteFont* getSpriteFontNormal() { return spriteFontNormal.get(); }
	SpriteBatch* getSpriteBatch() { return spriteBatch; }

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

	std::unique_ptr<SpriteFont> spriteFontBig;
	std::unique_ptr<SpriteFont> spriteFontNormal;
	SpriteBatch* spriteBatch;
};

////////////////////////////////////////////////////////////////////////////////
// CONSTANTS
////////////////////////////////////////////////////////////////////////////////
const bool FULL_SCREEN = true;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;