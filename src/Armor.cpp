#include "Armor.hpp"
#include <iostream>

Armor::Armor(std::string _name):Item(){
    setName(_name);
    //std::cout<<"Armor(" << _name << ")" << std::endl;
}

void Armor::setID(int _room, int _serial){
    room = _room;
    serial = _serial;
    //std::cout<<"Armor::setID(" << room << ',' << serial<< ")" << std::endl;
}

void Armor::setName(std::string _name){
    name = _name;
    //std::cout<<"Armor::setName(" << _name << ")" << std::endl;
}