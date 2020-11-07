#include "Player.hpp"

void Player::setWeapon(Item* sword){
    item_size++;
    items.resize(item_size);
    items[item_size - 1] = sword;
    
}

void Player::setArmor(Item* armor){
    item_size++;
    items.resize(item_size);
    items[item_size - 1] = armor;
   //std::cout << "Player::setArmor(armor)" << std::endl;
}