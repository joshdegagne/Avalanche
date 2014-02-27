
#include "ViewModelBase.h"

ViewModelBase::ViewModelBase(EntityType entityType)
{
	associatedEntity = entityType;
}

/*	GetAssociatedType
 *	==================================================
 *		Returns the EntityType associated with this
 *	ViewModel.
 */
EntityType ViewModelBase::GetAssociatedType()
{
	return associatedEntity;
}