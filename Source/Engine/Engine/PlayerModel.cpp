#include "GameModel.h"
#include "Model.h"
#include "QuadTexturedModel.h"
#include "PlayerModel.h"

PlayerModel::PlayerModel(float lengthX, float lengthY, WCHAR* aTextureFileName) : QuadTexturedModel(lengthX, lengthY, aTextureFileName)
{
	// create quadtexturedmodel and orient it to face camera (locally, not globally)
}

PlayerModel::~PlayerModel(void)
{
}

void PlayerModel::Shutdown()
{
}