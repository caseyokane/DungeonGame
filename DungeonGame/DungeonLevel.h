#ifndef _DungeonLevel_included_
#define _DungeonLevel_included_

#include <vector>
#include <random>
#include <string>

#include "Entity.h"
#include "Player.h"
#include "Armor.h"
#include "Weapon.h"
#include "Creature.h"
#include "Item.h"

class DungeonLevel
{
public:
	DungeonLevel(int iWidth, int iHeight, std::mt19937 & mt);
	~DungeonLevel(void);

	void dump();
	char at(int x, int y);

	int getWidth();
	int getHeight();
	virtual std::vector<Item*> getInventory();

	virtual bool locateEntity(int YCoord, int XCoord);
	virtual std::vector<int> findChar(char cInput);
	virtual std::vector<int> findCoords(std::string sObject, int iItemCtr);
	virtual std::vector<int> findCreatureCoords(Player * oPlayer, char cUserChar);

	virtual std::string replaceItem(std::string sType, std::string sName, int itemCount);
	virtual void dropItem(int iYCoord, int iXCoord, int iNum);

	virtual Creature * findCreature(Player * oPlayer, char cInput);

	virtual void generateObjects(int iNum_Items, std::string sObject_type, bool isInventory);

	virtual bool movementValid(int iPXcoord, int iPYCoord, char cDirection);
	virtual bool adjObject(Player * oPlayer, int YCoord, int XCoord); 
	virtual bool movementAttack(Player * oPlayer, char cUserChar);
	virtual bool ObjectPosComp(int YCoord, int XCoord);

	virtual void moveCreature(Player * oPlayer);

	virtual bool PlayerAttack(Player * oPlayer, char cUserChar, std::vector<std::string>& vStrings);
	virtual void CreatureAttack(Player * oPlayer, char cUserChar, std::vector<std::string>& vStrings);
	virtual int usePotion(Player * oPlayer, int iMaxHP, bool isHealthy);


	virtual void placePlayer(Player * oPlayer, bool isPlaced, bool isReturn, char iMovement);
	virtual void placeObjects(std::mt19937 & mt, bool newCritter);

	virtual std::vector<std::vector<char>>  displayDungeon(Player * oPlayer);


private:
	std::vector<std::vector<char>> m_vvTiles;
	std::vector<std::vector<char>> m_vvDisplayDungeon;

	//std::vector<Item*> vItems;
	std::vector<Creature*> vCreatures;
	std::vector<Entity*> vConsumables;
	std::vector<Armor*> vArmor;
	std::vector<Weapon*> vWeapons;

	std::vector<Item*> vInventory;

};

#endif
