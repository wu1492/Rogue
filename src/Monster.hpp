#ifndef _MONSTER_H_
#define _MONSTER_H_

#include "Creature.hpp"

class Monster : public Creature{
    private:

    public:
        Monster();
        void setName(std::string _name);
        void setID(int _room, int _serial);
};

#endif