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
	if (CurrentStamina < PlayerStats["elemcost"]) {
		return 0;
	}
	CurrentStamina -= PlayerStats["elemcost"];
	return PlayerStats["dmgrange"]*PlayerStats["elem"];
}

int Warrior::CutAttack()
{
	if (CurrentStamina < PlayerStats["cietycost"]) {
		return 0;
	}
	CurrentStamina -= PlayerStats["cietycost"];
	return PlayerStats["dmg"] * PlayerStats["ciety"];
}

int Warrior::CrushAttack()
{
	if (CurrentStamina < PlayerStats["obuchowycost"]) {
		return 0;
	}
	CurrentStamina -= PlayerStats["obuchowycost"];
	return PlayerStats["dmg"] * PlayerStats["obuchowycost"];
}
