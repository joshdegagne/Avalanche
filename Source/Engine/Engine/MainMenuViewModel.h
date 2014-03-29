
#pragma once

#include "ViewModel.h"
#include "SpriteBatch.h"
#include "TextureShader.h"
#include "SpriteFont.h"
#include "EntityType.h"
#include "GeometricPrimitive.h"
#include "CommonStates.h"
#include "ColorShader.h"
#include "PrimitiveBatch.h"
#include "Effects.h"
#include "VertexTypes.h"

class MainMenu;
class TextureManager;

using namespace DirectX;

class MainMenuViewModel : public ViewModel<MainMenu>
{
public:
	MainMenuViewModel(Game& game); // Initialize SpriteBatch with device context (every menu ViewModel will do this)
	virtual ~MainMenuViewModel();
	//MainMenuViewModel(Game&);
	bool InitializeTextures(TextureManager* texMan); // Load fonts, background textures
	bool InitializeVertexModels(ID3D11Device *d3dDevice);
	bool initializeTextures(ID3D11Device* d3dDevice) { return true; } // Deprecated
	virtual void cleanUpArrayMemory();

protected:
	bool RenderEntity(ID3D11DeviceContext*, XMFLOAT4X4, XMFLOAT4X4, ColorShader*, TextureShader*, MainMenu*); // Draw with SpriteBatch if the main menu is active; also highlight selected item

private:
	//std::unique_ptr<SpriteBatch> spriteBatch;
	//std::unique_ptr<SpriteFont>	spriteFont;

	
	std::unique_ptr<BasicEffect>                            batchEffect;
	std::unique_ptr<GeometricPrimitive>                     shape;
	std::unique_ptr<PrimitiveBatch<VertexPositionColor>>    batch;
	std::unique_ptr<SpriteFont>                             font;
	SpriteBatch*				                            sprites;
};