#include "Teleport.hpp"

Teleport::Teleport(std::string _name, Creature* _owner) : CreatureAction(_owner){ 
    owner = _owner;
    name = _name; 
    std::cout<<"Teleport::Teleport(" << name << ',' << owner->name << ')' << std::endl;
}
