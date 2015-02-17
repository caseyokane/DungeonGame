#include "Item.h"

#include <cstdlib>

using namespace std;

Item::Item(void)
{
	m_iValue = 0;
	m_iWeight = 0;
}


Item::~Item(void)
{
}

void Item::dumpObject()
{
	cout << "Item:" << endl;
	dumpObjectData();
}

void Item::dumpObjectData()
{
	Entity::dumpObjectData();

	cout << "        [Weight] " << getWeight() << endl;
	cout << "         [Value] " << getValue() << endl;

}

void Item::writeFragment(ostream & output)
{
	output << "   <Item>" << endl;
	writeDataAsFragment(output);
	output << "   </Item>" << endl;
}

void Item::writeDataAsFragment(ostream & output)
{
	Entity::writeDataAsFragment(output);

	output << "      <weight>" << getWeight() << "</weight>" << endl;
	output << "      <value>" << getValue() << "</value>" << endl;
}

void Item::setElementData(string sElementName, string sValue)
{
	Entity::setElementData(sElementName, sValue);

	if( sElementName == "weight" )
	{
		setWeight(atoi(sValue.c_str()));
	}
	else if( sElementName == "value" )
	{
		setValue(atoi(sValue.c_str()));
	}
}




int Item::getWeight() 
{ 
	return m_iWeight;
}

void Item::setWeight(int iWeight)
{ 
	m_iWeight = iWeight;
}

int Item::getValue()
{
	return m_iValue;
}

void Item::setValue(int iValue) 
{ 
	m_iValue = iValue;
}


