#ifndef CREATURE_H_
#define CREATURE_H_

// <tricky>circular dependency among classes. ItemAction(Creature owner) & setDeathAction(Creature Actionda)
// https://stackoverflow.com/questions/625799/resolve-build-errors-due-to-circular-dependency-amongst-classes
// might still be buggy

#include <iostream>
#include <string>
#include <vector>
#include "Displayable.hpp"
#include "CreatureAction.hpp"

class CreatureAction;
class Creature: public Displayable{
private:
    
public:
    std::vector<CreatureAction*> deaths;
    std::vector<CreatureAction*> hits;
    //CreatureAction* action;
    std::string name;
    int room;
    int serial;
    int death_size;
    int hits_size;
    bool is_teleport;
    char old_teleport;
    
    Creature();
    void setHp(int h);
    void setHpMoves(int hpm);
    void setDeathAction(CreatureAction* da);
    void setHitAction(CreatureAction* ha);
};

#endif /* CREATURE_H_ */