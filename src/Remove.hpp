#ifndef _REMOVE_H_
#define _REMOVE_H_

#include "CreatureAction.hpp"

class Remove : public CreatureAction {
    
    public:
        Remove(std::string name, Creature* owner);

};

#endif