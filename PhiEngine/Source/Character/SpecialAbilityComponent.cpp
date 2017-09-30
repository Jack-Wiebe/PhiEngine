#include "SpecialAbilityComponent.h"

const char* SpecialAbilityComponent::g_Name = "SpecialAbility";

void SpecialAbilityComponent::VActivateAbility()
{
	std::cout << "Activate ability for duration of " << m_duration << " seconds" << std::endl;
};

bool SpecialAbilityComponent::VInit()
{
	return true;
}