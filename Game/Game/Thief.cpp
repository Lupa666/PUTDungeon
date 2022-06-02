#include "Thief.h"

void Thief::LoadCombatActions()
{
	CombatActions.push_back("Melee");
	CombatActions.push_back("Range");
	CombatActions.push_back("Cut");
}

void Thief::TakeDamage(int dmg)
{
	CurrentHealth -= dmg;
}

int Thief::MeleeAttack()
{
	return PlayerStats["dmg"];
}

int Thief::RangeAttack()
{
	if (CurrentAmmo < 1 or CurrentStamina < PlayerStats["rangecost"]) {
		return 0;
	}
	CurrentAmmo--;
	CurrentStamina -= PlayerStats["rangecost"];
	return PlayerStats["dmgrange"];
}

int Thief::ElementalAttack()
{
	if (CurrentStamina < PlayerStats["elemcost"] or CurrentAmmo <= 0) {
		return 0;
	}
	CurrentAmmo--;
	CurrentStamina -= PlayerStats["elemcost"];
	return PlayerStats["dmgrange"] * PlayerStats["elem"];
}

int Thief::CutAttack()
{
	if (CurrentStamina < PlayerStats["elemcost"]) {
		return 0;
	}
	CurrentStamina -= PlayerStats["elemcost"];
	return PlayerStats["dmgrange"] * PlayerStats["elem"];
}
