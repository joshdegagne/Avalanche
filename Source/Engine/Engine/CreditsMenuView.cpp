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
#include "CreditsMenu.h"
#include "CreditsMenuView.h"

CreditsMenuView::CreditsMenuView(Game& g)
{
	game = &g;
}

bool CreditsMenuView::Draw(CreditsMenu* menu)
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
		spriteFontNormal->DrawString(spriteBatch, L"CREDITS", XMFLOAT2(315.0f + resolutionWidthOffset, 153.0f + resolutionHeightOffset), Colors::Purple);
		
		spriteFontNormal->DrawString(spriteBatch, L"max goad", XMFLOAT2(300.0f + resolutionWidthOffset, 213.0f + resolutionHeightOffset), Colors::Red);
		spriteFontNormal->DrawString(spriteBatch, L"cameron davies", XMFLOAT2(240.0f + resolutionWidthOffset, 263.0f + resolutionHeightOffset), Colors::Blue);
		spriteFontNormal->DrawString(spriteBatch, L"josh degagne", XMFLOAT2(270.0f + resolutionWidthOffset, 313.0f + resolutionHeightOffset), Colors::Green);
		spriteFontNormal->DrawString(spriteBatch, L"richard huynh", XMFLOAT2(262.0f + resolutionWidthOffset, 363.0f + resolutionHeightOffset), Colors::Purple);

		/*
		spriteFontNormal->DrawString(spriteBatch, L"left analog to move", XMFLOAT2(195, 380), Colors::DarkGreen);
		spriteFontNormal->DrawString(spriteBatch, L"left or right trigger to roll", XMFLOAT2(130, 430), Colors::DarkGreen);
		spriteFontNormal->DrawString(spriteBatch, L"a button to jump", XMFLOAT2(223, 480), Colors::DarkGreen);
		*/

		spriteBatch->End();

		game->getGraphics()->getD3D()->getSwapChain()->Present(0,0);
	}

	return true;
}