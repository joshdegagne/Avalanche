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
#include "Game.h"

MainMenuViewModel::MainMenuViewModel(Game& g) : ViewModel<MainMenu>(EntityType::MENU)
{
	//spriteFont = new SpriteFont(game.getContext(), "italic.spritefont");


	//font.reset(new SpriteFont(game.getContext(), "italic.spritefont"));


	sprites = new SpriteBatch(g.getContext());
	font.reset(new SpriteFont(g.getDevice(), L"tempesta7_menu.spritefont"));

	if (!sprites)
		writeTextToConsole(L"spritebatch not ok");

	if (!font)
		writeTextToConsole(L"spritefont not ok");

	game = &g;
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

bool MainMenuViewModel::Draw(MainMenu* menu)
{
	//if(!textureShader) return false; //we were not provided with a shader
	
	//writeTextToConsole(L"MainMenuViewModel::Draw");z

	//game.getContext()->ClearRenderTargetView(

	if (menu->isActive())
	{
		//writeTextToConsole(L"menu->isActive()");
		//sprites->Begin(SpriteSortMode_Deferred);
		sprites->Begin();

		//font->DrawString(sprites, L"AVALANCHE", XMFLOAT2(278, 85), Colors::Purple);
		game->getGraphics()->getSpriteFontBig()->DrawString(sprites, L"AVALANCHE", XMFLOAT2(200, 75), Colors::Purple);







		
		font->DrawString(sprites, L"start game", XMFLOAT2(275, 200), Colors::Silver);
		font->DrawString(sprites, L"view controls", XMFLOAT2(255, 250), Colors::Silver);
		font->DrawString(sprites, L"view credits", XMFLOAT2(270, 300), Colors::Silver);
		font->DrawString(sprites, L"quit game", XMFLOAT2(293, 350), Colors::Silver);

		

		//menu->getCurrentSelection();

		switch(menu->getCurrentSelection())
		{
		case 0: font->DrawString(sprites, L"start game", XMFLOAT2(275, 200), Colors::Purple); break;
		case 1: font->DrawString(sprites, L"view controls", XMFLOAT2(255, 250), Colors::Purple); break;
		case 2: font->DrawString(sprites, L"view credits", XMFLOAT2(270, 300), Colors::Purple); break;
		case 3: font->DrawString(sprites, L"quit game", XMFLOAT2(293, 350), Colors::Purple); break;
		}

		//writeLabelToConsole(
		//writeTextToConsole(L"MainMenuViewModel::RenderEntity");

		sprites->End();

		game->getGraphics()->getD3D()->getSwapChain()->Present(0,0);
	}

	return true;
}