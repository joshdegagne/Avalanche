#include "EntityBase.h"

EntityBase::EntityBase() : type(EntityType::DEFAULT_ENTITY) {}

EntityType EntityBase::getEntityType() { return type; }