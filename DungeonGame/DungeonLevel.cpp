#include <iostream>
#include <random>
#include <vector>
#include <string>


#include "DungeonLevel.h"
#include "Entity.h"
#include "GenericFactory.h"


using namespace std;



DungeonLevel::DungeonLevel(int iWidth, int iHeight, std::mt19937 & mt)
{
	// Initialize the blank vector
	m_vvTiles.resize(iHeight);

	for(auto it = m_vvTiles.begin();
		it != m_vvTiles.end();
		it++ )
	{
		(*it).resize(iWidth, ' ');
	}

	// We're going to divide the level into 4x2 chunks
	int iChunkWidth = iWidth / 4;
	int iChunkHeight = iHeight / 2;


	// The strategy here is to first draw a loop of tunnels on
	// the level, and then draw rooms on top of them.

	// Taking the easy way out, and generating
	// a loop of tunnels first to drop rooms on to
	for( int x = (iChunkWidth/2); x <= ((3 * iChunkWidth) + (iChunkWidth/2)); x++ )
	{
		m_vvTiles[iChunkHeight/2][x] = '#';
		m_vvTiles[iChunkHeight + (iChunkHeight/2)][x] = '#';
	}

	for( int y = (iChunkHeight/2); y <= (iChunkHeight + (iChunkHeight/2)); y++ )
	{
		m_vvTiles[y][iChunkWidth/2] = '#';
		m_vvTiles[y][(3 * iChunkWidth) + (iChunkWidth/2)] = '#';
	}

	// Pick rooms for the up and down stairs
	int iUpXChunk = mt() % 4;
	int iUpYChunk = mt() % 2;

	int iDownXChunk = mt() % 4;
	int iDownYChunk = mt() % 2;

	// Put them in different rooms...

	while( iUpXChunk == iDownXChunk && iUpYChunk == iDownYChunk )
	{
		iDownXChunk = mt() % 4;
		iDownYChunk = mt() % 2;
	}


	// So then we iterate through the chunks, and we
	// have individual blocks of the level which don't
	// overlap, so we're going to drop a room on each one.

	for( int iXChunk = 0; iXChunk < 4; iXChunk++ )
	{
		int iXStart = iXChunk * iChunkWidth;

		for( int iYChunk = 0; iYChunk < 2; iYChunk++ )
		{
			int iYStart = iYChunk * iChunkHeight;

			// Ok, so here we get a bit shifty.
			// We have 8 chunks.  We need to have 
			// at minimum 200 room tiles.  200/8 is
			// 25.  sqrt(25) is 5.  So we're going
			// to generate rooms of minimum size 5x5.

			int iRoomWidth = (mt() % (iChunkWidth - 5)) + 5;
			int iRoomHeight = (mt() % (iChunkHeight - 5)) + 5;

			// Randomly calculate the offset of the randomly
			// sized rood

			int iXOffset = mt() % (iChunkWidth - iRoomWidth);
			int iYOffset = mt() % (iChunkHeight - iRoomHeight);

			// Make sure this room lines up with the pre-generated
			// tunnels

			int iTunnelY = iYStart + (iChunkHeight/2);


			// Verify that the room matches the tunnel in the Y direction
			if( iYOffset + iYStart > iTunnelY )
			{
				iYOffset = iTunnelY - iYStart;
			}
			else if( iYOffset + iYStart + iRoomHeight <= iTunnelY )
			{
				iYOffset = 1 + iTunnelY - (iYStart + iRoomHeight);
			}

			// And check for the X direction (although this only matters for
			// rooms in the first or last chunk, X-wise)

			if( iXChunk == 0 || iXChunk == 3 )
			{
				int iTunnelX = iXStart + (iChunkWidth/2);

				if( iXOffset + iXStart > iTunnelX )
				{
					iXOffset = iTunnelX - iXStart;
				}
				else if( iXOffset + iXStart + iRoomWidth <= iTunnelX )
				{
					iXOffset = 1 + iTunnelX - (iXStart + iRoomWidth);
				}

			}

			// And then put the generated room on the level

			for( int x = 0; x < iRoomWidth; x++ )
			{
				for( int y = 0; y < iRoomHeight; y++ )
				{
					m_vvTiles[y + iYOffset + iYStart][x + iXOffset + iXStart] = '.';
				}
			}

			// Check to see if we picked this room for up/down stairs, and
			// if so, randomly place the stairs

			if( iXChunk == iUpXChunk && iYChunk == iUpYChunk )
			{
				m_vvTiles[iYOffset + iYStart + (mt() % iRoomHeight)][iXOffset + iXStart + (mt() % iRoomWidth)] = '<';
			}

			if( iXChunk == iDownXChunk && iYChunk == iDownYChunk )
			{
				m_vvTiles[iYOffset + iYStart + (mt() % iRoomHeight)][iXOffset + iXStart + (mt() % iRoomWidth)] = '>';
			}

		}
	}

}


