#ifndef CREATUREACTION_H_
#define CREATUREACTION_H_

#include <iostream>
#include "Action.hpp"
#include "Creature.hpp"

class Creature;
class CreatureAction: public Action {
    public:
        Creature* owner;
        CreatureAction(Creature* owner);
};

#endif /* CREATUREACTION_H_ */