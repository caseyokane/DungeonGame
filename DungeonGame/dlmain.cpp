#include <iostream>
#include <random>
#include <ctime>

#include "DungeonLevel.h"

using namespace std;

int main(int argc, char * argv[])
{
	mt19937 mt;
	mt.seed( time(NULL) );
	DungeonLevel dl(79, 20, mt);

	dl.dump();

	return 0;
}