DungeonLevel::~DungeonLevel(void)
{
}


void DungeonLevel::dump()
{
	for( auto itOuter = m_vvTiles.begin();
		itOuter != m_vvTiles.end();
		itOuter++ )
	{
		for( auto itInner = (*itOuter).begin();
			itInner != (*itOuter).end();
			itInner++ )
		{
			cout << *itInner;
		}

		cout << endl;
	}
}

char DungeonLevel::at(int x, int y)
{
	return m_vvTiles[y][x];
}

int DungeonLevel::getWidth()
{
	return m_vvTiles[0].size();
}

int DungeonLevel::getHeight()
{
	return m_vvTiles.size();
}


vector <Item*> DungeonLevel::getInventory()
{
	return  vInventory;
}


bool DungeonLevel::locateEntity(int YCoord, int XCoord)
{
	//get character at element at coordinates
	char posChar = m_vvDisplayDungeon[YCoord][XCoord];

	if((posChar != '.') && (posChar != ' ') && (posChar != '<') && (posChar != '>'))
	{
		return true;
	}

	else
	{
		return false;
	}
}

vector<int> DungeonLevel::findChar(char cInput)
{

	vector<int> vCoordVector;
	//Iterate though m_vvTiles
	for(int iRow = 0; iRow < getHeight(); iRow++)
	{
		for(int iClm = 0; iClm < getWidth(); iClm++)
		{
			if(m_vvTiles[iRow][iClm] == cInput)
			{
				vCoordVector.push_back(iRow);
				vCoordVector.push_back(iClm);
				return vCoordVector;
			}
		}
	}

}


vector<int> DungeonLevel::findCoords(string sInput, int iItemCtr)
{

	vector<int> vObjectCoords;
	//Use this function to find the coordinates of a specific item 

	if(sInput == "Armor")
	{
		vObjectCoords.push_back(vArmor[iItemCtr]->getYCoord());
		vObjectCoords.push_back(vArmor[iItemCtr]->getXCoord());

		return vObjectCoords;
	}

	if(sInput == "Weapon")
	{
		vObjectCoords.push_back(vWeapons[iItemCtr]->getYCoord());
		vObjectCoords.push_back(vWeapons[iItemCtr]->getXCoord());

		return vObjectCoords;
	}

	if(sInput == "Consumable")
	{
		vObjectCoords.push_back(vConsumables[iItemCtr]->getYCoord());
		vObjectCoords.push_back(vConsumables[iItemCtr]->getXCoord());

		return vObjectCoords;
	}

}

vector<int> DungeonLevel::findCreatureCoords(Player* oPlayer, char cUserChar)
{
	int iPY = oPlayer->getYCoord();
	int iPX = oPlayer->getXCoord();

	vector<int> vCreatureCoords;

	if(cUserChar == 'w')
	{
		iPY -= 1;
	}

	if(cUserChar == 's')
	{
		iPY += 1;
	}

	if(cUserChar == 'a')
	{
		iPX -= 1;
	}

	if(cUserChar == 'd')
	{
		iPX += 1;
	}

	vCreatureCoords.push_back(iPY);
	vCreatureCoords.push_back(iPX);

	return vCreatureCoords;


}

