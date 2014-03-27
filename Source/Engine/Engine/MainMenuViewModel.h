
#pragma once

#include "ViewModel.h"
#include "SpriteBatch.h"
#include "TextureShader.h"

class MainMenu;

class MainMenuViewModel : public ViewModel<MainMenu>
{
public:
	MainMenuViewModel(); // Initialize SpriteBatch with device context (every menu ViewModel will do this)
	virtual ~MainMenuViewModel();
	MainMenuViewModel(Game&);
	bool InitializeTextures(TextureManager* texMan); // Load fonts, background textures
	bool InitializeVertexModels(ID3D11Device *d3dDevice);
protected:
	bool initializeTextures(ID3D11Device* d3dDevice) { return true; } // Deprecated
	bool RenderEntity(ID3D11DeviceContext*, XMFLOAT4X4, XMFLOAT4X4, ColorShader*, TextureShader*, MainMenu*); // Draw with SpriteBatch if the main menu is active; also highlight selected item
private:
	std::unique_ptr<SpriteBatch> spriteBatch;
};