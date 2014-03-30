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
#include "ControlsMenu.h"

class Game;
class ControlsMenu;
class TextureManager;

using namespace DirectX;

class ControlsMenuView
{
public:
	ControlsMenuView(Game& game); // Initialize SpriteBatch with device context (every menu ViewModel will do this)
	bool Draw(ControlsMenu*);

private:
	Game*	game;
};