#include "Character.h"
#include "Item.h"


#include <cstdlib>

using namespace std;

Character::Character(void)
{
	m_iHealth = 10;
}


Character::~Character(void)
{
}


void Character::dumpObject()
{
	cout << "Character:" << endl;
	dumpObjectData();
}

void Character::dumpObjectData()
{
	Entity::dumpObjectData();

	cout << "        [Health] " << getHealth() << endl;
}

void Character::writeFragment(ostream & output)
{
	output << "   <Character>" << endl;
	writeDataAsFragment(output);
	output << "   </Character>" << endl;
}

void Character::writeDataAsFragment(ostream & output)
{
	Entity::writeDataAsFragment(output);

	output << "      <health>" << getHealth() << "</health>" << endl;

}

void Character::setElementData(string sElementName, string sValue)
{
	Entity::setElementData(sElementName, sValue);

	if( sElementName == "health" )
	{
		setHealth(atoi(sValue.c_str()));
	}

}



int Character::getHealth()
{
	return m_iHealth;
}

void Character::setHealth(int iHealth)
{
	m_iHealth = iHealth;
}

vector<Item*> Character::getInventory()
{
	return vInventory;
}

void Character::setInventory(Item * oItem, bool bSwap)
{
	vInventory.push_back(oItem);
	if(bSwap == true)
	{
		Item * oTemp = vInventory[0];
		Item * oTemp2 = vInventory[1];

		vInventory.pop_back();
		vInventory.pop_back();

		vInventory.push_back(oTemp2);
		vInventory.push_back(oTemp);
	}
}

void Character::eraseInventory(int iPos)
{
	/*
	for(int ctr = 0; ctr < vInventory.size(); ctr++)
	{
		vInventory.pop_back();
	}
	*/

	vInventory.erase(vInventory.begin() + iPos);
}

void Character::attack(Character & target)
{

	//target is a reference to a Character object
	//First, get it's current health.
	//int iTargetHP = target.getHealth();

	//Second get the attack bonus from the attacking creature
	/*

	if(attacker.weaponbonus > 0)
	{
		int iAttack_value = attacker.weaponBounus()
	}

	*/


	//Get Armor Bonus from target creature
	/*

	if(target.armorValue() > 0)
	{
		int iDefense_value = target.getDefenseBonus();
	}

	*/


	//get attack value from subtracting the two previous ints

	//iAttackValue -= iDfense_value;

	//Subtract this int from iTargetHP
	//iTargetHP -= iAttackValue;

	//Set this as the new target HP
	//target.setHealth(iTargetHP)
 

}
