#pragma once

#include "robot.h"

class CollisionManager
{
public:
	CollisionManager(void);
	~CollisionManager(void);

	void	MoveIfNotColliding(Robot* a, Robot* b, void (Robot::*FuncPtr)(void));
	bool	AreColliding(Robot* a, Robot* b);
};

