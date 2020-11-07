#include "KeyboardListener.hpp"
#include "Player.hpp"
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector> 
#define STACK dungeon->item_stack_list[*x][*y]

KeyboardListener::KeyboardListener(ObjectDisplayGrid* _grid) : grid(_grid) {}

bool KeyboardListener::move(int x, int y, int old_x, int old_y, char* old, Dungeon* dungeon,int topHeight) {
	char updated_old;
	if(grid->getchar(x,y) != ' ' && grid->getchar(x,y) != 'X'){
		grid->addObjectToDisplay(new GridChar(*old),old_x,old_y);
		*old = grid->getchar(x,y);

		grid->addObjectToDisplay(new GridChar('@'),x,y);
		return true;
	}
	return false;
}

void KeyboardListener::display_damage(int x, int y,Creature* monster,Player* player,int score,int screen_bottom){
	srand(time(NULL));
	int max_hit_mon = monster->maxhit;
	int damage_mon = rand() % (max_hit_mon + 1);
	monster->hp -= damage_mon;
	if(monster->hp < 0){
		grid->addObjectToDisplay(new GridChar('.'),x,y);
		//不确定对不对（我估计没问题）；如果monster死了，就直接用“."替代 
		//wsy:我觉得这个没问题
		grid->writeLine(screen_bottom, "Damage caused by monster = " + std::to_string(damage_mon));
		return;
	}

	int max_hit_player = player->maxhit;
	int damage_player = rand() % (max_hit_player + 1);
	player-> hp -= damage_player;
			
	grid->writeLine(0, "Remaining hp =" + std::to_string(player->hp) + "  Score =" + std::to_string(score));
	grid->writeLine(screen_bottom, "Damage caused by monster = " + std::to_string(damage_mon));

}

bool KeyboardListener::detect_monster(int x,int y){
	char target = grid->getchar(x,y);
	if(target <= 'Z' && target >= 'A' && target != 'X'){
		return true;
	}
	return false;
}

Creature* get_monster(int x, int y, Dungeon* dungeon,int top_length){
	for(int i = 0; i < dungeon->num_creatures;i++){
		if((dungeon->creatures[i]->posX) == x && (dungeon->creatures[i]->posY) == y){
			return dungeon->creatures[i];
		}
	}
	return NULL;
}
// argument: screen_bottom is the #line in the bottom of screen.
void KeyboardListener::run(int* x, int* y,Dungeon* dungeon) {
	Player* player = dungeon->player;
	int score = 0;
	running = true;
	char input;
	char prev_input;
	bool test = false;
	bool approach_monster = false; 
	char old = '.';
	int screen_bottom = dungeon->topHeight + dungeon->gameHeight + dungeon->bottomHeight;
	int topHeight = dungeon->topHeight;
	//bool item_has_been_taken = true;
	if(*x == -1 || *y == -1){
		do{
			prev_input = input;
			input = getchar();
			if(prev_input == 'E'){
				if(input == 'y' || input == 'Y'){
					running = false;
				}
			}
		}while(running && input != EOF);
	}
	else{
		grid->writeLine(0, "Remaining hp:" + std::to_string(player->hp) + "  Score:" + std::to_string(score));
		grid->update();
		do {
			prev_input = input;
			if(player->hp < 0){
				grid->writeLine(1, "Game ended! Please Exit!");
				grid->update();
				do{
					prev_input = input;
					input = getchar();
					if(input == 'y' || input == 'Y'){
						if(prev_input == 'E'){
							return;
						}
					}
				}while(running && input != EOF);
			}
			// wait for next input
			// lowercase so 'x' and 'X' are treated as the same
			input = getchar();
			if(input == 'h'){ //left
				approach_monster = detect_monster(*x-1,*y);

				if(approach_monster){
					Creature* monster = get_monster(*x-1,*y,dungeon,topHeight);
					display_damage(*x-1, *y, monster,player,score,screen_bottom);
				
				}
				else{
					test = move(*x-1,*y,*x,*y,&old,dungeon,topHeight);
					if(test == true){
						*x = *x - 1;						
					}
				}	
				approach_monster = false;
			}
		
			else if(input == 'l'){ //right
				approach_monster = detect_monster(*x+1,*y);

				if(approach_monster){
					Creature* monster = get_monster(*x+1,*y,dungeon,topHeight);
					display_damage(*x+1, *y, monster,player,score,screen_bottom);
				
				}
				else{
					test = move(*x+1,*y,*x,*y,&old,dungeon,topHeight);
					if(test == true){
						*x = *x + 1;						
					}
				}	
				approach_monster = false;
			}
		
			else if(input == 'j'){ // down
				approach_monster = detect_monster(*x,*y+1);

				if(approach_monster){
					Creature* monster = get_monster(*x,*y+1,dungeon,topHeight);
					display_damage(*x, *y+1, monster,player,score,screen_bottom);
				
				}
				else{
					test = move(*x,*y+1,*x,*y,&old,dungeon,topHeight);
					if(test == true){
						*y = *y + 1;						
					}
				}	
				approach_monster = false;
			}

			else if(input == 'k'){ // up
				approach_monster = detect_monster(*x,*y-1);

				if(approach_monster){
					Creature* monster = get_monster(*x,*y-1,dungeon,topHeight);
					display_damage(*x, *y-1, monster,player,score,screen_bottom);
				
				}
				else{
					test = move(*x,*y-1,*x,*y,&old,dungeon,topHeight);
					if(test == true){
						*y = *y - 1;						
					}
				}	
				approach_monster = false;
			}

			else if(input == 'y' || input == 'Y'){
				if(prev_input == 'E'){
					running = false;
				}					
			}
			
			else if(input == 'p'){
				if(old != '.'){
					player->setWeapon(STACK.back()); // STACK is the stack of item list at each point
					STACK.pop_back();
					if(STACK.size() != 0){	
						old = STACK.back()->type;
					}
					else{
						old = '.';
					}
				}
			}

			else if(input <= '9' && input >= '0'){// 目前只能支持一位数字
				if(prev_input == 'd'){ 
					int num = input - '0';
					if(num <= player->item_size){
						STACK.push_back(player->items[num-1]);
						player->items.erase(player->items.begin()+num-1);
						old = STACK.back()->type;
						player->item_size -=1;
					}
				}
			}

			else if(input == 'i'){
				grid->writeLine(screen_bottom -1 , "Player's Pack: ");
				std::string player_item_pack = "";
				for(int p =1; p <= player->item_size; p++){
					player_item_pack += std::to_string(p) + "   ";
					player_item_pack += player->items[p-1]->name;
					player_item_pack += "         " ;
				}
				grid->writeLine(screen_bottom , player_item_pack);
			}

			else if(input == 'E' || input == 'd'){
				// intended to leave for blank
			}

			else{
				std::string message = "Unknown key '";
					message += input;
					grid->writeLine(0, message + "'");
			}
			/*switch (input) {
				case 'h':
					test = move(x-1,y,x,y);
					if(test == true){
						x=x-1;
					}
				case 'l':
					test = move(x+1,y,x,y);
					if(test == true){
						x = x+1;
					}
				case 'j':
					test = move(x,y+1,x,y);
					if(test == true){
						y=y+1;
					}
				case 'k':
					test = move(x,y-1,x,y);
					if(test == true){
						y = y-1;
					}
				case 'E':
					input = std::tolower(getchar());
					if(input == 'y' || input == 'Y'){
						running = false;
					}
				default:
					std::string message = "Unknown key '";
					message += input;
					grid->writeLine(0, message + "'");
			}*/
			grid->update();
		} while (running && input != EOF);
	}

	
}