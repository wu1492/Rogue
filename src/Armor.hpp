#ifndef ARMOR_H_
#define ARMOR_H_

#include <iostream>
#include <string>
#include "Item.hpp"
class Armor: public Item{
private:
    
public:
    int room;
    int serial;
    Armor(std::string _name);
    void setID(int room, int serial);
    void setName(std::string);
};

#endif /* ARMOR_H_ */