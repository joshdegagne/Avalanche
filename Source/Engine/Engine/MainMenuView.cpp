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


		spriteBatch->Begin();

		//font->DrawString(sprites, L"AVALANCHE", XMFLOAT2(278, 85), Colors::Purple);
		spriteFontBig->DrawString(spriteBatch, L"AVALANCHE", XMFLOAT2(MENU_TITLE_X, MENU_TITLE_Y), Colors::Purple);



		spriteFontNormal->DrawString(spriteBatch, L"start game", XMFLOAT2(280, 200), Colors::Silver);
		spriteFontNormal->DrawString(spriteBatch, L"how to play", XMFLOAT2(278, 250), Colors::Silver);
		spriteFontNormal->DrawString(spriteBatch, L"view credits", XMFLOAT2(270, 300), Colors::Silver);
		spriteFontNormal->DrawString(spriteBatch, L"quit game", XMFLOAT2(297, 350), Colors::Silver);

		switch(menu->getCurrentSelection())
		{
		case 0: spriteFontNormal->DrawString(spriteBatch, L"start game", XMFLOAT2(280, 200), Colors::MediumPurple); break;
		case 1: spriteFontNormal->DrawString(spriteBatch, L"how to play", XMFLOAT2(278, 250), Colors::MediumPurple); break;
		case 2: spriteFontNormal->DrawString(spriteBatch, L"view credits", XMFLOAT2(270, 300), Colors::MediumPurple); break;
		case 3: spriteFontNormal->DrawString(spriteBatch, L"quit game", XMFLOAT2(297, 350), Colors::MediumPurple); break;
		}

		spriteBatch->End();

		game->getGraphics()->getD3D()->getSwapChain()->Present(0,0);
	}

	return true;
}