#include "MainMenuView.h"
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

		int xPos = 190;

		//font->DrawString(sprites, L"AVALANCHE", XMFLOAT2(278, 85), Colors::Purple);
		spriteFontBig->DrawString(spriteBatch, L"AVALANCHE", XMFLOAT2(MENU_TITLE_X, MENU_TITLE_Y), Colors::Purple);
		spriteFontNormal->DrawString(spriteBatch, L"HOW TO PLAY", XMFLOAT2(260, 150), Colors::Purple);
		
		spriteFontNormal->DrawString(spriteBatch, L"1.  dodge obstacles", XMFLOAT2(xPos, 213), Colors::MediumPurple);
		spriteFontNormal->DrawString(spriteBatch, L"2. tackle friends", XMFLOAT2(xPos, 263), Colors::MediumPurple);
		spriteFontNormal->DrawString(spriteBatch, L"3. don't fall behind", XMFLOAT2(xPos, 313), Colors::MediumPurple);

		spriteFontNormal->DrawString(spriteBatch, L"move:  left analog stick", XMFLOAT2(xPos, 380), Colors::DarkGreen);
		spriteFontNormal->DrawString(spriteBatch, L"roll:     left or right trigger", XMFLOAT2(xPos, 430), Colors::DarkGreen);
		spriteFontNormal->DrawString(spriteBatch, L"jump:   A button", XMFLOAT2(xPos, 480), Colors::DarkGreen);

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