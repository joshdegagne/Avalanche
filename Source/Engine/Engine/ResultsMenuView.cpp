#include "EntityType.h"
#include "SmallRockObstacle.h"
#include "SmallRockViewModel.h"
#include "TextureShader.h"
#include "Texture.h"
#include "ViewModel.cpp"
#include "DebugConsole.h"
#include "SpriteFont.h"
#include "Player.h"
#include "Game.h"
#include "ResultsMenu.h"
#include "ResultsMenuView.h"
#include <vector>

ResultsMenuView::ResultsMenuView(Game& g)
{
	game = &g;
}

bool ResultsMenuView::Draw(ResultsMenu* menu)
{
	if (menu->isActive())
	{
		SpriteBatch* spriteBatch = game->getGraphics()->getSpriteBatch();
		SpriteFont* spriteFontBig = game->getGraphics()->getSpriteFontBig();
		SpriteFont* spriteFontNormal = game->getGraphics()->getSpriteFontNormal();

		spriteBatch->Begin();


		game->getGraphics()->getSpriteFontBig()->DrawString(game->getGraphics()->getSpriteBatch(), L"AVALANCHE", XMFLOAT2(MENU_TITLE_X, MENU_TITLE_Y), Colors::Purple);


		int x = 218;
		int x2 = 180;


		game->getGraphics()->getSpriteFontNormal()->DrawString(spriteBatch, L"game over", XMFLOAT2(295, 150), Colors::Purple);


		// terribly hardcoded for the final presentation, i'm sorry
		for(std::vector<bool>::size_type i = menu->getSurvivors().size() - 1; i != (std::vector<int>::size_type) -1; i--) 
		{
			if (i == 0)
			{
				if(menu->getSurvivors()[i])
					game->getGraphics()->getSpriteFontNormal()->DrawString(spriteBatch, L"player 1 survived!", XMFLOAT2(x, 213), Colors::DarkRed);
				else
					game->getGraphics()->getSpriteFontNormal()->DrawString(spriteBatch, L"player 1 went missing", XMFLOAT2(x2, 213), Colors::Silver);
			}
			else if (i == 1)
			{
				if(menu->getSurvivors()[i])
					game->getGraphics()->getSpriteFontNormal()->DrawString(spriteBatch, L"player 2 survived!", XMFLOAT2(x, 263), Colors::DarkSlateBlue);
				else
					game->getGraphics()->getSpriteFontNormal()->DrawString(spriteBatch, L"player 2 went missing", XMFLOAT2(x2, 263), Colors::Silver);
			}
			else if (i == 2)
			{
				if(menu->getSurvivors()[i])
					game->getGraphics()->getSpriteFontNormal()->DrawString(spriteBatch, L"player 3 survived!", XMFLOAT2(x, 313), Colors::DarkOliveGreen);
				else
					game->getGraphics()->getSpriteFontNormal()->DrawString(spriteBatch, L"player 3 went missing", XMFLOAT2(x2, 313), Colors::Silver);
			}
			else if (i == 3)
			{
				if(menu->getSurvivors()[i])
					game->getGraphics()->getSpriteFontNormal()->DrawString(spriteBatch, L"player 4 survived!", XMFLOAT2(x, 363), Colors::Pink);
				else
					game->getGraphics()->getSpriteFontNormal()->DrawString(spriteBatch, L"player 4 went missing", XMFLOAT2(x2, 363), Colors::Silver);
			}
		}

		spriteBatch->End();
		
		game->getGraphics()->getD3D()->getSwapChain()->Present(0,0);

	}
	return true;
}

ResultsMenuView::~ResultsMenuView()
{
	if (game)
	{
		delete game;
		game = 0;
	}
}