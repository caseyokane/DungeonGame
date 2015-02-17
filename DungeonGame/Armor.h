#ifndef _Armor_included_
#define _Armor_included_

#include "Equipment.h"

class Armor :
	public Equipment
{
public:
	Armor(void);
	virtual ~Armor(void);

	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeFragment(std::ostream & output);
	virtual void writeDataAsFragment(std::ostream & output);
	virtual void setElementData(std::string sElementName, std::string sValue);

	virtual int getDefenseBonus();
	virtual void setDefenseBonus(int iDefenseBonus);

private:
	int m_iDefenseBonus;
};


#endif