string DungeonLevel::replaceItem(string sType, string sName, int iPos)
{

	string tempName;

	if(sType == "Weapon")
	{
		//Get the name of the temporary weapon
		Weapon * tempWep = vWeapons[iPos];
		tempName = tempWep->getName();

		//Change the name of the weapon to be that of the player's inventory
		vWeapons[iPos]->setName(sName);
		return tempName;
	}

	if(sType == "Armor")
	{
		//Get the name of the temporary weapon
		Armor * tempArm = vArmor[iPos];
		tempName = tempArm->getName();

		//Change the name of the weapon to be that of the player's inventory
		vArmor[iPos]->setName(sName);
		return tempName;

	}
}

void DungeonLevel::dropItem(int iYCoord, int iXCoord, int iNum)
{
	if(iNum % 2 == 0)
	{
		Armor * pOArmor = NULL;
		pOArmor = new Armor(* GenericFactory::instance().generateArmor());
		pOArmor->setCoord(iYCoord, iXCoord);
		vArmor.push_back(pOArmor);
	}

	else
	{
		Weapon * pOWeapon = NULL;
		pOWeapon = new Weapon(* GenericFactory::instance().generateWeapon());
		pOWeapon->setCoord(iYCoord, iXCoord);
		vWeapons.push_back(pOWeapon);

	}

}


Creature * DungeonLevel::findCreature(Player * oPlayer, char cUserChar)
{
	//Get the coordinates of the player object
	int iPY = oPlayer->getYCoord();
	int iPX = oPlayer->getXCoord();

	int iCY = 0;
	int iCX = 0;

//	char cCreature = ' ';

	//Get the proposed coordinates
	if(cUserChar == 'w')
	{
		iPY -= 1;
	}

	if(cUserChar == 's')
	{
		iPY += 1;
	}

	if(cUserChar == 'a')
	{
		iPX -= 1;
	}

	if(cUserChar == 'd')
	{
		iPX += 1;
	}


	//Iterate through the vector of objects
	for(int ctr = 0; ctr < vCreatures.size(); ctr++)
	{
		//cCreature = vObjects[ctr]->getSymbol();
		//if(cCreature == 'C')

			iCY = vCreatures[ctr]->getYCoord();
			iCX = vCreatures[ctr]->getXCoord();

			if((iCY == iPY) && (iCX == iPX))
			{
				//Creature * oCreature =  vObjects[ctr];
				return vCreatures[ctr];
			}


	
	}

}

void DungeonLevel::generateObjects(int num_objects, string object_type, bool isInventory)
{

	//vector<Entity*> vObjects;
	if(object_type == "Creature")
	{
		for(int ctr = 0; ctr < num_objects; ctr++)
		{
			//Creature * pCritter = GenericFactory::instance().generateCreature(20);

			Creature * pCritter = NULL; 
			pCritter = new Creature(*GenericFactory::instance().generateCreature(20));
			pCritter->setCoord(0, 0);

			//append the creature object to the vector of objects and creatures
			//vObjects.push_back(pCritter);
			vCreatures.push_back(pCritter);
		}

	}

	if(object_type == "Armor")
	{
		for(int ctr = 0; ctr < num_objects; ctr++)
		{
			Armor * pArmor = NULL;
			pArmor = new Armor(* GenericFactory::instance().generateArmor());
			pArmor->setCoord(0, 0);
			if(isInventory == false)
			{
				vArmor.push_back(pArmor);
			}
			else
			{
				vInventory.push_back(pArmor);
			}
		}

	}

	if(object_type == "Weapon")
	{
		for(int ctr = 0; ctr < num_objects; ctr++)
		{
			Weapon *  pWeapon =  NULL;
			pWeapon = new Weapon(*GenericFactory::instance().generateWeapon());
			pWeapon->setCoord(0, 0);
			if(isInventory == false)
			{
				vWeapons.push_back(pWeapon);
			}
			else
			{
				vInventory.push_back(pWeapon);
			}
		}

	}


	if(object_type == "Consumable")
	{
		for(int ctr =0; ctr < num_objects; ctr++)
		{
			Entity * pConsumable = NULL;
			pConsumable = new Entity;
			pConsumable->setName("Potion");
			pConsumable->setSymbol('u');
			pConsumable->setCoord(0,0);
			vConsumables.push_back(pConsumable);
		}
	}


}


