#pragma once
#include "ObjectDisplayGrid.hpp"
#include "Player.hpp"
#include "Creature.hpp"
#include "Dungeon.hpp"
#include <vector> 

class KeyboardListener {
private:
    /** Object display grid reference to write errors */
    ObjectDisplayGrid* grid;
    Dungeon* dungeon;
    /** set to false to stop running the keyboard listener */
    bool running = false;

public:
    /**
     * Creates a new keyboard listener, you can pass in extra objects here to interact with them during the game if you wish
     * @param grid  Object display grid reference
     */
    KeyboardListener(ObjectDisplayGrid* grid);

    /**
     * Runs the keyboard listener in a thread
     */
    void run(int* x, int* y,Dungeon* dungeon);
    bool move(int x, int y, int old_x, int old_y, char* old, Dungeon* dungeon,int topHeight);
    bool detect_monster(int x,int y);
    void display_damage(int x, int y,Creature* monster,Player* player,int score,int screen_bottom);
};

