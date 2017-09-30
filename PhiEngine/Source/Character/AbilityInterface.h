#pragma once
#include "ActorComponent.h"

class AbilityInterface : public ActorComponent
{
public:
	const static ComponentId COMPONENT_ID;

	virtual ComponentId VGetComponentID(void) const
	{
		return COMPONENT_ID;
	}

	virtual void VActivateAbility() = 0;

private:

protected:

};