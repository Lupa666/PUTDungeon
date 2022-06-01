#include "Archer.h"


void Archer::LoadCombatActions()
{
	CombatActions.push_back("Melee");
	CombatActions.push_back("Range");
}

void Archer::TakeDamage(int dmg)
{
	CurrentHealth -= dmg;
}

int Archer::MeleeAttack()
{
	return PlayerStats["dmg"];
}

int Archer::RangeAttack()
{
	if (CurrentAmmo < 1 and CurrentStamina < PlayerStats["rangecost"]) {
		return 0;
	}
	CurrentAmmo--;
	CurrentStamina -= PlayerStats["rangecost"];
	return PlayerStats["dmgrange"];
}

int Archer::ElementalAttack()
{
	if (CurrentStamina < PlayerStats["elemcost"]) {
		return 0;
	}
	CurrentStamina -= PlayerStats["elemcost"];
	return PlayerStats["dmgrange"] * PlayerStats["elem"];
}
