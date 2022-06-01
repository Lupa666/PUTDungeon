#include "Thief.h"

void Thief::LoadCombatActions()
{
	CombatActions.push_back("Cut");
	CombatActions.push_back("Range");
	CombatActions.push_back("Melee");
}

void Thief::TakeDamage(int dmg)
{
}

int Thief::MeleeAttack()
{
	return 0;
}

int Thief::RangeAttack()
{
	return 0;
}

int Thief::ElementalAttack()
{
	return 0;
}

int Thief::CutAttack()
{
	return 0;
}
