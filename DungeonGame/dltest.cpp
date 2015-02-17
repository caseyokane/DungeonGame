#include <iostream>
#include <string>
#include <random>
#include <ctime>

#include "DungeonLevel.h"

using namespace std;



void markPosition(vector<string> & vLevel, int x, int y)
{
        if( x < 0 )
                return;

        if( y < 0 )
                return;

        if( y >= vLevel.size() )
                return;

        if( x >= vLevel[y].size() )
                return;

        char cTile = vLevel[y][x];

        if( cTile != '.' && cTile != '#' && cTile != '<' && cTile != '>' )
                return;

        vLevel[y][x] = 'X';

        markPosition(vLevel, x+1, y);
        markPosition(vLevel, x-1, y);
        markPosition(vLevel, x, y+1);
        markPosition(vLevel, x, y-1);
}


bool testLevelConnection(vector<string> & vLevel)
{
	// Display the initial state
	cout << "Initial state: " << endl;
	for( auto it = vLevel.begin(); it != vLevel.end(); it++ )
	{
		cout << (*it) << endl;
	}

	cout << endl;

	int x = -1;
	int y = -1;

	// pick a starting position
	for( int i = 0; i < vLevel.size(); i++ )
	{
		for( int j = 0; j < vLevel[i].size(); j++ )
		{
			if( vLevel[i][j] == '.' || vLevel[i][j] == '#' || vLevel[i][j] == '<' || vLevel[i][j] == '>' )
			{
				// Starting position just has to be a room or
				// tunnel tile
				x = j;
				y = i;
			}
		}
	}

	if( x == -1 )
	{
		cout << "Unable to find starting position!" << endl;
		return false;
	}
	
	// Call the function which actually marks the tiles -- it should mark
	// the starting tile, then any adjacent to it, etc -- so after it's done,
	// everything that can be connected to the starting tile should be
	// marked.
	markPosition(vLevel, x, y);

	bool bCorrect = true;

	cout << endl << "Marked state: " << endl;
	// Outer loop
	for( auto itOuter = vLevel.begin(); itOuter != vLevel.end(); itOuter++ )
	{
		// Inner loop
		for( auto itInner = (*itOuter).begin(); itInner != (*itOuter).end(); itInner++ )
		{
			cout << (*itInner);


			// Now, test if it's a room/tunnel tile -- if it's still
			// one after we've 
			if( (*itInner) == '.' || (*itInner) == '#' || (*itInner) == '<' || (*itInner) == '>' )
			{
				bCorrect = false;
			}
		}

		cout << endl;
	}

	cout << endl;

	if( !bCorrect )
	{
		cout << "Unreached room/tunnel tile detected!" << endl;
	}


	return bCorrect;

}


bool testRoom(DungeonLevel & dl, int x, int y)
{
	// Count room width
	int iWidth = 0;

	for( int i = 0;
		(dl.at(x+i,y) == '.' || dl.at(x+i,y) == '<' || dl.at(x+i,y) == '>') && x+i < 79;
		i++ )
	{
		iWidth++;
	}

	// Count room height

	int iHeight = 0;

	for( int i = 0;
		(dl.at(x,y+i) == '.' || dl.at(x,y+i) == '<' || dl.at(x,y+i) == '>') && y+i < 20;
		i++ )
	{
		iHeight++;
	}

	// Verify that the room is of at least 16 tiles

	if( iHeight * iWidth < 16 )
	{
		cout << "* INVALID ROOM SIZE *" << endl;
		return false;
	}

	// Verify that the room is rectangular -- that is, all
	// of the tiles inside the room are floor or stairs, and
	// all of the tiles immediately around it are not

	for( int j = y - 1; j < y + iHeight + 1; j++ )
	{
		for( int i = x - 1; i < x + iWidth + 1; i++ )
		{
			// (i,j) is a tile in the rectangle that surrounds the room

			// Check to see if (i,j) is outside of the rectangle

			if( i < x || i >= x + iWidth || j < y || j >= y + iHeight )
			{
				// If the tile is outside the range, it's ok
				if( i < 0 || j < 0 || i >= 79 || j >= 20 )
				{
					// Nothing here, we're good
					// (done this way just to make the code a bit
					// more readable; your mileage may vary, though)
				}
				else
				{
					// Check to make sure this tile *isn't* a valid room tile
					if( dl.at(i,j) == '.' || dl.at(i,j) == '<' || dl.at(i,j) == '>' )
					{
						cout << "* INVALID ROOM SHAPE *" << endl;
						return false;
					}
				}
			}
			else
			{
				// Inside the room, make sure that the tiles inside
				// the room are actually room tiles

				if( dl.at(i,j) != '.' && dl.at(i,j) != '<' && dl.at(i,j) != '>' )
				{
					cout << "* INVALID ROOM SHAPE *" << endl;
					return false;
				}
			}
		}


	}

	return true;

}

bool testDungeonLevel(mt19937 & mt)
{
	DungeonLevel dl(79, 20, mt);

	// Counts of the various values we need to
	// keep track of
	int iTileCount = 0;
	int iUpCount = 0;
	int iDownCount = 0;

	// Generate a vector of strings, so we
	// can use the code from Practicum 8
	// to test connectivity

	vector<string> vLevel;

	for( int y = 0; y < 20; y++ )
	{
		vLevel.push_back("");

		for( int x = 0; x < 79; x++ )
		{
			vLevel[y].push_back(dl.at(x,y));

			if( dl.at(x,y) == '.' )
			{
				iTileCount++;
			}
			else if( dl.at(x,y) == '<' )
			{
				iTileCount++;
				iUpCount++;
			}
			else if( dl.at(x,y) == '>' )
			{
				iTileCount++;
				iDownCount++;
			}

			// Check to see if this tile starts a room
			if( dl.at(x,y) == '.' || dl.at(x,y) == '<' || dl.at(x,y) == '>' )
			{
				bool bCheckLeft = (x == 0) || (dl.at(x-1,y) == ' ') || (dl.at(x-1,y) == '#');
				bool bCheckAbove = (y == 0) || (dl.at(x,y-1) == ' ') || (dl.at(x,y-1) == '#');

				if( bCheckLeft && bCheckAbove )
				{
					if( !testRoom(dl, x, y) )
						return false;
				}
			}
		}
	}


	if( testLevelConnection(vLevel) )
	{
		cout << "All tiles connected." << endl;
	}
	else
	{
		cout << "* ALL TILES NOT CONNECTED *" << endl;
		return false;
	}


	cout << "Tiles: " << iTileCount << endl;

	if( iTileCount < 200 )
	{
		cout << "* INVALID TILE COUNT *" << endl;
		return false;
	}

	cout << "Upstairs count: " << iUpCount << endl;

	if( iUpCount != 1 )
	{
		cout << "* INVALID UPSTAIRS COUNT *" << endl;
		return false;
	}

	cout << "Downstairs count: " << iDownCount << endl;
	
	if( iDownCount != 1 )
	{
		cout << "* INVALID DOWNSTAIRS COUNT *" << endl;
		return false;
	}





	return true;
}

int main(int argc, char * argv[])
{
	mt19937 mt;
	mt.seed( time(NULL) );

	int iTestCount = 1;

	if( argc > 1 )
	{
		iTestCount = atoi(argv[1]);
	}

	for( int i = 0; i < iTestCount; i++ )
	{
		testDungeonLevel(mt);
	}

	return 0;
}
