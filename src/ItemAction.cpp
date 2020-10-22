#include "ItemAction.hpp"

ItemAction::ItemAction(Item* _owner){
    owner = _owner;
    std::cout << "ItemAction::ItemAction(" << owner->name << ")" << std::endl;
}