#include "ChangedDisplayedType.hpp"

ChangedDisplayedType::ChangedDisplayedType(std::string _name, Creature* _owner) : CreatureAction(_owner) { 
    owner = _owner;
    name = _name;
    //std::cout<<"ChangedDisplayedType::ChangedDisplayedType(" << name << ',' << owner->name << ')' << std::endl;
}
