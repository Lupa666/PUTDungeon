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
	if (CurrentAmmo < 1 and CurrentStamina < PlayerStats["rangecost"]) {
		return 0;
	}
	CurrentAmmo--;
	CurrentStamina -= PlayerStats["rangecost"];
	return PlayerStats["dmgrange"];
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
