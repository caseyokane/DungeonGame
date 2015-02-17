/*Casey O'Kane CS216 Section 2
  Programming Assignment 3 & 4
*/

//Headers
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <functional>
#include <random>
#include <ctime>
#include <ncurses.h>
#include <sstream>

#include "Entity.h"
#include "Player.h"
#include "Item.h"
#include "Creature.h"
#include "Character.h"


#include "DungeonLevel.h"
#include "GenericFactory.h"
#include "parser.h"


using namespace std;




//Potential Singleton Class:

/*
class SingClass
{
public:

	~SingClass();
	static SingClass& instance();


private:

	SingClass();
	stringstream  ssOutput;

}

SingClass::SingClass()
{
	//Object has been constructed

	//Construct String Stream that is empty
	ssOutput = ssOutput.str("");
}

SingClass::~SingClass()
{
	//Object gets  destructed
}

SingClass& SingClass::instance()
{
	static SingClass oSSObject;
	return oSSobject;
}
*/






int experienceManagement(Player * oPlayer, int iMaxHP, vector<string>& vStrings )
{
	int iCurEXP = oPlayer->getExperience();
	int iLevel = 1;
	int iEXP = 5;

	iCurEXP += iEXP;

	if((iCurEXP % 10) == 0)
	{
		iLevel += (iCurEXP/10);
		oPlayer->setLevel(iLevel);
		stringstream sLevel;

		sLevel << oPlayer->getLevel();
		vStrings.push_back("Level up!");


		string sPLevel = sLevel.str();

		string sPName = oPlayer->getName();
		vStrings.push_back(sPName +  " is now Level " + sPLevel +  "! Max HP increased by 10. ");
		iMaxHP += 10;
	}

	oPlayer->setExperience(iCurEXP);
	return iMaxHP;

}

void healthManagement(Player * oPlayer, int iMaxHP, int iTurnCount)
{
	int iCurHP = oPlayer->getHealth();

	if((iCurHP < iMaxHP) && (iTurnCount % 2 == 0))
	{
		iCurHP += 1;
	}
	oPlayer->setHealth(iCurHP);
}

void displayInventory(Player * oPlayer, vector<string>& vStrings)
{
	//Have a vector of Equipment pointers, 1 Item and 1 Armor
	//Go through this vector and display to screen
	vector<Item*> tempVector = oPlayer->getInventory();
	string sWeapon = tempVector[0]->getName();
	string sArmor = tempVector[1]->getName();
	vStrings.push_back("Weapon: " + sWeapon + "		Armor: " + sArmor);

}


void displayRules(bool firstTime, vector<string>& vStrings)
{

	if(firstTime == false)
	{
		vStrings.push_back(" ");
		vStrings.push_back("Command List: ");
		vStrings.push_back(" ");
		vStrings.push_back("	Use the arrow keys to move around the board.	          ");
		vStrings.push_back("'u' = use item/stairs.		'r' = display rules.");
		vStrings.push_back("'i' = display inventory. 	'p' = pick up item.");
		vStrings.push_back(" ");
		vStrings.push_back( "Other Symbols: ");
		vStrings.push_back(" ");
		vStrings.push_back("'P' = Player.		'C' = Creature.		'[' = Armor.		'(' = Weapon. ");
		vStrings.push_back("'u' = Potion.		'<' = Up Stairs.	'>' = Down Stairs. ");
		vStrings.push_back(" ");

	}


	if(firstTime == true)
	{

		cout << endl;
		cout << "Command List: " << endl;
		cout << endl;
		cout << "	Use the arrow keys to move around the board.	          " << endl;
		cout << "'u' = use item/stairs.		'r' = display rules." << endl;
		cout << "'i' = display inventory. 	'p' = pick up item." << endl;
		cout << endl;
		cout << "Other Symbols: " << endl;
		cout << endl;
		cout << "'P' = Player.		'C' = Creature.		'[' = Armor.		'(' = Weapon. " << endl;
		cout << "'u' = Potion.		'<' = Up Stairs.	'>' = Down Stairs. " <<endl;
		cout << endl;

		cout << "					Casey O'Kane's Dungeon Experience" << endl;
		cout << endl;
		cout << "	For this program, I decided to stick pretty close to the requirements provided and didn't attempt for any real extra credit.  " << endl;
		cout << "In order to solve the positioning issue with the program, I decided to simply have all of the Entities maintain X and Y Coordinates. " << endl;
		cout << "I went with this decision mostly because I thought that it would be the easiest to implement. I also, chose to do everything without " << endl;
		cout << "implementing a tile class, as when I did, I kept receiving an absured amount of segmentation fault errors. I mostly handle everything" << endl;
		cout << "just using the coordinates of the entities themselves." << endl;
		cout << endl;
		cout << "	I handle experience increasing the Players experience by 5 whenever they kill an opposing creature. for every 10 experience points" << endl;
		cout << "a player's level increases. For every increase in level, the plays health points will also increase by 10 and their attack value increases" << endl;
		cout << "by 1.	While, I certainly had some issues with the inventory,, I belive that the majority of the requirements are here.		   " << endl;
		cout << endl;
		cout << "Good luck!" <<endl;
		cout << endl;

	}



}