bool DungeonLevel::movementValid(int iPYcoord, int iPXcoord, char cDirection)
{
	if(cDirection == 'w' || cDirection == 'W')
	{
		//Get character at position that we want to move  if, not ' ' or 'C', then it's fine
		if((m_vvTiles[(iPYcoord - 1)][iPXcoord] != ' ') && (m_vvTiles[(iPYcoord -1)][iPXcoord] != 'C') && (m_vvTiles[(iPYcoord -1)][iPXcoord] != 'P'))
		{
			return true;
		}

		else
		{
			return false;
		}
	}

	if(cDirection == 's' || cDirection == 'S')
	{
		//Get character at position that we want to move  if, not ' ' or 'C', then it's fine
		if((m_vvTiles[(iPYcoord + 1)][iPXcoord] != ' ') && (m_vvTiles[(iPYcoord + 1)][iPXcoord] != 'C') && (m_vvTiles[(iPYcoord +1)][iPXcoord] != 'P'))
		//if(m_vvTiles[(iPYcoord + 1)][iPXcoord] != ' ')
		{
			return true;
		}

		else
		{
			return false;
		}
	}

	if(cDirection == 'a' || cDirection == 'A')
	{
		//Get character at position that we want to move  if, not ' ' or 'C', then it's fine
		if((m_vvTiles[iPYcoord][(iPXcoord -1)] != ' ') && (m_vvTiles[iPYcoord][(iPXcoord -1)] != 'C') && (m_vvTiles[iPYcoord][(iPXcoord - 1)] != 'P'))
		//if(m_vvTiles[iPYcoord][(iPXcoord - 1)] != ' ')
		{
			return true;
		}

		else
		{
			return false;
		}
	}


	if(cDirection == 'd' || cDirection == 'D')
	{
		//Get character at position that we want to move  if, not ' ' or 'C', then it's fine
		if((m_vvTiles[iPYcoord][(iPXcoord + 1)] != ' ') && (m_vvTiles[iPYcoord][(iPXcoord + 1)] != 'C') && (m_vvTiles[iPYcoord][(iPXcoord +1)] != 'P'))
		//if(m_vvTiles[iPYcoord][(iPXcoord + 1)] != ' ')
		{
			return true;
		}

		else
		{
			return false;
		}
	}

}

bool DungeonLevel::adjObject(Player * oPlayer, int YCoord, int XCoord)
{
	int oY;
	int oX;

	//If we are checking to see if the player is adjacent to a creature
	//We simply get the coordinates of the player, if they are the same as the parameters passed, then we return true;
	for(int ctr = 0; ctr < vCreatures.size(); ctr++)
	{
//		oSym = vObjects[ctr]->getSymbol();
//		if(oSym == 'C')


//			oY = vObjects[ctr] -> getYCoord();
//			oX = vObjects[ctr] -> getXCoord();

			oY = vCreatures[ctr] -> getYCoord();
			oX = vCreatures[ctr] -> getXCoord();

			//if the creature object is located directly above the player return true
			if(((oY + 1) == YCoord) && (oX == XCoord))
			{
				return true;
			}

			//If the creature object is below the player return true
			if(((oY - 1) == YCoord) && (oX == XCoord))
			{
				return true;
			}

			//if the creature is to the left of the player return true
			if((oY == YCoord) && ((oX - 1) == XCoord))
			{
				return true;
			}

			//If the creatue is to the right of the player return true
			if((oY == YCoord) && ((oX + 1) == XCoord))
			{
				return true;
			}

			else
			{
				return false;
			}
	
	}

/*
	if(sOName == "Player")
	{
		bool objAdj = false;

		//If we are checking if a Player moves on a Creature though, it's slightly more complicated
		//iterate through the vector or objects
		for(int ctr = 0; ctr < vObjects.size(); ctr++)
		{
			oSym = vObjects[ctr]->getSymbol();
			if(oSym == 'C')
			{
				oY = vObjects[ctr] -> getYCoord();
				oX = vObjects[ctr] -> getXCoord();

				if((oY == YCoord) && (oX == XCoord))
				{
					return true;
				}

				else
				{
					objAdj = false;
				}
			}

			else
			{
			 	objAdj = false;
			}
		}

		return objAdj;
	}
*/


}


