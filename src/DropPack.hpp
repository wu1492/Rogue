#ifndef _DROPPACK_H_
#define _DROPPACK_H_

#include "CreatureAction.hpp"

class DropPack : public CreatureAction {
    
    public:
        DropPack(std::string name, Creature* owner);

};

#endif