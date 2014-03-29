#include "MainMenuViewModel.h"
#include "EntityType.h"
#include "SmallRockObstacle.h"
#include "SmallRockViewModel.h"
#include "TextureShader.h"
#include "Texture.h"
#include "ViewModel.cpp"
#include "DebugConsole.h"
#include "SpriteFont.h"
#include "MainMenu.h"'
#include "Player.h"

MainMenuViewModel::MainMenuViewModel(Game& game) : ViewModel<MainMenu>(EntityType::MENU)
{
	//spriteFont = new SpriteFont(game.getContext(), "italic.spritefont");


	//font.reset(new SpriteFont(game.getContext(), "italic.spritefont"));

	writeTextToConsole(L"MainMenuViewModel::MainMenuViewModel");
	sprites = new SpriteBatch(game.getContext());
	font.reset(new SpriteFont(game.getDevice(), L"italic.spritefont"));
}

MainMenuViewModel::~MainMenuViewModel()
{
}

bool MainMenuViewModel::InitializeTextures(TextureManager* texMan)
{
	//writeTextToConsole(L"MainMenuViewModel::InitializeTextures");
	return true;
}

bool MainMenuViewModel::InitializeVertexModels(ID3D11Device* device)
{
	//writeTextToConsole(L"MainMenuViewModel::InitializeVertexModels");
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
	writeTextToConsole(L"MainMenuViewModel::RenderEntity");
	if(!textureShader) return false; //we were not provided with a shader

	//if (menu->isActive())
	//{
		sprites->Begin(SpriteSortMode_Deferred);

		font->DrawString(sprites, L"AVALANCHE", XMFLOAT2(200, 200), Colors::Purple);

		//writeLabelToConsole(
		//writeTextToConsole(L"MainMenuViewModel::RenderEntity");

		sprites->End();
	//}

	return true;
}

void MainMenuViewModel::cleanUpArrayMemory()
{
}