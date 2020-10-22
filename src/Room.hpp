#ifndef _ROOM_H_
#define _ROOM_H_

#include "Structure.hpp"
#include "Creature.hpp"
#include <iostream>
#include <vector>

class Room : public Structure{
    private:
        
    public:
        int room; // id
        std::string name;
        int creature_size;
        std::vector<Creature*> creatures;
        Room(std::string);
        void setId(int room);
        void setCreature(Creature* Monster);

};

#endif