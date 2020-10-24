#ifndef _ROOM_H_
#define _ROOM_H_

#include "Structure.hpp"
#include "Creature.hpp"
#include "Item.hpp"
#include <iostream>
#include <vector>

class Room : public Structure{
    private:
        
    public:
        int room; // id
        std::string name;
        int creature_size;
        int item_size;
        std::vector<Creature*> creatures;
        Room(std::string);
        void setId(int room);
        void setCreature(Creature* Monster);
        void setItem(Item* item);
        std::vector<Item*> items;
};

#endif