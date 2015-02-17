#include "GenericFactory.h"

#include <map>
#include <random>
#include <ctime>

#include "parser.h"


#include "Player.h"
#include "Armor.h"
#include "Weapon.h"
#include "Creature.h"
#include "Consumable.h"
#include "Item.h"
#include "Tools.h"
#include "Character.h"

using namespace std;


GenericFactory & GenericFactory::instance()
{
	static GenericFactory factory;
	return factory;
}

GenericFactory::GenericFactory()
{
	map<string, function<XMLSerializable*()>> mConstructors;
	mConstructors["Player"] = []() { return new Player; };
	mConstructors["Item"] = []() { return new Item; };
	mConstructors["Consumable"] = []() { return new Consumable; };
	mConstructors["Creature"] = []() { return new Creature; };
	mConstructors["Weapon"] = []() { return new Weapon; };
	mConstructors["Armor"] = []() { return new Armor; };
	mConstructors["Character"] = []() { return new Character; };

	vector<XMLSerializable*> vObjects;

    parseXML(mConstructors, "world.xml", vObjects);

	m_vCreatures.constructVector(vObjects);
	m_vItems.constructVector(vObjects);
	m_vArmor.constructVector(vObjects);
	m_vWeapons.constructVector(vObjects);
}

GenericFactory::~GenericFactory()
{
}


Creature * GenericFactory::generateCreature(int iMaxHealth)
{
	return m_vCreatures.generate( [=](Creature * pCreature) { return pCreature->getHealth() < iMaxHealth; });
}


Item * GenericFactory::generateItem()
{
	return m_vItems.generate([](Item * pItem) { return true; });
}


Armor * GenericFactory::generateArmor()
{
	return m_vArmor.generate( [=] (Armor * pArmor) { return true; });
}

Weapon * GenericFactory::generateWeapon()
{
	return m_vWeapons.generate( [=] (Weapon * pWeapon) { return true; });
}
