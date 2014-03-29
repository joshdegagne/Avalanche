#pragma once

#include "ViewModel.h"
#include "SpriteBatch.h"
#include "TextureShader.h"
#include "SpriteFont.h"
#include "EntityType.h"
#include "GeometricPrimitive.h"
#include "CommonStates.h"
#include "ColorShader.h"
#include "PrimitiveBatch.h"
#include "Effects.h"
#include "VertexTypes.h"

class Game;
class PlayerSelectMenu;
class TextureManager;

using namespace DirectX;

class PlayerSelectMenuView
{
public:
	PlayerSelectMenuView(Game& game); // Initialize SpriteBatch with device context (every menu ViewModel will do this)
	~PlayerSelectMenuView();
	bool Draw(PlayerSelectMenu*);

private:
	Game* game;

	/*
	std::unique_ptr<BasicEffect>                            batchEffect;
	std::unique_ptr<GeometricPrimitive>                     shape;
	std::unique_ptr<PrimitiveBatch<VertexPositionColor>>    batch;
	std::unique_ptr<SpriteFont>                             font;
	SpriteBatch*				                            sprites;
	Game*													game;
	*/
};