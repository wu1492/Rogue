#ifndef ITEM_H_
#define ITEM_H_

#include <iostream>
#include <string>
#include "Displayable.hpp"
#include "Creature.hpp"
#include "ItemAction.hpp"

class ItemAction;
class Item : public Displayable{
public:
    std::string name;  // add name
    Creature* owner; // bug, item可以有主人也可以没有，需要解决owner的初始化问题，但不急，可以下次step解决
    std::vector<ItemAction*> actions;
    void setOwner(Creature* owner);
};

#endif /* ITEM_H_ */