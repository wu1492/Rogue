#ifndef SWORD_H_
#define SWORD_H_

#include <iostream>
#include <string>
#include "Item.hpp"

class Sword: public Item{
private:
    
public:
    int room;
    int serial;
    Sword(std::string _name);
    void setID(int room, int serial);
};

#endif /* SCROLL_H_ */