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

		
		// From the original 800x600 positions to 1366x768
		// Can be refactored to use inheritance and be dynamic to whatever the screen dimensions are
		float resolutionWidthOffset = 283.0f;
		float resolutionHeightOffset = 84.0f;
		
		game->getGraphics()->getSpriteFontBig()->DrawString(game->getGraphics()->getSpriteBatch(), L"AVALANCHE", XMFLOAT2(MENU_TITLE_X, MENU_TITLE_Y), Colors::Purple); // 75?

		//game->getGraphics()->getSpriteFontNormal()->DrawString(spriteBatch, L"players", XMFLOAT2(315, 155), Colors::Purple);
		game->getGraphics()->getSpriteFontNormal()->DrawString(spriteBatch, L"PLAYERS", XMFLOAT2(315.0f + resolutionWidthOffset, 153.0f + resolutionHeightOffset), Colors::Purple);

		//spriteFontBig->DrawString(spriteBatch, L"1", XMFLOAT2(373, 200), Colors::Silver);


		spriteFontBig->DrawString(spriteBatch, L"2", XMFLOAT2(372.0f + resolutionWidthOffset, 210.0f + resolutionHeightOffset), Colors::Silver);
		spriteFontBig->DrawString(spriteBatch, L"3", XMFLOAT2(372.0f + resolutionWidthOffset, 270.0f + resolutionHeightOffset), Colors::Silver);
		spriteFontBig->DrawString(spriteBatch, L"4", XMFLOAT2(372.0f + resolutionWidthOffset, 330.0f + resolutionHeightOffset), Colors::Silver);

		spriteFontNormal->DrawString(spriteBatch, L"player", XMFLOAT2(25.0f + resolutionWidthOffset, 450.0f + resolutionHeightOffset), Colors::DarkRed);
		spriteFontBig->DrawString(spriteBatch, L"1", XMFLOAT2(70.0f + resolutionWidthOffset, 500.0f + resolutionHeightOffset), Colors::DarkRed);

		switch(menu->getCurrentSelection())
		{
		case 0: spriteFontBig->DrawString(spriteBatch, L"2", XMFLOAT2(372.0f + resolutionWidthOffset, 210.0f + resolutionHeightOffset), Colors::Purple); 
				spriteFontNormal->DrawString(spriteBatch, L"player", XMFLOAT2(225.0f + resolutionWidthOffset, 450.0f + resolutionHeightOffset), Colors::DarkSlateBlue);
				spriteFontBig->DrawString(spriteBatch, L"2", XMFLOAT2(270.0f + resolutionWidthOffset, 500.0f + resolutionHeightOffset), Colors::DarkSlateBlue);
				break;
		case 1: spriteFontBig->DrawString(spriteBatch, L"3", XMFLOAT2(372.0f + resolutionWidthOffset, 270.0f + resolutionHeightOffset), Colors::Purple); 
				spriteFontNormal->DrawString(spriteBatch, L"player", XMFLOAT2(225.0f + resolutionWidthOffset, 450.0f + resolutionHeightOffset), Colors::DarkSlateBlue);
				spriteFontBig->DrawString(spriteBatch, L"2", XMFLOAT2(270.0f + resolutionWidthOffset, 500.0f + resolutionHeightOffset), Colors::DarkSlateBlue);
				spriteFontNormal->DrawString(spriteBatch, L"player", XMFLOAT2(425.0f + resolutionWidthOffset, 450.0f + resolutionHeightOffset), Colors::DarkOliveGreen);
				spriteFontBig->DrawString(spriteBatch, L"3", XMFLOAT2(470.0f + resolutionWidthOffset, 500.0f + resolutionHeightOffset), Colors::DarkOliveGreen);
				break;
		case 2: spriteFontBig->DrawString(spriteBatch, L"4", XMFLOAT2(372.0f + resolutionWidthOffset, 330.0f + resolutionHeightOffset), Colors::Purple); 
				spriteFontNormal->DrawString(spriteBatch, L"player", XMFLOAT2(225.0f + resolutionWidthOffset, 450.0f + resolutionHeightOffset), Colors::DarkSlateBlue);
				spriteFontBig->DrawString(spriteBatch, L"2", XMFLOAT2(270.0f + resolutionWidthOffset, 500.0f + resolutionHeightOffset), Colors::DarkSlateBlue);
				spriteFontNormal->DrawString(spriteBatch, L"player", XMFLOAT2(425.0f + resolutionWidthOffset, 450.0f + resolutionHeightOffset), Colors::DarkOliveGreen);
				spriteFontBig->DrawString(spriteBatch, L"3", XMFLOAT2(470.0f + resolutionWidthOffset, 500.0f + resolutionHeightOffset), Colors::DarkOliveGreen);
				spriteFontNormal->DrawString(spriteBatch, L"player", XMFLOAT2(625.0f + resolutionWidthOffset, 450.0f + resolutionHeightOffset), Colors::Purple);
				spriteFontBig->DrawString(spriteBatch, L"4", XMFLOAT2(670.0f + resolutionWidthOffset, 500.0f + resolutionHeightOffset), Colors::Purple);
				break;
		}

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