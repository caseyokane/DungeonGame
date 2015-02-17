OBJECTS = Entity.o Item.o Consumable.o Equipment.o Armor.o Weapon.o Character.o Creature.o Player.o XMLSerializable.o Tile.o DungeonLevel.o GenericFactory.o parser.o Tools.o 
HEADERS = Entity.h Item.h Consumable.h Equipment.h Armor.h Weapon.h Character.h Creature.h Player.h XMLSerializable.h Tile.h DungeonLevel.h GenericFactory.h parser.h Tools.h EntityVector.h



all: dlmain dltest

CaseysDungeon: $(OBJECTS) CaseysDungeon.o
	g++ -g -o CaseysDungeon $^ -lncurses

prog1: $(OBJECTS) pa1.o
	g++ $^ -o prog1

dlmain: $(OBJECTS) dlmain.o
	g++ -o dlmain $^

dltest: $(OBJECTS) dltest.o
	g++ -o dltest $^

%.o: %.cpp $(HEADERS)
	g++ -g -std=c++0x -c $< -o $@

clean:
	rm -f *.o prog1 la5

