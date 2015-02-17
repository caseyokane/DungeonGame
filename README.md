# DungeonGame
Multi-Class C++ project involving randomized objects and XML Serialization


File Explanations!!!


Armor,Character, Consumable, Creature, Entity, EquipmentFactory, Item, Tile, Tools and Weapon are all 
different classes that are connected together through inheritence so that some items can have similar attributes.

Dlmain is used to create a randomly generate dungeon level object using the dungeon level class.

Dltest is used to test that the randomly generated levels are correct based on prior requirements.

Generic Factory is used to generate objects using the XML serialization and Parser files. 

pa1 was an ealier program that takes and xml file and then builds objects. It can be run, but isn't essential.
Some aspects of it's code were used later in the factory file.

make CaseysDungeon is what creates the the actual executable (CaseysDungeon) which should be run to get 
the desire executable. All rules are then explained following the inital start to the game.

Good luck, have fun!


*DISCLAIMER* Please make sure that you have libncurses5 installed if you want
to run make on the files. I use ncurses to account for movement without priting the results each time. The current executable should run just fine, but if you run make again, please have ncurses installed.
