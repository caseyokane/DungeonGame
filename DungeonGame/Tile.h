#ifndef TILE_H_INCLUDED
#define TILE_H_INCLUDED

#include <vector>

#include "Entity.h"

using namespace std;

class Tile

{

public:
	//Default Constructor
	Tile();
	Tile(char symbol, bool passable);

	//getters
	char getChar();
	char getDisplayChar();
	bool getPassable();

	//Enitity * getEntity();

	//Setters
	virtual void setChar(char cInput);
	//Want a display character so that the character with the highest priority char at that position is displayed.
	virtual void setDisplayChar(char cDispInput);
	//virtual void setEntity(Tile * oInputEntity);



private:


	//Symbol of a of a given tile position
	char m_cTileChar;
	//highest priority symbol of a given tile position
	char m_cTileDispChar;
	//Bool representing whether a tile is passable or not.
	bool m_bIsPassable;

	//Also consider a Entity * oEntity which is intialized to NULL, but is set to whatever entity is created for it
	Entity * oEntity;
};


#endif
