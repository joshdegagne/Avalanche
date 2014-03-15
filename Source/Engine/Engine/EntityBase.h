#pragma once

#include "EntityType.h"

class EntityBase {
public:
	EntityBase();

	EntityType getEntityType();

protected:
	EntityType	 type;

private:

};