bool DungeonLevel::movementAttack(Player * oPlayer, char cUserChar)
{
	//Get the coordinates of the player object
	int iPY = oPlayer->getYCoord();
	int iPX = oPlayer->getXCoord();

	int iPYini = iPY;
	int iPXini = iPX;

	int iCY = 0;
	int iCX = 0;


	//Get the proposed coordinates
	if(cUserChar == 'w')
	{
		iPY -= 1;
	}

	if(cUserChar == 's')
	{
		iPY += 1;
	}

	if(cUserChar == 'a')
	{
		iPX -= 1;
	}

	if(cUserChar == 'd')
	{
		iPX += 1;
	}

	//Iterate through the vector of objects
	for(int ctr = 0; ctr < vCreatures.size(); ctr++)
	{
//		cCreature = vObjects[ctr]->getSymbol();
//		if(cCreature == 'C')

			iCY = vCreatures[ctr]->getYCoord();
			iCX = vCreatures[ctr]->getXCoord();

			if((iCY == iPY) && (iCX == iPX))
			{
				return true;
			}

			if((iCY == iPYini) && (iCX == iPXini))
			{
				return true;
			}

	}


	return false;



}

bool DungeonLevel::ObjectPosComp(int YCoord, int XCoord)
{

	bool isSame = false;

	//Iterates through the vector of objects
	for(int ObjCtr = 0; ObjCtr < vCreatures.size(); ObjCtr++)
	{
		int iObjYCoord = vCreatures[ObjCtr]->getYCoord();
		int iObjXCoord = vCreatures[ObjCtr]->getXCoord();

		if((YCoord == iObjYCoord) && (XCoord == iObjXCoord))
		{
			//Set isSame to true if a match is found
			isSame = true;
		}

	}

	return isSame;
}


void DungeonLevel::moveCreature(Player * oPlayer)
{
	//First get the coordinates of each
	int iPlayerY = oPlayer->getYCoord();
	int iPlayerX = oPlayer->getXCoord();

//	char cSym = ' ';

	for(int ctr =0; ctr < vCreatures.size(); ctr++)
	{
//		cSym = vObjects[ctr]->getSymbol();
//		if(cSym == 'C')

			int iCreatureY = vCreatures[ctr]->getYCoord();
			int iCreatureX = vCreatures[ctr]->getXCoord();

			//Create a boolean value to determine when a monster can move properly
			bool MoveValid = false;

			//Try to move in the x direction
			if(iCreatureX  < iPlayerX)
			{
				MoveValid = movementValid(iCreatureY, iCreatureX, 'd');
				if(MoveValid == true)
				{
					vCreatures[ctr]->setCoord(iCreatureY, (iCreatureX + 1));
				}
			}

			if(iCreatureX  > iPlayerX)
			{
				MoveValid = movementValid(iCreatureY, iCreatureX, 'a');
				if(MoveValid == true)
				{
					vCreatures[ctr]->setCoord(iCreatureY, (iCreatureX - 1));
				}
			}


			//if that fails then try to move in the y direction
			if(iCreatureY  > iPlayerY)
			{
				MoveValid = movementValid(iCreatureY, iCreatureX, 'w');
				if(MoveValid == true)
				{
					vCreatures[ctr]->setCoord((iCreatureY - 1), iCreatureX);
				}
			}

			if(iCreatureY  < iPlayerY)
			{
				MoveValid = movementValid(iCreatureY, iCreatureX, 's');
				if(MoveValid == true)
				{
					vCreatures[ctr]->setCoord((iCreatureY + 1), iCreatureX);
				}
			}

	}


}


