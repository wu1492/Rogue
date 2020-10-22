#include "Displayable.hpp"

Displayable::Displayable(){
    std::cout << "Displayable::Displayable()" << std::endl;
}
void Displayable::setInvisible(){
    visible = 0;
    std::cout << "Displayable::setInvisible()" << std::endl;
}
void Displayable::setVisible(){
    visible = 1;
    std::cout << "Displayable::setVisible()" << std::endl;
}
void Displayable::setMaxHit(int _maxhit){
    maxhit = _maxhit;
    std::cout << "Displayable::setMaxHit(" << maxhit << ')' << std::endl;
}
void Displayable::setHpMove(int _hpMoves){
    hpMoves = _hpMoves;
    std::cout << "Displayable::setHpMove(" << hpMoves << ')' << std::endl;
}
void Displayable::setHp(int _Hp){
    hp = _Hp;
    std::cout << "Displayable::setHp(" << hp << ')' << std::endl;
}
void Displayable::setType(char t){
    type = t;
    std::cout << "Displayable::setType(" << t << ')' << std::endl;
}
void Displayable::setIntValue(int v){
    ivalue = v;
    std::cout << "Displayable::setIntValue(" << v << ')' << std::endl;
}
void Displayable::setPosX(int x){
    posX  = x;
    std::cout << "Displayable::setPosX(" << x << ')' << std::endl;
}
void Displayable::setPosY(int y){
    posY = y;
    std::cout << "Displayable::setPosY(" << y << ')' << std::endl;
}
void Displayable::setWidth(int x){
    width = x;
    std::cout << "Displayable::setWidth(" << x << ')' << std::endl;
}
void Displayable::setHeight(int y){
    height = y;
    std::cout << "Displayable::setHeight(" << y << ')' << std::endl;
}