#include "MainMenuView.h"
#include "EntityType.h"
#include "SmallRockObstacle.h"
#include "SmallRockViewModel.h"
#include "TextureShader.h"
#include "Texture.h"
#include "ViewModel.cpp"
#include "DebugConsole.h"
#include "SpriteFont.h"
#include "MainMenu.h"
#include "Player.h"
#include "Game.h"
#include "DebugDefinitions.h"

MainMenuView::MainMenuView(Game& g)
{
	game = &g;
}

bool MainMenuView::Draw(MainMenu* menu)
{
	if (menu->isActive())
	{
		SpriteBatch* spriteBatch = game->getGraphics()->getSpriteBatch();
		SpriteFont* spriteFontBig = game->getGraphics()->getSpriteFontBig();
		SpriteFont* spriteFontNormal = game->getGraphics()->getSpriteFontNormal();

		// 800->1366 (+566)
		// 600->768 (+168)
		// From the original 800x600 positions to 1366x768
		float resolutionWidthOffset = 283.0f; 
		float resolutionHeightOffset = 84.0f;

		spriteBatch->Begin();

		//font->DrawString(sprites, L"AVALANCHE", XMFLOAT2(278, 85), Colors::Purple);
		spriteFontBig->DrawString(spriteBatch, L"AVALANCHE", XMFLOAT2(MENU_TITLE_X, MENU_TITLE_Y), Colors::Purple);



		spriteFontNormal->DrawString(spriteBatch, L"start game", XMFLOAT2(280.0f + resolutionWidthOffset, 200.0f + resolutionHeightOffset), Colors::Silver);
		spriteFontNormal->DrawString(spriteBatch, L"how to play", XMFLOAT2(278.0f + resolutionWidthOffset, 250.0f + resolutionHeightOffset), Colors::Silver);
		spriteFontNormal->DrawString(spriteBatch, L"view credits", XMFLOAT2(270.0f + resolutionWidthOffset, 300.0f + resolutionHeightOffset), Colors::Silver);
		spriteFontNormal->DrawString(spriteBatch, L"quit game", XMFLOAT2(297.0f + resolutionWidthOffset, 350.0f + resolutionHeightOffset), Colors::Silver);

		switch(menu->getCurrentSelection())
		{
		case 0: spriteFontNormal->DrawString(spriteBatch, L"start game", XMFLOAT2(280.0f + resolutionWidthOffset, 200.0f + resolutionHeightOffset), Colors::Purple); break;
		case 1: spriteFontNormal->DrawString(spriteBatch, L"how to play", XMFLOAT2(278.0f + resolutionWidthOffset, 250.0f + resolutionHeightOffset), Colors::Purple); break;
		case 2: spriteFontNormal->DrawString(spriteBatch, L"view credits", XMFLOAT2(270.0f + resolutionWidthOffset, 300.0f + resolutionHeightOffset), Colors::Purple); break;
		case 3: spriteFontNormal->DrawString(spriteBatch, L"quit game", XMFLOAT2(297.0f + resolutionWidthOffset, 350.0f + resolutionHeightOffset), Colors::Purple); break;
		}

		spriteBatch->End();

		game->getGraphics()->getD3D()->getSwapChain()->Present(0,0);
	}

	return true;
}