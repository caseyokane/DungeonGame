#include "Tile.h"


Tile::Tile()
{
	m_cTileChar = ' ';
	m_cTileDispChar;
	m_bIsPassable = false;
}

Tile::Tile(char symbol, bool passible)
{
	m_cTileChar = symbol;
	m_bIsPassable = passible;
}

char Tile::getChar()
{
	return m_cTileChar;
}

char Tile::getDisplayChar()
{
	return m_cTileDispChar;
}

bool Tile::getPassable()
{
	return m_bIsPassable;
}

void Tile::setChar(char cInput)
{
	m_cTileChar = cInput;
}

void Tile::setDisplayChar(char cDispInput)
{
	m_cTileDispChar = cDispInput;
}
