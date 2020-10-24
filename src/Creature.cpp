#include "Creature.hpp"


Creature::Creature(){
    death_size = 0;
    hits_size = 0;
    //std::cout << "Creature::Creature()" << std::endl;
}
void Creature::setHp(int h){
    hp = h;
    //std::cout << "Creature::setHp(" << h << ')' << std::endl;
}
void Creature::setHpMoves(int hpm){
    hpMoves = hpm;
    //std::cout << "Creature::setHpMoves(" << hpm << ')' << std::endl;
}
void Creature::setDeathAction(CreatureAction* da){
    // propabaly bug
    death_size++;
    deaths.resize(death_size);
    deaths[death_size - 1] = da;
    //std::cout << "Creature::setdeathAction( " << da->name <<")" << std::endl;
}
void Creature::setHitAction(CreatureAction* ha){
    hits_size++;
    hits.resize(hits_size);
    hits[hits_size - 1] = ha;
    //std::cout << "Creature::setHitAction( " << ha->name<<")" << std::endl;
}