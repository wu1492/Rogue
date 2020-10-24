#include <iostream>
#include "Item.hpp"
#include "Creature.hpp"

void Item::setOwner(Creature* _owner){
    owner = _owner;
   //std::cout << "setOwner(" << owner->name << ')' << std::endl;
}
