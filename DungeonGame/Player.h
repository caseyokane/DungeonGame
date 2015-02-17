#ifndef _Player_included_
#define _Player_included_

#include "Character.h"
#include "Creature.h"
#include <fstream>
#include <vector>

class Player : public Character
{
public:
	Player();
	int getExperience();
	void setExperience(int iExperience);
	int getLevel();
	void setLevel(int iLevel);
	int getAttack();
	void setAttack(int iAttackValue);

	virtual bool attack(Creature * oCreature, std::vector<std::string>& vStrings);

	virtual void dumpObjectData();
	virtual void dumpObject();
	virtual void writeFragment(std::ostream & output);
	virtual void writeDataAsFragment(std::ostream & output);
	virtual void setElementData(std::string sElementName, std::string sValue);

private:
	int m_iExperience;
	int m_iLevel;
	int m_iAttack;
};

#endif

