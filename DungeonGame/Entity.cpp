#include "Entity.h"

#include <vector>

using namespace std;

Entity::Entity(void)
{
	m_cSymbol = '?';
}


Entity::~Entity(void)
{
}


void Entity::dumpObject()
{
	cout << "Entity:" << endl;
	dumpObjectData();
}

void Entity::dumpObjectData()
{
	XMLSerializable::dumpObjectData();

	cout << "          [Name] " << getName() << endl;
	cout << "        [Symbol] " << getSymbol() << endl;
}

void Entity::writeFragment(ostream & output)
{
	output << "   <Entity>" << endl;
	writeDataAsFragment(output);
	output << "   </Entity>" << endl;
}

void Entity::writeDataAsFragment(ostream & output)
{
	XMLSerializable::writeDataAsFragment(output);

	output << "      <name>" << getName() << "</name>" << endl;
	output << "      <symbol>" << getSymbol() << "</symbol>" << endl;
}

void Entity::setElementData(string sElementName, string sValue)
{
	XMLSerializable::setElementData(sElementName, sValue);


	if( sElementName == "name" )
	{
		setName(sValue);
	}
	else if( sElementName == "symbol" )
	{
		if( sValue.length() > 0 )
			setSymbol(sValue[0]);
	}
}

string Entity::getName()
{
	return m_sName;
}

void Entity::setName(string sName)
{
		m_sName = sName;
}

char Entity::getSymbol()
{
	return m_cSymbol;
}

void Entity::setSymbol(char cSymbol)
{
	m_cSymbol = cSymbol;
}


int Entity::getXCoord()
{
	return Xcoord;
}

int Entity::getYCoord()
{
	return Ycoord;
}

void Entity::setCoord(int y, int x)
{
	Xcoord = x;
	Ycoord = y;
}
