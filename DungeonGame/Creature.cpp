#include "Creature.h"

#include <cstdlib>
#include <iostream>


using namespace std;

Creature::Creature(void)
{
	m_bHostile = true;
}


Creature::~Creature(void)
{
}


void Creature::dumpObject()
{
	cout << "Creature:" << endl;
	dumpObjectData();
}

void Creature::dumpObjectData()
{
	Character::dumpObjectData();

	cout << "       [Hostile] " << (isHostile() ? "true" : "false") << endl;
}

void Creature::writeFragment(ostream & output)
{
	output << "   <Creature>" << endl;
	writeDataAsFragment(output);
	output << "   </Creature>" << endl;
}

void Creature::writeDataAsFragment(ostream & output)
{
	Character::writeDataAsFragment(output);

	output << "      <hostile>" << (isHostile() ? "true" : "false") << "</hostile>" << endl;

}

void Creature::setElementData(string sElementName, string sValue)
{
	Character::setElementData(sElementName, sValue);

	if( sElementName == "hostile" )
	{
		if( sValue == "true" )
		{
			setHostile(true);
		}
		else if( sValue == "false" )
		{
			setHostile(false);
		}
	}

}

bool Creature::isHostile()
{
	return m_bHostile;
}

void Creature::setHostile(bool bHostile)
{
	m_bHostile = bHostile;
}

int Creature::attack(int iPlayerHP)
{
	int iTargetHP = iPlayerHP;
	int iAttack = 4;

	iTargetHP -= iAttack;

	return iTargetHP;


}

