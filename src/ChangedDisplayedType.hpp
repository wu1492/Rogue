#ifndef _CHANGEDDISPLAYEDTYPE_H_
#define _CHANGEDDISPLAYEDTYPE_H_

#include "CreatureAction.hpp"

class ChangedDisplayedType : public CreatureAction {
    
    public:
        ChangedDisplayedType(std::string name, Creature* owner);

};

#endif