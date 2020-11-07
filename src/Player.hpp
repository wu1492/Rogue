#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Creature.hpp"
#include "Item.hpp"
#include <iostream>
#include <vector>

class Player: public Creature{
        
    public:
        std::vector<Item*> items;
        int item_size; 
        void setWeapon(Item* sword);
        void setArmor(Item* armor);
};

#endif