#ifndef _Consumable_included_
#define _Consumable_included_

#include "Item.h"
#include "Character.h"

class Consumable :
	public Item
{
public:
	Consumable(void);
	virtual ~Consumable(void);


	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeFragment(std::ostream & output);
	virtual void writeDataAsFragment(std::ostream & output);
	virtual void setElementData(std::string sElementName, std::string sValue);

	virtual void use(Character & user);

	virtual int getQuantity();
	virtual void setQuantity(int iQuantity);

private:
		int m_iQuantity;
};

#endif