#include "ObjectDisplayGrid.hpp"

//?????
//How to change gameHeight, width?

void ObjectDisplayGrid::getObjectDisplayGrid(int gameHeight, int width, int topHeight){
    std::cout << "ObjectDisplayGrid::getObjectDisplayGrid(" << gameHeight << ',' << width << ',' << topHeight << ')' << std::endl;
}
void ObjectDisplayGrid::setTopMessageHeight(int _topHeight){
    topHeight = _topHeight;
    std::cout << "ObjectDisplayGrid::setTopMessageHeight(" << topHeight << ')'<< std::endl;
}