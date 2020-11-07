#ifndef SCROLL_H_
#define SCROLL_H_

#include <iostream>
#include <string>
#include "Item.hpp"

class Scroll: public Item{
public:
    int room;
    int serial;
    Scroll(std::string _name);
    void setID(int room, int serial);
};

#endif /* SCROLL_H_ */