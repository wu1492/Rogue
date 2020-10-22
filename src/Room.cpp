#include "Room.hpp"

Room::Room(std::string _name){
    name = _name;
    creature_size = 0;
    std::cout << "Room::Room("<< name << ')' << std::endl;
}

void Room::setId(int _room){
    room = _room;
    std::cout << "Room::setId("<< name << ')' << std::endl;
}

void Room::setCreature(Creature* Monster){
    creature_size++;
    creatures.resize(creature_size);
    creatures[creature_size - 1] = Monster;
    std::cout << "Room::setCreature(" << Monster->name << ')' << std::endl;
}