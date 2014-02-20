#include "GameModel.h"
#include "Model.h"
#include "QuadTexturedModel.h"
#include "PlayerModel.h"

PlayerModel::PlayerModel(float lengthX, float lengthY, WCHAR* aTextureFileName) : QuadTexturedModel(lengthX, lengthY, aTextureFileName)
{
	// create quadtexturedmodel and orient it to face camera (locally, not globally)

	// test hardcoding orientation to face camera - need to fix to use camera information (projection or view matrix?)
	orientRotateZ(-XM_PIDIV2); // test
	orientRotateY(XM_PIDIV4/2); // test
	//orientRotateX(XM_PIDIV4); // test

	//worldTranslate
}


/*
PlayerModel::~PlayerModel(void)
{
}

void PlayerModel::Shutdown()
{
}*/