#include "Passage.hpp"
#include <iostream>

Passage::Passage(){
    id1 = 0;
    id2 = 0;
    num_posx = 0;
    num_posy = 0;
    name = "name_to_fill";
    std::cout << "Passage::Passage()" << std::endl;
}

void Passage::setName(std::string new_name){
    name = new_name;
    std::cout << "Passage::setName(" << name << ')' << std::endl;
}

void Passage::setPosX(int data){
    num_posx++;
    posxs.resize(num_posx);
    posxs[num_posx - 1] = data;
    std::cout << "Passage::setPosX(" << data << ')' << std::endl;
}

void Passage::setPosY(int data){
    num_posy++;
    posys.resize(num_posy);
    posys[num_posy - 1] = data;
    std::cout << "Passage::setPosY(" << data << ')' << std::endl;
}


void Passage::setID(int room1, int room2){
    id1 = room1;
    id2 = room2;
    std::cout << "Passage::setID(" << id1 <<',' << id2 << ')' << std::endl;
}