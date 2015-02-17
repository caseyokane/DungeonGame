#include "Player.h"

#include <cstdlib>
#include <iostream>
#include <sstream>

using namespace std;

Player::Player()
{
	m_iExperience = 0;
	m_iLevel = 1;
	m_iAttack = 2;
}

int Player::getExperience()
{
	return m_iExperience;
}

void Player::setExperience(int iExperience)
{
	m_iExperience = iExperience;
}

int Player::getLevel()
{
	return m_iLevel;
}

void Player::setLevel(int iLevel)
{
	m_iLevel = iLevel;
}

int Player::getAttack()
{
	return m_iAttack;
}

void Player::setAttack(int iAttack)
{
	m_iAttack = iAttack;
}

bool Player::attack(Creature * oCreature, vector<string>& vStrings)
{

	//first get the current health of the target
	int iTargetHP = oCreature->getHealth();
	//cout << "Creature HP: " << iTargetHP << endl;
	//find attack value
	int iAttack = getAttack();

	//Subtract health of target by attack value
	iTargetHP -= iAttack;

	string cName = oCreature->getName();
	int cHP = oCreature->getHealth();
	stringstream ssConv;
	ssConv.str("");


	if(iTargetHP > 0)
	{
		//cout << oCreature->getName() << " was attacked, for " << iAttack <<  " damage!" << endl;
		//cout << oCreature->getName() << " has " <<  oCreature->getHealth() << " Health!" << endl;
		ssConv << iAttack;
		string sAttack = ssConv.str();
		ssConv.str("");

		ssConv << cHP;
		string sHP = ssConv.str();


		vStrings.push_back(cName + " was attacked, for " + sAttack + " damage! 	" + cName + " has " + sHP + " health.");



		oCreature->setHealth(iTargetHP);

		return false;
	}

	else
	{
		//cout << oCreature->getName() << " was killed!	5 XP Earned" << endl;
		vStrings.push_back(cName + " was killed! 5 XP Earned.");
		return true;
	}


}

//XML
void Player::dumpObjectData()
{
	Character::dumpObjectData();

	cout << "	[Experience]  " << getExperience() << endl;
	cout << "	[Level] " << getLevel() << endl;
}

void Player::dumpObject()
{
	cout << "Player:" << endl;

	dumpObjectData();
}

void Player::writeDataAsFragment(ostream & output)
{

	Character::writeDataAsFragment(output);

	output << "	<experience>"
		<< getExperience()
		<< "</experience>"
		<< endl
		<<" 	<level>"
		<< getLevel()
		<< "</level>"
		<< endl;

}

void Player::writeFragment(ostream & output)
{
	cout << " <Player>" << endl;

	writeDataAsFragment(output);

	cout << " </Player>" << endl;
}

void Player::setElementData(string sElementName, string sValue)
{
	Character::setElementData(sElementName, sValue);

	if((sElementName == "Experience")||(sElementName == "experience"))
	{
		m_iExperience = atoi(sValue.c_str());
	}

	if((sElementName == "Level")||(sElementName == "level"))
	{
		m_iLevel == atoi(sValue.c_str());
	}
}