bool DungeonLevel::PlayerAttack(Player * oPlayer, char cUserChar, vector<string>& vStrings )
{
	bool bCreatureKilled = false;

	//Get a creature object wherre the user is trying to move
	Creature * oCreature = findCreature(oPlayer, cUserChar);
	//get object coordinates
	int iY = oCreature->getYCoord();
	int iX = oCreature->getXCoord();
	int iNum = 0;

	//return a value that determines if Creature died or not
	bCreatureKilled =  oPlayer->attack(oCreature, vStrings);

	//if the creature died, erase it from vCreatures
	if(bCreatureKilled == true)
	{
		//Find it's position in vCreatures
		for(int ctr = 0; ctr < vCreatures.size(); ctr++)
		{
			if((iY == vCreatures[ctr]->getYCoord()) && (iX == vCreatures[ctr]->getXCoord()));
			{
				iNum = ctr;
			}
		}
		//Erase the creature at this position in the vector of creatures.
		vCreatures.erase(vCreatures.begin() + iNum);
	}
}


void DungeonLevel::CreatureAttack(Player * oPlayer, char cUserChar, vector<string>& vStrings)
{
	Creature * oCreature = findCreature(oPlayer, cUserChar);
	//get object coordinates
	//int iY = oCreature->getYCoord();
	//int iX = oCreature->getXCoord();

	int iPlayerHP = oPlayer->getHealth();

	iPlayerHP = oCreature->attack(iPlayerHP);
	string sName = oPlayer->getName();

	vStrings.push_back(sName + " you were attacked for 4 damage.");
	//cout << oPlayer->getName() << " you were attacked for " << "4 damage." << endl;

	oPlayer->setHealth(iPlayerHP);

}


int  DungeonLevel::usePotion(Player * oPlayer, int iMaxHP, bool isHealthy)
{
	int iIniHP = oPlayer->getHealth();
	int iHPGained = 0;

	//If the player is at 100 health then just erase the consumable.
	if(isHealthy == true)
	{
		vConsumables.erase(vConsumables.begin());
		return iHPGained;
	}

	else
	{
		int iCurHP = iIniHP + 10;
		if(iCurHP > iMaxHP)
		{
			oPlayer->setHealth(iMaxHP);
			iHPGained = (iMaxHP - iIniHP);
			vConsumables.erase(vConsumables.begin());

			return iHPGained;
		}

		else
		{
			oPlayer->setHealth(iCurHP);
			iHPGained = (iCurHP - iIniHP);
			vConsumables.erase(vConsumables.begin());

			return iHPGained;
		}
	}

}


void DungeonLevel::placePlayer(Player * oPlayer, bool isPlaced, bool isReturn, char cMovement)
{
	//use this method to take a player object and determine it's coordinates for m_vvDispalyDungeon
	//If the player object doesn't already have coordinates, find where the upstairs position in the Display Dungeon is.
	if(isPlaced == false)
	{
		//If the player is returning upstairs, place them at the downstairs position
		if(isReturn == true)
		{
			vector<int> dnstairCoords = findChar('>');
			int iniDNPlayerY = dnstairCoords[0];
			int iniDNPlayerX = dnstairCoords[1];


			//Set player coordinates to the values in the stairCoords
			oPlayer->setCoord(iniDNPlayerY, iniDNPlayerX);
			return;

		}


		//initialize a vector to store the stair coordinates to return value of findChar
		vector<int> stairCoords = findChar('<');

		int iniPlayerY = stairCoords[0];
		int iniPlayerX = stairCoords[1];


		//Set player coordinates to the values in the stairCoords
		oPlayer->setCoord(iniPlayerY, iniPlayerX);
		return;

	}

	//If the player object already has coordinates and the movement is valid, then change coordinates based on movement ints 
	else
	{

		//Get the x and y coordinates of oPlayer
		int iPlayerY = oPlayer->getYCoord();
		int iPlayerX = oPlayer->getXCoord();


		//Determine movement based on char received. 
		if(cMovement == 'w' || cMovement == 'W')
		{
			iPlayerY -= 1;
		}

		if(cMovement == 's' || cMovement == 'S')
		{
			iPlayerY += 1;
		}

		if(cMovement == 'd' || cMovement == 'D')
		{
			iPlayerX += 1;
		}

		if(cMovement == 'a' || cMovement == 'A')
		{
			iPlayerX -= 1;
		}



		//Set new coordinates based on movement
		oPlayer->setCoord(iPlayerY, iPlayerX);
		return;
	}
}


