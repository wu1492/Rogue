#ifndef _ITEMACTION_H_
#define _ITEMACTION_H_

#include <iostream>
#include "Action.hpp"
#include "Creature.hpp"
#include "Item.hpp"

class Item;
class ItemAction : public Action {
    public:
        Item* owner;
        ItemAction(Item* owner);
};

#endif 