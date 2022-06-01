#include "Thief.h"

void Thief::LoadCombatActions()
{
	CombatActions.push_back("Melee");
	CombatActions.push_back("Range");
	CombatActions.push_back("Cut");
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
