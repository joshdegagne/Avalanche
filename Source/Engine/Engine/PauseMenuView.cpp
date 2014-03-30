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
		spriteFontNormal->DrawString(spriteBatch, L"PAUSED", XMFLOAT2(310, 150), Colors::Purple);

		spriteFontNormal->DrawString(spriteBatch, L"resume game", XMFLOAT2(260, 213), Colors::Silver);
		spriteFontNormal->DrawString(spriteBatch, L"how to play", XMFLOAT2(275, 263), Colors::Silver);
		spriteFontNormal->DrawString(spriteBatch, L"exit to menu", XMFLOAT2(268, 313), Colors::Silver);

		switch(menu->getCurrentSelection())
		{
		case 0: spriteFontNormal->DrawString(spriteBatch, L"resume game", XMFLOAT2(260, 213), Colors::Purple); break;
		case 1: spriteFontNormal->DrawString(spriteBatch, L"how to play", XMFLOAT2(275, 263), Colors::Purple); break;
		case 2: spriteFontNormal->DrawString(spriteBatch, L"exit to menu", XMFLOAT2(268, 313), Colors::Purple); break;
		}

		spriteBatch->End();

		game->getGraphics()->getD3D()->getSwapChain()->Present(0,0);
	}

	return true;
}