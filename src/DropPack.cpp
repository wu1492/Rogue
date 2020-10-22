#include "DropPack.hpp"

DropPack::DropPack(std::string _name, Creature* _owner) : CreatureAction(_owner){
    owner = _owner;
    std::cout<<"DropPack::DropPack(" << name << ',' << owner->name << ')' << std::endl;
}
