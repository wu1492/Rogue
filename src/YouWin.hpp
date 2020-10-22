#ifndef _YOUWIN_H_
#define _YOUWIN_H_

#include "CreatureAction.hpp"

class YouWin : public CreatureAction {
    
    public:
        YouWin(std::string name, Creature* owner);

};

#endif