#ifndef _ENDGAME_H_
#define _ENDGAME_H_

#include "CreatureAction.hpp"

class EndGame : public CreatureAction {
    
    public:
        EndGame(std::string name, Creature* owner);

};

#endif