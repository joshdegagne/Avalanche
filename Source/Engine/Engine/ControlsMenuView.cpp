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
#include "ControlsMenu.h"
#include "ControlsMenuView.h"

ControlsMenuView::ControlsMenuView(Game& g)
{
	game = &g;
}

bool ControlsMenuView::Draw(ControlsMenu* menu)
{
	if (menu->isActive())
	{
		SpriteBatch* spriteBatch = game->getGraphics()->getSpriteBatch();
		SpriteFont* spriteFontBig = game->getGraphics()->getSpriteFontBig();
		SpriteFont* spriteFontNormal = game->getGraphics()->getSpriteFontNormal();


		spriteBatch->Begin();

		float xPos = 170.0f;

		//font->DrawString(sprites, L"AVALANCHE", XMFLOAT2(278, 85), Colors::Purple);
		spriteFontBig->DrawString(spriteBatch, L"AVALANCHE", XMFLOAT2(MENU_TITLE_X, MENU_TITLE_Y), Colors::Purple);
		spriteFontNormal->DrawString(spriteBatch, L"HOW TO PLAY", XMFLOAT2(275.0f, 150.0f), Colors::Purple);
		
		spriteFontNormal->DrawString(spriteBatch, L"1.", XMFLOAT2(xPos, 213.0f), Colors::MediumPurple);
		spriteFontNormal->DrawString(spriteBatch, L"2.", XMFLOAT2(xPos, 263.0f), Colors::MediumPurple);
		spriteFontNormal->DrawString(spriteBatch, L"3.", XMFLOAT2(xPos, 313.0f), Colors::MediumPurple);

		spriteFontNormal->DrawString(spriteBatch, L"dodge obstacles", XMFLOAT2(xPos + 55.0f, 213.0f), Colors::MediumPurple);
		spriteFontNormal->DrawString(spriteBatch, L"tackle friends", XMFLOAT2(xPos + 55.0f, 263.0f), Colors::MediumPurple);
		spriteFontNormal->DrawString(spriteBatch, L"don't fall behind", XMFLOAT2(xPos + 55.0f, 313.0f), Colors::MediumPurple);

		spriteFontNormal->DrawString(spriteBatch, L"move:", XMFLOAT2(xPos, 380.0f), Colors::DarkGreen);
		spriteFontNormal->DrawString(spriteBatch, L"roll:", XMFLOAT2(xPos, 430.0f), Colors::DarkGreen);
		spriteFontNormal->DrawString(spriteBatch, L"jump:", XMFLOAT2(xPos, 480.0f), Colors::DarkGreen);

		spriteFontNormal->DrawString(spriteBatch, L"left analog stick", XMFLOAT2(xPos + 145.0f, 380.0f), Colors::DarkGreen);
		spriteFontNormal->DrawString(spriteBatch, L"left or right trigger", XMFLOAT2(xPos + 145.0f, 430.0f), Colors::DarkGreen);
		spriteFontNormal->DrawString(spriteBatch, L"A button", XMFLOAT2(xPos + 145.0f, 480.0f), Colors::DarkGreen);

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