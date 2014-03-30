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
#include "PlayerSelectMenu.h"
#include "PlayerSelectMenuView.h"

PlayerSelectMenuView::PlayerSelectMenuView(Game& g)
{
	game = &g;
}

bool PlayerSelectMenuView::Draw(PlayerSelectMenu* menu)
{
	if (menu->isActive())
	{
		SpriteBatch* spriteBatch = game->getGraphics()->getSpriteBatch();
		SpriteFont* spriteFontBig = game->getGraphics()->getSpriteFontBig();
		SpriteFont* spriteFontNormal = game->getGraphics()->getSpriteFontNormal();

		spriteBatch->Begin();

		
		
		game->getGraphics()->getSpriteFontBig()->DrawString(game->getGraphics()->getSpriteBatch(), L"AVALANCHE", XMFLOAT2(MENU_TITLE_X, MENU_TITLE_Y), Colors::Purple); // 75?

		//game->getGraphics()->getSpriteFontNormal()->DrawString(spriteBatch, L"players", XMFLOAT2(315, 155), Colors::Purple);
		game->getGraphics()->getSpriteFontNormal()->DrawString(spriteBatch, L"PLAYERS", XMFLOAT2(315, 153), Colors::Purple);

		//spriteFontBig->DrawString(spriteBatch, L"1", XMFLOAT2(373, 200), Colors::Silver);


		spriteFontBig->DrawString(spriteBatch, L"2", XMFLOAT2(372, 210), Colors::Silver);
		spriteFontBig->DrawString(spriteBatch, L"3", XMFLOAT2(372, 270), Colors::Silver);
		spriteFontBig->DrawString(spriteBatch, L"4", XMFLOAT2(372, 330), Colors::Silver);

		spriteFontNormal->DrawString(spriteBatch, L"player", XMFLOAT2(25, 450), Colors::Red);
		spriteFontBig->DrawString(spriteBatch, L"1", XMFLOAT2(70, 500), Colors::Red);

		switch(menu->getCurrentSelection())
		{
		case 0: spriteFontBig->DrawString(spriteBatch, L"2", XMFLOAT2(372, 210), Colors::Purple); 
				spriteFontNormal->DrawString(spriteBatch, L"player", XMFLOAT2(225, 450), Colors::DarkSlateBlue);
				spriteFontBig->DrawString(spriteBatch, L"2", XMFLOAT2(270, 500), Colors::DarkSlateBlue);
				break;
		case 1: spriteFontBig->DrawString(spriteBatch, L"3", XMFLOAT2(372, 270), Colors::Purple); 
				spriteFontNormal->DrawString(spriteBatch, L"player", XMFLOAT2(225, 450), Colors::DarkSlateBlue);
				spriteFontBig->DrawString(spriteBatch, L"2", XMFLOAT2(270, 500), Colors::DarkSlateBlue);
				spriteFontNormal->DrawString(spriteBatch, L"player", XMFLOAT2(425, 450), Colors::DarkOliveGreen);
				spriteFontBig->DrawString(spriteBatch, L"3", XMFLOAT2(470, 500), Colors::DarkOliveGreen);
				break;
		case 2: spriteFontBig->DrawString(spriteBatch, L"4", XMFLOAT2(372, 330), Colors::Purple); 
				spriteFontNormal->DrawString(spriteBatch, L"player", XMFLOAT2(225, 450), Colors::DarkSlateBlue);
				spriteFontBig->DrawString(spriteBatch, L"2", XMFLOAT2(270, 500), Colors::DarkSlateBlue);
				spriteFontNormal->DrawString(spriteBatch, L"player", XMFLOAT2(425, 450), Colors::DarkOliveGreen);
				spriteFontBig->DrawString(spriteBatch, L"3", XMFLOAT2(470, 500), Colors::DarkOliveGreen);
				spriteFontNormal->DrawString(spriteBatch, L"player", XMFLOAT2(625, 450), Colors::Purple);
				spriteFontBig->DrawString(spriteBatch, L"4", XMFLOAT2(670, 500), Colors::Purple);
				break;
		}


		/*
		game->getGraphics()->getSpriteFontNormal()->DrawString(game->getGraphics()->getSpriteBatch(), L"start game", XMFLOAT2(275, 200), Colors::Silver);
		game->getGraphics()->getSpriteFontNormal()(game->getGraphics()->getSpriteBatch(), L"view controls", XMFLOAT2(255, 250), Colors::Silver);
		game->getGraphics()->getSpriteFontNormal()(game->getGraphics()->getSpriteBatch(), L"view credits", XMFLOAT2(270, 300), Colors::Silver);
		game->getGraphics()->getSpriteFontNormal()(game->getGraphics()->getSpriteBatch(), L"quit game", XMFLOAT2(293, 350), Colors::Silver);
		*/
		/*

		//menu->getCurrentSelection();

		switch(menu->getCurrentSelection())
		{
		case 0: font->DrawString(sprites, L"start game", XMFLOAT2(275, 200), Colors::Purple); break;
		case 1: font->DrawString(sprites, L"view controls", XMFLOAT2(255, 250), Colors::Purple); break;
		case 2: font->DrawString(sprites, L"view credits", XMFLOAT2(270, 300), Colors::Purple); break;
		case 3: font->DrawString(sprites, L"quit game", XMFLOAT2(293, 350), Colors::Purple); break;
		}
		*/


		spriteBatch->End();

		
		game->getGraphics()->getD3D()->getSwapChain()->Present(0,0);

	}
	return true;
}


/*
PlayerSelectMenuView::PlayerSelectMenuView(Game& g)
{
	game = &g;
}

bool PlayerSelectMenuView::Draw(PlayerSelectMenu* menu)
{
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
}*/


PlayerSelectMenuView::~PlayerSelectMenuView()
{
	if (game)
	{
		delete game;
		game = 0;
	}
}