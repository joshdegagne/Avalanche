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
#include "CreditsMenu.h"

class Game;
class CreditsMenu;
class TextureManager;

using namespace DirectX;

class CreditsMenuView
{
public:
	CreditsMenuView(Game& game); // Initialize SpriteBatch with device context (every menu ViewModel will do this)
	bool Draw(CreditsMenu*);

private:
	Game*	game;
};