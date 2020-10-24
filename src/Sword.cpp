#include "Sword.hpp"

Sword::Sword(std::string _name):Item(){
    name = _name;
   //std::cout<<"Sword::Sword(" << _name << ")" << std::endl;
}

void Sword::setID(int _room, int _serial){
    room = _room;
    serial = _serial;
   //std::cout<<"Sword::setID(" << room << ',' << serial<< ")" << std::endl;
}