int main(int argc, char * argv[])
{


	//Intialize and seed  a mercine twister object
	mt19937 mt;
	mt.seed( time(NULL) );

	//Intialize a vector of Dungeon Level Pointers
	vector<DungeonLevel*> vDungeonLevels;

	//Use a for loop to place 5 random dungeon levels in the dungeon levels vector
	for(int dlvl = 0; dlvl < 10; dlvl++)
	{

		DungeonLevel * oDungeonLevel = NULL;
		oDungeonLevel = new DungeonLevel(79, 20, mt);
		//Generate creatures and items for every level

		//start out with 3 creatures
		oDungeonLevel->generateObjects(2, "Creature", false);

		//start out with 1 armor and 1 weapon
		//oDungeonLevel->generateObjects(2, "Item");
		oDungeonLevel->generateObjects(1, "Armor", false);
		oDungeonLevel->generateObjects(1, "Weapon", false);

		//generate a consumable as well
		oDungeonLevel->generateObjects(1, "Consumable", false);

		//now give these objects coordinates
		oDungeonLevel->placeObjects(mt, false);

		//Push the DungeonLevel onto the the vector of Dungeon Levels
		vDungeonLevels.push_back(oDungeonLevel);

	}

	//Set Initial dungeon to level 0
	//DungeonLevel *  vpCurrentDLevel =  vDungeonLevels[0];
	int iDungeonLevel = 0;
	DungeonLevel * vCurrentDLevel = vDungeonLevels[0];

	vector<string> vStrings(0);


	//Print out "Rules Screen"
	displayRules(true, vStrings);


	//Declare and Initialize Player object
	Player * oPlayer = NULL;
	oPlayer = new Player;

	string sUser = " ";
	cout << "Good day adventurer! What is your name?: "; 
	cin >> sUser;
	cout << endl;
	if(sUser == "name")
	{
		cout << "Really? That's the best could come up with? " << endl;
		cout << "No, I think your name will be Meat" << endl;
		oPlayer->setName("Meat");
	}
	else
	{
		oPlayer->setName(sUser);
	}

	cout << endl;
	cout << "You enter the dungeon..." << endl;

	//Initialize Entity Characteristics of Player
	oPlayer->setSymbol('P');
	oPlayer->setHealth(20);

	int iMaxHP = 20;
	//Initialize Inventory Characteristics of Player
	//Generate a an armor object along with a weapon object
	vCurrentDLevel->generateObjects(1, "Weapon", true);
	vCurrentDLevel->generateObjects(1, "Armor", true);


	//place them into respective pointers
	vector<Item*> vPInventory = vCurrentDLevel->getInventory();
	Item * oPWeapon = vPInventory[0];
	Item * oPArmor = vPInventory[1];

	//Set the player iventory to the pointer objects
	//oPlayer->setInventory(oPWeapon, oPArmor);
	oPlayer->setInventory(oPWeapon, false);
	oPlayer->setInventory(oPArmor, false);


	//First  place the player object at intial up stairs position
	vCurrentDLevel->placePlayer(oPlayer, false, false,  ' ');


	//Insert Practicum  code 

	//Declare an integer to store a command that isn't one of the directions
	int iCommand = ' ';

	//Create a string to keep track of the command
	string sCommand = "Entered the dungeon...";

	//Initialize a 2D vector of chars to store the dungeon level created from disPlayDungeon
	vector<vector<char>> vvDisplayDungeon;

	//keep track of the number of monsters killed and the number of turns that have occured.
	int iBodyCount = 0;
	int iTurnCount = 0;

	string sEndState = "quit";
	bool bGameEnd = false;

	//Create a vector of strings to keep track of messages incurred throughout the program.

	stringstream ssOutput;

	//Initialize the ncurses screen
	initscr();

	//Initialize the key-pad in order to use macro commands
	keypad(stdscr, TRUE);


	// Enter.... THE WHILE LOOP
	do
	{

	clear();

	iTurnCount++;


	//print out the current dungeon level. Call the display method
	vvDisplayDungeon = vCurrentDLevel->displayDungeon(oPlayer);
	for(int y = 0; y < vCurrentDLevel->getHeight(); y++)
	{
		for(int x = 0; x < vCurrentDLevel->getWidth(); x++)
		{
			move(y,x);
			addch(vvDisplayDungeon[y][x]);
		}
	}

	int iCurY = oPlayer->getYCoord();
	int iCurX = oPlayer->getXCoord();

	move(iCurY, iCurX);
	addch('P');

	ssOutput.str("");

	//print out status and instructions
	ssOutput << "Name: " << oPlayer->getName() << "	Level: " << oPlayer->getLevel() << "	HP: " << oPlayer->getHealth() << "		Dungeon Level: " << (iDungeonLevel +1) << endl;
	ssOutput << "What do you want to do? ('r' = rules) : " << sCommand << endl;

	//Iterate through the vector of strings and put its contents into ssOutput;
	for(int ctr = 0; ctr < vStrings.size(); ctr++)
	{
		ssOutput << vStrings[ctr] << endl;
	}

	move(20, 0);
	addstr(ssOutput.str().c_str());
	refresh();

	for(int ctr = 0; ctr < vStrings.size(); ctr++)
	{
		vStrings.pop_back();
	}

	//Get Input
	iCommand = getch();

	//Movement Possibility:


	//use a bool to keep track whether a Player is adjacent to a Creature or not.
	bool ObjAdj = false;
	char cUserChar = ' ';

	if(iCommand == KEY_DOWN)
	{
		sCommand = "moved down";
		cUserChar = 's';
	}

	else if(iCommand == KEY_UP)
	{
		sCommand = "moved up";
		cUserChar = 'w';
	}

	else if(iCommand == KEY_LEFT)
	{
		sCommand = "moved to the left";
		cUserChar = 'a';
	}

	else if(iCommand == KEY_RIGHT)
	{
		sCommand = "moved to the right";
		cUserChar = 'd';
	}

	else
	{
		cUserChar = static_cast<char>(iCommand);
	}

	if((cUserChar == ('w')) || (cUserChar == ('s')) || (cUserChar == ('a')) || (cUserChar == ('d')))
 	{
		//When movement occurs, call the movement valid method, which make sure that an entity doesn't exist at that location. Return bool

		bool moveValid = vCurrentDLevel->movementValid(iCurY, iCurX, cUserChar);
		if(moveValid == false)
		{
			vStrings.push_back("You can't move there!");
			sCommand = "Wasting a turn.";
		}


		//If movement is valid, then test to see if an object is adjacent
		ObjAdj = vCurrentDLevel->movementAttack(oPlayer, cUserChar);
		bool creatureDead = false;
		int iChoice = 1;

		if((moveValid == true) && (ObjAdj == true))
		{

			vector<int> vCreatureCoords = vCurrentDLevel->findCreatureCoords(oPlayer, cUserChar);
			int iCY = vCreatureCoords[0];
			int iCX = vCreatureCoords[1];

			sCommand = "Attacked a creature!";
			creatureDead = vCurrentDLevel->PlayerAttack(oPlayer, cUserChar, vStrings);
			if(creatureDead == true)
			{

				//Increment the body count
				iBodyCount++;

				//call the experience management method
				iMaxHP = experienceManagement(oPlayer, iMaxHP, vStrings);

				if(iBodyCount % 2 == 0)
				{
					vCurrentDLevel->dropItem(iCY, iCX, iChoice);
				}

				iChoice++;
			}


		}

			//If you make it through the while loop, then move the player to the new location
		if((moveValid == true) && (ObjAdj == false))
		{
			vCurrentDLevel->placePlayer(oPlayer, true, false, cUserChar);
		}
	}


	int iPYCoord = oPlayer->getYCoord();
	int iPXCoord = oPlayer->getXCoord();



	//Use Possibility:
	if((cUserChar == 'U') || (cUserChar == 'u'))
	{

		//get stair coordinates
		vector<int> vUPCoords = vCurrentDLevel->findChar('<');
		vector<int> vDNCoords = vCurrentDLevel->findChar('>');
		//Iterate through the vector of consumables and get their coordinates

		vector<int> vConCoords = vCurrentDLevel->findCoords("Consumable", 0);


		int iSUYCoord = vUPCoords[0];
		int iSUXCoord = vUPCoords[1];

		int iSDYCoord = vDNCoords[0];
		int iSDXCoord = vDNCoords[1];

		//Iterate through each object  in the vector, first setting to a vector, then checking to see if the positios are the same as the player.
		int iConYCoord = vConCoords[0];
		int iConXCoord = vConCoords[1];


		//have player position
		//Check for stair position at those coordinates
		if((iSDYCoord == iPYCoord) && (iSDXCoord == iPXCoord))
		{
			if(iDungeonLevel < 10)
			{
				//Change the DungeonLevel to the one below
				vCurrentDLevel = vDungeonLevels[(iDungeonLevel + 1)];
				iDungeonLevel++;
				vCurrentDLevel->placePlayer(oPlayer, false, false, ' ');
				vStrings.push_back( "Descend to the next level...");
				sCommand = "Went down the stairs";
			}


			else
			{
				vStrings.push_back( "Sorry, you're at the bottom...");
			}

		}

		if((iSUYCoord == iPYCoord) && (iSUXCoord == iPXCoord))
		{
			//Game Ending State! 
			//If user attempts to go upstairs on level 1, then the game ends
			if(iDungeonLevel == 0)
			{

				sEndState = "exit";
				bGameEnd = true;
			}

			//If they aren't on level 1, simply just go to the level above.
			else
			{
				vCurrentDLevel = vDungeonLevels[(iDungeonLevel - 1)];
				iDungeonLevel--;
				vCurrentDLevel->placePlayer(oPlayer, false, true, ' ');
				vStrings.push_back("Went up the stairs.");
				sCommand = "Went up the stairs";

			}
		}

		//Check if there is an item at that position
		//find the number of weapons and armor in a map

		//check if there is a weapon at that position
		for(int ctr = 0; ctr < 1; ctr++)
		{
			vector<int> vWepCoords = vCurrentDLevel->findCoords("Weapon", ctr);
			int iWepYCoord = vWepCoords[0];
			int iWepXCoord = vWepCoords[1];

			if((iWepYCoord == iPYCoord) && (iWepXCoord == iPXCoord))
			{
				vector<Item*> vTempItems = oPlayer->getInventory();
				//Weapon * dlWeapon = vCurrentDLevel->vWeapons[0];
				Item * pWeapon = vTempItems[0];
				Item * pArmor = vTempItems[1];

/*
				string WepName = vTempItems[0]->getName();
				string ArmName = vTempItems[1]->getName();
				vStrings.push_back("weapon before: " + WepName);
				vStrings.push_back("armor before: " + ArmName);
*/

				string pItem = pWeapon->getName();

				//Get the name from both items
				string dlItem = vCurrentDLevel->replaceItem("Weapon", pItem, ctr);
				vStrings.push_back("Picked up " + dlItem + " and dropped " + pItem);

				pWeapon->setName(dlItem);

				oPlayer->eraseInventory(0);


				oPlayer->setInventory(pWeapon, true);


			}
		}


		//Check if there is armor at that position
		for(int ctr = 0; ctr < 1; ctr++)
		{
			vector<int> vArmCoords = vCurrentDLevel->findCoords("Armor", ctr);
			int iArmYCoord = vArmCoords[0];
			int iArmXCoord = vArmCoords[1];

			if((iArmYCoord == iPYCoord) && (iArmXCoord == iPXCoord))
			{
				vector<Item*> vTempItems = oPlayer->getInventory();

				Item * pWeapon = vTempItems[0];
				Item * pArmor = vTempItems[1];
				string pItem = pArmor->getName();

				//Get the name from both items
				string dlItem = vCurrentDLevel->replaceItem("Armor", pItem, ctr);
				vStrings.push_back("Picked up " + dlItem + " and dropped " + pItem);


				pArmor->setName(dlItem);

				oPlayer->eraseInventory(1);

				oPlayer->setInventory(pArmor, false);

			}

		}

		//Check if there is a consumable at that position
		if((iConYCoord == iPYCoord) && (iConXCoord == iPXCoord))
		{
			int iHPGained = 0;
			int User_Health = oPlayer->getHealth();

			if(User_Health == iMaxHP)
			{

/*
				string sInput = " ";
				//cout << "You seem to have quite a bit of health already, are you sure you want to use that? (y or n): ";
				cin >> sInput;
				if(sInput[0] ==  'y')
				{
					//erase the consumable from the consumable vector
					iHPGained = vCurrentDLevel->usePotion(oPlayer, iMaxHP, true);
					//cout << "You used a potion to recover 0 health!" << endl;
					//cout << "Well, that was a waste..." << endl;
				}

				else
				{
					//cout << "Probably a smart decision..." << endl;
				}

*/
				iHPGained = vCurrentDLevel->usePotion(oPlayer, iMaxHP, true);
				vStrings.push_back("You used a potion to recover 0 Health!");
				vStrings.push_back("Well, that was a waste...");
			}


			if(User_Health < iMaxHP)
			{
				stringstream ssHP;
				iHPGained = vCurrentDLevel->usePotion(oPlayer, iMaxHP, false);
				ssHP << iHPGained;
				string sHPGained = ssHP.str();
				vStrings.push_back("You used a poition to recover " + sHPGained + " health!");
			}

		}


	}

	//Inventory Possibility:
	if(cUserChar == 'I' || cUserChar == 'i')
	{
		displayInventory(oPlayer, vStrings);
		sCommand = "Looking at inventory...";
	}




	//Rules Possibility:
	if(cUserChar == 'R' || cUserChar == 'r')
	{
		displayRules(false, vStrings);
		sCommand = "Displaying Rules...";
	}


	//Calculate Monster movement
	bool CreatureAdj = false;
	//Check if Creature is adjacent
	CreatureAdj = vCurrentDLevel->movementAttack(oPlayer, cUserChar);

		//If the creature isn't adjacent use movement function
		if(CreatureAdj == false)
		{
			vCurrentDLevel->moveCreature(oPlayer);
		}
		//If they are then use attack method

		if(CreatureAdj == true)
		{
			vCurrentDLevel->CreatureAttack(oPlayer, cUserChar, vStrings);
			//vStrings.push_back("Creature just attacked you for damage!");
		}


	//End Game State Possibilty: User's health reaches 0
	if(oPlayer->getHealth() < 1)
	{
		sEndState = "died";
		bGameEnd = true;
	}

	//increment turn count 
	if((iTurnCount % 50) == 0)
	{
		vCurrentDLevel->generateObjects(1, "Creature", false);
		vCurrentDLevel->placeObjects(mt, true);
	}

	healthManagement(oPlayer, iMaxHP, iTurnCount);



	}while((iCommand != 'q') && (bGameEnd == false));

	endwin();

	cout << endl;

	//End State Code

	if(sEndState == "quit")
	{
		//"quit"
		cout << "You quitter! You Scored " << oPlayer->getExperience() << " points over the course of " << iTurnCount << " turns!" << endl;
	}

	if (sEndState == "exit")
	{
		//"exit"
		cout << "You escaped the dungeon! " << endl;
		cout << "Congrats " << oPlayer->getName() << ", you scored  " << oPlayer->getExperience() << " points in " << iTurnCount << " turns, and killed " << iBodyCount << " creatures!" << endl; 
	}

	if (sEndState == "died")
	{
		//"died
		cout << "You died! How sad...  "  << "	Score: " << oPlayer->getExperience() << endl;
	}


	return 0;

}

