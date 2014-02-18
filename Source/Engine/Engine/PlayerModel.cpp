#include "GameModel.h"
#include "Model.h"
#include "QuadModel.h"
#include "PlayerModel.h"

PlayerModel::PlayerModel(float lengthX, float lengthY, XMFLOAT4 * pColor) : QuadModel(lengthX, lengthY, pColor)
{
}

PlayerModel::~PlayerModel(void)
{
}

void PlayerModel::Shutdown()
{
}