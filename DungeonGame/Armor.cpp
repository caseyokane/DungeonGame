#include "Armor.h"

#include <cstdlib>

using namespace std;

Armor::Armor(void)
{
	m_iDefenseBonus = 0;
}


Armor::~Armor(void)
{
}

void Armor::dumpObject()
{
	cout << "Armor:" << endl;
	dumpObjectData();
}

void Armor::dumpObjectData()
{
	Equipment::dumpObjectData();

	cout << "  [DefenseBonus] " << getDefenseBonus() << endl;

}

void Armor::writeFragment(ostream & output)
{
	output << "   <Armor>" << endl;
	writeDataAsFragment(output);
	output << "   </Armor>" << endl;
}

void Armor::writeDataAsFragment(ostream & output)
{
	Equipment::writeDataAsFragment(output);

	output << "      <defenseBonus>" << getDefenseBonus() << "</defenseBonus>" << endl;

}

void Armor::setElementData(string sElementName, string sValue)
{
	Equipment::setElementData(sElementName, sValue);

	if( sElementName == "defenseBonus" )
	{
		setDefenseBonus(atoi(sValue.c_str()));
	}

}

int Armor::getDefenseBonus()
{
	return m_iDefenseBonus;
}

void Armor::setDefenseBonus(int iDefenseBonus)
{
	m_iDefenseBonus = iDefenseBonus;
}




