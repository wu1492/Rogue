#include "UpdateDisplay.hpp"

UpdateDisplay::UpdateDisplay(std::string _name, Creature* _owner) : CreatureAction(_owner){
    owner = _owner;
    name = _name; 
   //std::cout<<"UpdateDisplay::UpdateDisplay(" << name << ',' << owner->name << ')' << std::endl;
}
