#include "Warrior.h"

void Warrior::LoadCombatActions()
{
	CombatActions.push_back("Melee");
	CombatActions.push_back("Range");
	CombatActions.push_back("Cut");
	CombatActions.push_back("Crush");
}

void Warrior::TakeDamage(int dmg)
{
	int damageToTake = dmg - PlayerStats["armour"];
	if (damageToTake < 1) {
		damageToTake = 1;
	}
	CurrentHealth -= damageToTake;
}

int Warrior::MeleeAttack()
{
	return PlayerStats["dmg"];
}

int Warrior::RangeAttack()
{
	return 0;
}

int Warrior::ElementalAttack()
{
	return 0;
}

int Warrior::CutAttack()
{
	return 0;
}

int Warrior::CrushAttack()
{
	return 0;
}
