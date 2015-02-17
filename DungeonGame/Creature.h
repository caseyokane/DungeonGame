#ifndef _Creature_included_
#define _Creature_included_

#include "Character.h"

class Creature :
	public Character
{
public:
	Creature(void);
	virtual ~Creature(void);

	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeFragment(std::ostream & output);
	virtual void writeDataAsFragment(std::ostream & output);
	virtual void setElementData(std::string sElementName, std::string sValue);


	virtual bool isHostile();
	virtual void setHostile(bool bHostile);

	virtual int attack(int iPlayerHP);

private:
	bool m_bHostile;


};

#endif

