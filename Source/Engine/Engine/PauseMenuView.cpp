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
#include "PauseMenuView.h"
#include "PauseMenu.h"

PauseMenuView::PauseMenuView(Game& g)
{
	game = &g;
}

bool PauseMenuView::Draw(PauseMenu* menu)
{
	if (menu->isActive())
	{
		SpriteBatch* spriteBatch = game->getGraphics()->getSpriteBatch();
		SpriteFont* spriteFontBig = game->getGraphics()->getSpriteFontBig();
		SpriteFont* spriteFontNormal = game->getGraphics()->getSpriteFontNormal();


		spriteBatch->Begin();

		// From the original 800x600 positions to 1366x768
		// Can be refactored to use inheritance and be dynamic to whatever the screen dimensions are
		float resolutionWidthOffset = 283.0f;
		float resolutionHeightOffset = 84.0f;

		//font->DrawString(sprites, L"AVALANCHE", XMFLOAT2(278, 85), Colors::Purple);
		spriteFontBig->DrawString(spriteBatch, L"AVALANCHE", XMFLOAT2(MENU_TITLE_X, MENU_TITLE_Y), Colors::Purple);

		switch(menu->getPausedPlayer())
		{
		case 0: spriteFontNormal->DrawString(spriteBatch, L"PLAYER 1 PAUSED", XMFLOAT2(228.0f + resolutionWidthOffset, 155.0f + resolutionHeightOffset), Colors::Purple); break;
		case 1: spriteFontNormal->DrawString(spriteBatch, L"PLAYER 2 PAUSED", XMFLOAT2(228.0f + resolutionWidthOffset, 155.0f + resolutionHeightOffset), Colors::Purple); break;
		case 2: spriteFontNormal->DrawString(spriteBatch, L"PLAYER 3 PAUSED", XMFLOAT2(228.0f + resolutionWidthOffset, 155.0f + resolutionHeightOffset), Colors::Purple); break;
		case 3: spriteFontNormal->DrawString(spriteBatch, L"PLAYER 4 PAUSED", XMFLOAT2(228.0f + resolutionWidthOffset, 155.0f + resolutionHeightOffset), Colors::Purple); break;
		}

		

		spriteFontNormal->DrawString(spriteBatch, L"resume game", XMFLOAT2(260.0f + resolutionWidthOffset, 213.0f + resolutionHeightOffset), Colors::Silver);
		spriteFontNormal->DrawString(spriteBatch, L"how to play", XMFLOAT2(275.0f + resolutionWidthOffset, 263.0f + resolutionHeightOffset), Colors::Silver);
		spriteFontNormal->DrawString(spriteBatch, L"exit to menu", XMFLOAT2(265.0f + resolutionWidthOffset, 313.0f + resolutionHeightOffset), Colors::Silver);

		switch(menu->getCurrentSelection())
		{
		case 0: spriteFontNormal->DrawString(spriteBatch, L"resume game", XMFLOAT2(260.0f + resolutionWidthOffset, 213.0f + resolutionHeightOffset), Colors::Purple); break;
		case 1: spriteFontNormal->DrawString(spriteBatch, L"how to play", XMFLOAT2(275.0f + resolutionWidthOffset, 263.0f + resolutionHeightOffset), Colors::Purple); break;
		case 2: spriteFontNormal->DrawString(spriteBatch, L"exit to menu", XMFLOAT2(265.0f + resolutionWidthOffset, 313.0f + resolutionHeightOffset), Colors::Purple); break;
		}

		spriteBatch->End();

		game->getGraphics()->getD3D()->getSwapChain()->Present(0,0);
	}

	return true;
}