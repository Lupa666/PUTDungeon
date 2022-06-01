#include "Mage.h"

void Mage::LoadCombatActions()
{
	CombatActions.push_back("Melee");
	CombatActions.push_back("Range");
}

void Mage::TakeDamage(int dmg)
{
	CurrentHealth -= dmg;
}

int Mage::MeleeAttack()
{
	return PlayerStats["dmg"];
}

int Mage::RangeAttack()
{
	if (CurrentAmmo < 1 and CurrentStamina < PlayerStats["rangecost"]) {
		return 0;
	}
	CurrentAmmo--;
	CurrentStamina -= PlayerStats["rangecost"];
	return PlayerStats["dmgrange"];
}

int Mage::ElementalAttack()
{
	if (CurrentStamina < PlayerStats["elemcost"]) {
		return 0;
	}
	CurrentStamina -= PlayerStats["elemcost"];
	return PlayerStats["dmgrange"] * PlayerStats["elem"];
}
