#pragma once
#include "AbilityInterface.h"
#include <iostream>

class SpecialAbilityComponent : public AbilityInterface
{
private:

	float m_duration;

public:
	static const char *g_Name;
	virtual const char *VGetName() const { return g_Name; }

	//Class Functions
	virtual void VActivateAbility();

	//Base Inherited Functions
	virtual bool VInit() override;
};

