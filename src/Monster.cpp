#include "Monster.hpp"
#include <iostream>

Monster::Monster(){
   //std::cout << "Monster::Monster()" << std::endl;
}

void Monster::setName(std::string _name){
    name = _name;
   //std::cout << "Monster::setName(" << _name << ')' << std::endl;
}

void Monster::setID(int _room, int _serial){
    room = _room;
    serial = _serial;
   //std::cout << "Monster::setID(" << _room << ',' << _serial << ')' << std::endl;
}