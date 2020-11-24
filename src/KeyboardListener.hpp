#pragma once
#include "ObjectDisplayGrid.hpp"
#include "Player.hpp"
#include "Creature.hpp"
#include "Dungeon.hpp"
#include "Item.hpp"
#include <vector> 

class KeyboardListener {
private:
    /** Object display grid reference to write errors */
    ObjectDisplayGrid* grid;
    /** set to false to stop running the keyboard listener */
    bool running = false;
    char** map;
    bool is_hallucinate;
    int hallucinate_count;
    Item* sword_worn;
    Item* armor_worn;
    char old;
    Player* player;
    int move_count;

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
    bool move(int x, int y, int old_x, int old_y, Dungeon* dungeon,int topHeight);
    bool detect_monster(int x,int y);
    void creature_action(Creature* crea,CreatureAction* action, std::string name,bool is_player,Dungeon* dungeon,int screen_bottom);
    void display_damage(int x, int y,int player_x, int player_y,Creature* monster,int score,int screen_bottom, Dungeon* dungeon);
};

