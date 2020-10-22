#include "Scroll.hpp"

Scroll::Scroll(std::string _name):Item(){
    name = _name;
    std::cout << "Scroll:: Scroll(" << name << ')' <<std::endl;
}

void Scroll::setID(int _room, int _serial){
    room = _room;
    serial = _serial;
    
    std::cout<<"Scroll::setID(" << room << ',' << serial<< ")" << std::endl;
}