void DungeonLevel::placeObjects(mt19937 & mt, bool newCritter)
{

	int iYRand;
	int iXRand;

	//Create a bool that keeps track whether two objects have the same coordinate
	bool bSame = false;

	if(newCritter == false)
	{
		//First, iterate through the vector of Creatures
		for(int ctr = 0; ctr < vCreatures.size(); ctr++)
		{
			//Initialize to random valus spanning the parameters of the room

			iYRand = (mt() % getHeight());
			iXRand = (mt() % getWidth());

			bSame = ObjectPosComp(iYRand, iXRand);

			//Enter a while loop that makes sure that position does not contain coordinates of another object and has '.'
			while((m_vvTiles[iYRand][iXRand] != '.') || (bSame == true))
			{
				iYRand = (mt() % getHeight());
				iXRand = (mt() % getWidth());

				bSame = ObjectPosComp(iYRand, iXRand);
			}

			//Once valid coordinates have been found set these coordinates to the object
			vCreatures[ctr]->setCoord(iYRand, iXRand);

		}


		//First, iterate through the vector of Items
		for(int ctr = 0; ctr < vArmor.size(); ctr++)
		{
			//Initialize to random valus spanning the parameters of the room

			iYRand = (mt() % getHeight());
			iXRand = (mt() % getWidth());

			//Enter a while loop that makes sure that position does not contain coordinates of another object and has '.'
			while((m_vvTiles[iYRand][iXRand] != '.'))
			{
				iYRand = (mt() % getHeight());
				iXRand = (mt() % getWidth());

			}

			//Once valid coordinates have been found set these coordinates to the object
			vArmor[ctr]->setCoord(iYRand, iXRand);
		}


		//First, iterate through the vector of Weapons
		for(int ctr = 0; ctr < vWeapons.size(); ctr++)
		{
			//Initialize to random valus spanning the parameters of the room

			iYRand = (mt() % getHeight());
			iXRand = (mt() % getWidth());

			//Enter a while loop that makes sure that position does not contain coordinates of another object and has '.'
			while((m_vvTiles[iYRand][iXRand] != '.'))
			{
				iYRand = (mt() % getHeight());
				iXRand = (mt() % getWidth());
			}

			//Once valid coordinates have been found set these coordinates to the object
			vWeapons[ctr]->setCoord(iYRand, iXRand);
		}

		for(int ctr = 0; ctr < vConsumables.size(); ctr++)
		{
			//Initialize to random valus spanning the parameters of the room

			iYRand = (mt() % getHeight());
			iXRand = (mt() % getWidth());

			//bSame = ObjectPosComp(iYRand, iXRand);

			//Enter a while loop that makes sure that position does not contain coordinates of another object and has '.'
			while((m_vvTiles[iYRand][iXRand] != '.'))
			{
				iYRand = (mt() % getHeight());
				iXRand = (mt() % getWidth());
				//bSame = ObjectPosComp(iYRand, iXRand);
			}

			//Once valid coordinates have been found set these coordinates to the object
			vConsumables[ctr]->setCoord(iYRand, iXRand);

		}
	}

	if(newCritter == true)
	{

		iYRand = (mt() % getHeight());
		iXRand = (mt() % getWidth());

		bSame = ObjectPosComp(iYRand, iXRand);

		//Enter a while loop that makes sure that position does not contain coordinates of another object and has '.'
		while((m_vvTiles[iYRand][iXRand] != '.') || (bSame == true))
		{
			iYRand = (mt() % getHeight());
			iXRand = (mt() % getWidth());

			bSame = ObjectPosComp(iYRand, iXRand);
		}

		//Once valid coordinates have been found set these coordinates to the object
		vCreatures.back()->setCoord(iYRand, iXRand);

	}


}


