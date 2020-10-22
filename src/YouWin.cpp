#include "YouWin.hpp"

YouWin::YouWin(std::string _name, Creature* _owner) : CreatureAction(_owner){
    name = _name; 
    owner = _owner;
    std::cout<<"YouWin::YouWin(" << name << ',' << owner->name << ')' << std::endl;
}
