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

		//font->DrawString(sprites, L"AVALANCHE", XMFLOAT2(278, 85), Colors::Purple);
		spriteFontBig->DrawString(spriteBatch, L"AVALANCHE", XMFLOAT2(MENU_TITLE_X, MENU_TITLE_Y), Colors::Purple);

		switch(menu->getPausedPlayer())
		{
		case 0: spriteFontNormal->DrawString(spriteBatch, L"PLAYER 1 PAUSED", XMFLOAT2(228, 155), Colors::Purple); break;
		case 1: spriteFontNormal->DrawString(spriteBatch, L"PLAYER 2 PAUSED", XMFLOAT2(228, 155), Colors::Purple); break;
		case 2: spriteFontNormal->DrawString(spriteBatch, L"PLAYER 3 PAUSED", XMFLOAT2(228, 155), Colors::Purple); break;
		case 3: spriteFontNormal->DrawString(spriteBatch, L"PLAYER 4 PAUSED", XMFLOAT2(228, 155), Colors::Purple); break;
		}


		

		spriteFontNormal->DrawString(spriteBatch, L"resume game", XMFLOAT2(260, 213), Colors::Silver);
		spriteFontNormal->DrawString(spriteBatch, L"how to play", XMFLOAT2(275, 263), Colors::Silver);
		spriteFontNormal->DrawString(spriteBatch, L"exit to menu", XMFLOAT2(265, 313), Colors::Silver);

		switch(menu->getCurrentSelection())
		{
		case 0: spriteFontNormal->DrawString(spriteBatch, L"resume game", XMFLOAT2(260, 213), Colors::MediumPurple); break;
		case 1: spriteFontNormal->DrawString(spriteBatch, L"how to play", XMFLOAT2(275, 263), Colors::MediumPurple); break;
		case 2: spriteFontNormal->DrawString(spriteBatch, L"exit to menu", XMFLOAT2(265, 313), Colors::MediumPurple); break;
		}

		spriteBatch->End();

		game->getGraphics()->getD3D()->getSwapChain()->Present(0,0);
	}

	return true;
}