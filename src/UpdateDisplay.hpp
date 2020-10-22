#ifndef _UPDATEDISPLAY_H_
#define _UPDATEDISPLAY_H_

#include "CreatureAction.hpp"

class UpdateDisplay : public CreatureAction {
    
    public:
        UpdateDisplay(std::string name, Creature* owner);

};

#endif