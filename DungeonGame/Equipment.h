#ifndef _Equipment_included_
#define _Equipment_included_

#include "Item.h"

#include <string>

class Equipment :
	public Item
{
public:
	Equipment(void);
	virtual ~Equipment(void);

	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeFragment(std::ostream & output);
	virtual void writeDataAsFragment(std::ostream & output);
	virtual void setElementData(std::string sElementName, std::string sValue);

	virtual std::string getSlot();
	virtual void setSlot(std::string sSlot);

private:
	std::string m_sSlot;

};

#endif