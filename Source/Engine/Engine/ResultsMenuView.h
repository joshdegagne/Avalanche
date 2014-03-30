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
class ResultsMenu;

class ResultsMenuView
{
public:
	ResultsMenuView(Game& game); // Initialize SpriteBatch with device context (every menu ViewModel will do this)
	~ResultsMenuView();
	bool Draw(ResultsMenu*);

private:
	Game* game;
};