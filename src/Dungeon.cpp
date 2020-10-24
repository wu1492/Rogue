#include <iostream>
#include <string>
#include "Dungeon.hpp"

Dungeon::Dungeon(std::string _name, int _width,int _gameHeight,int _topHeight, int _bottomHeight){
    name = _name;
    width = _width;
    gameHeight = _gameHeight;
    topHeight = _topHeight;
    bottomHeight = _bottomHeight;
    num_creatures = 0;
    num_passages = 0;
    num_items = 0;
    num_rooms = 0;
   //std::cout << "Dungeon(" << _name << ',' << _width << ',' << _gameHeight << ',' << _topHeight << ',' << _bottomHeight << ')' << std::endl;
}


//我还没想明白这块到底是咋运作的，你可以研究一下
 void Dungeon::getDungeon(std::string name, int width, int gameHeight){
   //std::cout << "Dungeon::getDungeon(" << name << ',' << width << ',' << gameHeight << ')' << std::endl;
 }
/*
void addRoom(Room){
   //std::cout << "Dungeon::addRoom(Room)" << std::endl;
}
*/

// pointer?
void Dungeon::addRoom(Room* _room)
{
    num_rooms++;
    rooms.resize(num_rooms);
    rooms[num_rooms - 1] = _room;
   //std::cout << "Dungeon::addRoom(" << _room->name << ')' << std::endl; // needs fixing, cout "_creature" kinda cuts corner
}


// buggy
void Dungeon::addCreature(Creature _creature)
{
    num_creatures++;
    creatures.resize(num_creatures);
    creatures[num_creatures - 1] = &_creature;
   //std::cout << "Dungeon::addCreature(" << _creature.name << ')' << std::endl;
}


void Dungeon::addPassage(Passage* _pas){
    num_passages++;
    passages.resize(num_passages);
    passages[num_passages - 1] = _pas;
   //std::cout << "Dungeon::addCreature(Passage)" << std::endl;
}



void Dungeon::addItem(Item _item){
    num_items++;
    items.resize(num_items);
    items[num_items - 1] = &_item;
   //std::cout << "Dungeon::addCreature(" << _item.name << ')' << std::endl;
}


