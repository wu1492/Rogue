#ifndef _TELEPORT_H_
#define _TELEPORT_H_

#include "CreatureAction.hpp"

class Teleport : public CreatureAction {
    
    public:
        Teleport(std::string name, Creature* owner);

};

#endif