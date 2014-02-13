#include "Player.h"

Player::Player(Game& g, int pNum) : Entity(), playerNum(pNum)
{
	controller = g.getControllerManager();
}

void Player::update(float elapsed)
{
}