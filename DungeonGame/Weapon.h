#ifndef _Weapon_included_
#define _Weapon_included_

#include "Equipment.h"

class Weapon :
	public Equipment
{
public:
	Weapon(void);
	virtual ~Weapon(void);

	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeFragment(std::ostream & output);
	virtual void writeDataAsFragment(std::ostream & output);
	virtual void setElementData(std::string sElementName, std::string sValue);

	virtual int getAttackBonus();
	virtual void setAttackBonus(int iAttackBonus);
	virtual int getWeaponType();
	virtual void setWeaponType(int iWeaponType);

private:
	int m_iAttackBonus;
	int m_iWeaponType;
};


#endif