#include "EndGame.hpp"

EndGame::EndGame(std::string _name, Creature* _owner) : CreatureAction(_owner){ 
    owner = _owner;
    name = _name; 
   //std::cout<<"EndGame::EndGame(" << name << ',' << owner->name << ')' << std::endl;
}
