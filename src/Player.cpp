#include "Player.hpp"

void Player::setWeapon(Item sword){
    Weapon = sword;
    std::cout << "Player::setWeapon(sword)" << std::endl;
}

void Player::setArmor(Item armor){
    Armor = armor;
    std::cout << "Player::setArmor(armor)" << std::endl;
}