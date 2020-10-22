#include "CreatureAction.hpp"
#include "Creature.hpp"


CreatureAction::CreatureAction(Creature* _owner): Action(){
    owner = _owner;
    std::cout << "CreatureAction::CreatureAction(" << owner->name << ')' << std::endl;
}