#include "Archer.h"


void Archer::LoadCombatActions()
{
	CombatActions.push_back("Range");
	CombatActions.push_back("Melee");
}

void Archer::TakeDamage(int dmg)
{
}

int Archer::MeleeAttack()
{
	return 0;
}

int Archer::RangeAttack()
{
	return 0;
}

int Archer::ElementalAttack()
{
	return 0;
}