vector<vector<char>> DungeonLevel::displayDungeon(Player * oPlayer)
{
	//Create an empty vector for m_vvDisplayDungeon
	m_vvDisplayDungeon.resize(getHeight());

	for(auto it = m_vvDisplayDungeon.begin();
		it != m_vvDisplayDungeon.end();
		it++ )
	{
		(*it).resize(getWidth(), ' ');
	}

	//Get the coordinates of the player object
	int iPY = oPlayer->getYCoord();
	int iPX = oPlayer->getXCoord(); 

	//Initialize variables that are needed to place non player objects
	int iOY = 0;
	int iOX = 0;

	//Place the generated objects into DungeonLevel

	//Iterate through m_vvTiles
	for(int iDLrow = 0; iDLrow < getHeight(); iDLrow++)
	{
		for(int iDLclm = 0; iDLclm < getWidth(); iDLclm++)
		{
			//bool that determines if object was placed or not
			bool bCharPlaced = false;

			//If there is another Item  at the coordinate then print
			//Iterate through the vector of coordinates, checking
			for(int ctr = 0; ctr < vArmor.size(); ctr++)
			{
				iOY = vArmor[ctr]->getYCoord();
				iOX = vArmor[ctr]->getXCoord();

				if((iDLrow == iOY) && (iDLclm == iOX))
				{
					m_vvDisplayDungeon[iDLrow][iDLclm] = vArmor[ctr]->getSymbol();
					bCharPlaced = true;

				}
			}

			for(int ctr = 0; ctr < vWeapons.size(); ctr++)
			{
				iOY = vWeapons[ctr]->getYCoord();
				iOX = vWeapons[ctr]->getXCoord();

				if((iDLrow == iOY) && (iDLclm == iOX))
				{
					m_vvDisplayDungeon[iDLrow][iDLclm] = vWeapons[ctr]->getSymbol();
					bCharPlaced = true;

				}
			}

			//If there is a consumable at the coordinates then print it
			for(int ctr = 0; ctr < vConsumables.size(); ctr++)
			{
				iOY = vConsumables[ctr]->getYCoord();
				iOX = vConsumables[ctr]->getXCoord();

				if((iDLrow == iOY) && (iDLclm == iOX))
				{
					m_vvDisplayDungeon[iDLrow][iDLclm] = vConsumables[ctr]->getSymbol();
					bCharPlaced = true;

				}
			}

			//If there is another Creature at the coordinate then print
			//Iterate through the vector of coordinates, checking
			for(int ctr = 0; ctr < vCreatures.size(); ctr++)
			{
				iOY = vCreatures[ctr]->getYCoord();
				iOX = vCreatures[ctr]->getXCoord();

				if((iDLrow == iOY) && (iDLclm == iOX))
				{
					m_vvDisplayDungeon[iDLrow][iDLclm] = vCreatures[ctr]->getSymbol();
					bCharPlaced = true;

				}
			}


			//If there is a Player at the  coordinate then set the character equal to  'P'
			if((iDLrow == iPY) && (iDLclm == iPX))
			{
				m_vvDisplayDungeon[iDLrow][iDLclm] = 'P';
				bCharPlaced = true;
			}


			//else just do the normal thing
			if(bCharPlaced == false)
			{
				m_vvDisplayDungeon[iDLrow][iDLclm] = m_vvTiles[iDLrow][iDLclm];
			}

		}
	}

	return m_vvDisplayDungeon;

/*
	//vector<vector<char>> vvTempVector;
	vvTempVector.resize(getHeight());

	for(auto it = vvTempVector.begin();
		it !=  vvTempVector.end();
		it++ )
	{
		(*it).resize(getWidth(), ' ');
	}


	//Iterate through Display vector and display it's contents
	for(int iDispRow =0; iDispRow < getHeight(); iDispRow++)
	{
		for(int iDispClm =0; iDispClm < getWidth(); iDispClm++)
		{
			//cout << m_vvDisplayDungeon[iDispRow][iDispClm];
			vvTempVector.push_back( m_vvDisplayDungeon[iDispRow][iDispClm]);

		}

		//Endline after last chracter in row
		//cout << endl;
	}
*/

	//cout << endl;
}
