#ifndef _GenericFactory_included_
#define _GenericFactory_included_


#include "Item.h"
#include "Creature.h"
#include "Armor.h"
#include "Weapon.h"
#include "EntityVector.h"

#include <vector>

class GenericFactory
{
public:	
	static GenericFactory & instance();
	virtual ~GenericFactory();
	Creature  * generateCreature(int iMaxHealth);
	Item * generateItem();
	Armor * generateArmor();
	Weapon * generateWeapon();

private:
	GenericFactory();
	EntityVector<Creature>  m_vCreatures;
	EntityVector<Item> m_vItems;
	EntityVector<Armor> m_vArmor;
	EntityVector<Weapon> m_vWeapons;
};

#endif
