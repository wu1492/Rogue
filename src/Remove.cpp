#include "Remove.hpp"

Remove::Remove(std::string _name, Creature* _owner) : CreatureAction(_owner){ 
    name = _name; 
    owner = _owner;
    std::cout<<"Remove::Remove(" << name << ',' << owner->name << ')' << std::endl;
}
