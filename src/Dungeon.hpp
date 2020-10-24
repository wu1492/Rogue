#ifndef DUNGEON_H_
#define DUNGEON_H_

#include <string>
#include <vector>
#include "Room.hpp"
#include "Creature.hpp"
#include "Item.hpp"
#include "Passage.hpp"


class Dungeon{
private:
   
    

public:
    Dungeon(std::string _name, int _width,int _gameHeight,int _topHeight, int _bottomHeight);
	std::string name;
    int width;
    int gameHeight;
    int topHeight;
    int bottomHeight;
    std::vector<Room*> rooms; 
    int num_creatures;
	std::vector<Creature*> creatures; 
    int num_passages;
	std::vector<Passage*> passages; 
    int num_items;
	std::vector<Item*> items; 
    int num_rooms;
    void getDungeon(std::string name, int width, int gameHeight);
    void addRoom(Room*);
    void addCreature(Creature);
    void addPassage(Passage*);
    void addItem(Item);

	std::string toString();

};


#endif /* DUNGEON_H_ */
