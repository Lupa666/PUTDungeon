#include "Mage.h"

void Mage::LoadCombatActions()
{
	CombatActions.push_back("Melee");
	CombatActions.push_back("Range");
}

void Mage::TakeDamage(int dmg)
{
}

int Mage::MeleeAttack()
{
	return 0;
}

int Mage::RangeAttack()
{
	return 0;
}

int Mage::ElementalAttack()
{
	return 0;
}
