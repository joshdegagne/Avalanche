#include "MainMenuViewModel.h"
#include "EntityType.h"
#include "SmallRockObstacle.h"
#include "SmallRockViewModel.h"
#include "TextureShader.h"
#include "Texture.h"
#include "ViewModel.cpp"
#include "DebugConsole.h"

MainMenuViewModel::MainMenuViewModel(Game& game) : ViewModel<MainMenu>(EntityType::MENU)
{
	//spriteFont = new SpriteFont(game.getContext(), "italic.spritefont");


	//font.reset(new SpriteFont(game.getContext(), "italic.spritefont"));
}

MainMenuViewModel::~MainMenuViewModel()
{
}

bool MainMenuViewModel::InitializeTextures(TextureManager* texMan)
{
	return true;
}

bool MainMenuViewModel::InitializeVertexModels(ID3D11Device* device)
{
	return true;
}
/*
bool MainMenuViewModel::initializeTextures(ID3D11Device* device)
{
	return true;
}
*/
bool MainMenuViewModel::RenderEntity(ID3D11DeviceContext* deviceContext,  XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, ColorShader* colorShader, TextureShader* textureShader, MainMenu* menu)
{
	return true;
}

void MainMenuViewModel::cleanUpArrayMemory()
{
}