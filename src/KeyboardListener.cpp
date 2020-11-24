#include "KeyboardListener.hpp"
#include "Player.hpp"
#include "Item.hpp"
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector> 
#define STACK dungeon->item_stack_list[*x][*y]
#define INFO_MSG screen_bottom - 2

/*
	不确定
			
*/

KeyboardListener::KeyboardListener(ObjectDisplayGrid* _grid) : grid(_grid) {}

bool KeyboardListener::move(int x, int y, int old_x, int old_y, Dungeon* dungeon,int topHeight) {
	char updated_old;
	if(map[x][y] != ' ' && map[x][y] != 'X'){
		if(is_hallucinate){
			hallucinate_count -= 1;
		}
		move_count += 1;
		grid->addObjectToDisplay(new GridChar(old),old_x,old_y);
		map[old_x][old_y] = old;
		old = map[x][y];

		grid->addObjectToDisplay(new GridChar(player->type),x,y);
		map[x][y] = player->type;
		player->posX = x;
		player->posY = y;
		return true;
	}
	return false;
}

void KeyboardListener::creature_action(Creature* crea,CreatureAction* action,std::string name,bool is_player,Dungeon* dungeon,int screen_bottom){
	if(name.compare("ChangeDisplayedType") == 0){
		grid->addObjectToDisplay(new GridChar(action->cValue),crea->posX,crea->posY);
		map[crea->posX][crea->posY] = action->cValue;
		crea->type = action->cValue;
		char test = action->cValue;
		std::string s(2,test);
		if(is_player){
			grid->writeLine(INFO_MSG,"The player has changed its displayed type to "+s);
		}
		else{
			grid->writeLine(INFO_MSG,crea->name+" has changed its displayed type to "+s);
		}
	}
	else if(name.compare("Remove") == 0){
		if(crea->is_teleport){
			grid->addObjectToDisplay(new GridChar(crea->old_teleport),crea->posX,crea->posY);
			map[crea->posX][crea->posY]=crea->old_teleport;
		}
		else if(is_player){
			grid->addObjectToDisplay(new GridChar(old),crea->posX,crea->posY);
			map[crea->posX][crea->posY]=old;
		}
		else{
			grid->addObjectToDisplay(new GridChar('.'),crea->posX,crea->posY);
			map[crea->posX][crea->posY] = '.';
		}

		if(is_player){
			grid->writeLine(INFO_MSG,"The player is removed.");
			running = false;
		}
		else{
			grid->writeLine(INFO_MSG,crea->name+" is removed.");
		}
	}
	else if(name.compare("Teleport") == 0){
		srand(time(NULL));
		int a;
		int b;
		
		do{
			a = rand() % (dungeon->width);
			b = rand() % (dungeon->gameHeight);
			
		}while(map[a][b+dungeon->topHeight] != '.' && map[a][b+dungeon->topHeight] != '+' && map[a][b+dungeon->topHeight] != '#');
		grid->addObjectToDisplay(new GridChar(crea->old_teleport),crea->posX,crea->posY);
		map[crea->posX][crea->posY] = crea->old_teleport;
		crea->old_teleport = map[a][b+dungeon->topHeight];
		crea->posX = a;
		crea->posY = b + dungeon->topHeight;
		grid->addObjectToDisplay(new GridChar(crea->type),crea->posX,crea->posY);
		map[crea->posX][crea->posY] = crea->type;
		grid->writeLine(INFO_MSG,action->msg);
	}
	else if(name.compare("UpdateDisplay") == 0){
			if(is_player){
				grid->writeLine(0, "Remaining hp =" + std::to_string(player->hp) + "  Score =" + std::to_string(0));
			}
			grid->update();
			grid->writeLine(INFO_MSG,"Display Updated.");
	}
	else if(name.compare("YouWin") == 0){
		grid->writeLine(INFO_MSG,action->msg);
	}
	else if(is_player){
		if(name.compare("DropPack") == 0){
			if(player->item_size >0){
				if(sword_worn == player->items[0]){
					sword_worn = NULL;
				} 
				else if(armor_worn == player->items[0]){
					armor_worn = NULL;
				}
				dungeon->item_stack_list[crea->posX][crea->posY].push_back(player->items[0]);
				player->items.erase(player->items.begin());
				old = dungeon->item_stack_list[crea->posX][crea->posY].back()->type;
				player->item_size -=1;
				grid->writeLine(INFO_MSG,"The first item in the pack has been dropped");
			}
			else{
				grid->writeLine(INFO_MSG,"DropPack action has activated. But there's nothing in the pack, so nothing is dropped.");
			}
		}
		else if(name.compare("EmptyPack") == 0){
			for(int i = 0;i < player->item_size;i++){
				if(sword_worn == player->items[0]){
				sword_worn = NULL;
				} 
				else if(armor_worn == player->items[0]){
				armor_worn = NULL;
				}
				dungeon->item_stack_list[crea->posX][crea->posY].push_back(player->items[0]);
				player->items.erase(player->items.begin());
				old = dungeon->item_stack_list[crea->posX][crea->posY].back()->type;
				player->item_size -=1;
			}
			grid->writeLine(INFO_MSG,"Every item in the pack has been dropped");
		}
		else if(name.compare("EndGame") == 0){
			grid->writeLine(INFO_MSG,action->msg);
			running = false;
		}
	}
}

void KeyboardListener::display_damage(int x, int y, int player_x, int player_y, Creature* monster,int score,int screen_bottom, Dungeon* dungeon){
	srand(time(NULL));
	int max_hit_mon = player->maxhit;
	int damage_mon;
	if(sword_worn == NULL){
		damage_mon = rand() % (max_hit_mon + 1);
	}
	else{
		damage_mon = rand() % (max_hit_mon + 1) + sword_worn->ivalue;
	}
	monster->hp -= damage_mon;
	for(int i = 0; i < monster->hits_size;i++){
		creature_action(monster,monster->hits[i],monster->hits[i]->name,false,dungeon,screen_bottom);
	}
	if(monster->hp < 0){
		grid->writeLine(INFO_MSG-1, "Damage caused by player to monster = " + std::to_string(damage_mon)+"   "+"No damaged caused by monster to player because monster is dead.");
		//grid->update();
		for(int i = 0; i < monster->death_size;i++){
			creature_action(monster,monster->deaths[i],monster->deaths[i]->name,false,dungeon,screen_bottom);
		}
		return;
	}
	if(monster->is_teleport){
		grid->writeLine(INFO_MSG-1, "Damage caused by player to monster = " + std::to_string(damage_mon)+"   "+"No damaged caused by monster to player because monster is teleported to other place.");
		//grid->update();
		return;
	}
	int max_hit_player = monster->maxhit;
	int damage_player;
	if(armor_worn == NULL){
		damage_player = rand() % (max_hit_player + 1);
	}
	else{
		damage_player = rand() % (max_hit_player + 1) - armor_worn->ivalue;
		if(damage_player < 0){
			damage_player = 0;
		}
	}
	player->hp -= damage_player;
	for(int i = 0; i < player->hits_size;i++){
		creature_action(player,player->hits[i],player->hits[i]->name,true,dungeon,screen_bottom);
	}
	
	if(player->hp < 0) {
		for(int i = 0; i < player->death_size;i++){
			creature_action(player,player->deaths[i],player->deaths[i]->name,true,dungeon,screen_bottom);
		}
	}

	grid->writeLine(0, "Remaining hp =" + std::to_string(player->hp) + "  Score =" + std::to_string(score));
	grid->writeLine(INFO_MSG-1, "Damage caused by player to monster = " + std::to_string(damage_mon)+"   "+"Damaged caused by monster to player = "+ std::to_string(damage_player));

}

bool KeyboardListener::detect_monster(int x,int y){
	char target = map[x][y];
	if(target <= 'Z' && target >= 'A' && target != 'X' || target <= 'z' && target >= 'a' && target != 'X'){
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
	int hallucinate_total;
	move_count=0;
	player = dungeon->player;
	is_hallucinate = false;
	hallucinate_count = 0;
	armor_worn = NULL;
	sword_worn = NULL;
	int score = 0;
	running = true;
	char input;
	char prev_input;
	bool test = false;
	bool approach_monster = false; 
	old = '.';
	int screen_bottom = dungeon->topHeight + dungeon->gameHeight + dungeon->bottomHeight;
	int topHeight = dungeon->topHeight;
	map = new char*[dungeon->width];
	for(int i = 0; i < dungeon->width; i++){
		map[i] = new char[dungeon->gameHeight+dungeon->topHeight];
		for(int j = 0; j < (dungeon->gameHeight+dungeon->topHeight);j++){
			map[i][j] = grid->getchar(i,j);
		}
	}
	if(*x == -1 || *y == -1){
		do{
			prev_input = input;
			input = getchar();
			if(prev_input == 'E'){
				if(input == 'y' || input == 'Y'){
					grid->writeLine(INFO_MSG,"Game ended because of end game command being entered.");
					running = false;
					while(1){

					}
				}
			}
		}while(running && input != EOF);
	}
	else{
		grid->writeLine(0, "Remaining hp:" + std::to_string(player->hp) + "  Score:" + std::to_string(score));
		grid->update();
		do {
			if(is_hallucinate){
				if(hallucinate_count == 0){
					is_hallucinate = false;
					for(int a = 0; a < dungeon->width;a++){
						for(int b = 0; b < dungeon->gameHeight; b++){
							grid->addObjectToDisplay(new GridChar(map[a][b+dungeon->topHeight]),a,b+dungeon->topHeight);
						}
					}
					
				}
				else if(hallucinate_count != hallucinate_total){
					
					int count = player->item_size + dungeon->num_creatures + 3;
					if(dungeon->num_passages > 0){
						count += 2;
					}
					char* objects = (char*) new char[count];
					count = 0;
					objects[0] = '.';
					objects[1] = 'X';
					objects[2] = '@';
					
					if(dungeon->num_passages > 0){
						objects[2] = '+';
						objects[3] = '#';
						count = 5;
					}
					else{
						count = 3;
					}
					
					for(int i = 0; i < player->item_size;i++){
						objects[count] = player->items[i]->type;
						count++;
					}
					for(int i = 0; i < dungeon->num_creatures;i++){
						objects[count] = dungeon->creatures[i]->type;
						count++;
					}
					srand(time(NULL));
					for(int a = 0; a < dungeon->width;a++){
						for(int b = 0; b < dungeon->gameHeight; b++){
							if(map[a][b+dungeon->topHeight] != ' '){
								grid->addObjectToDisplay(new GridChar(objects[rand() % count]),a,b+dungeon->topHeight);
							}
						}
					}
					if(hallucinate_count != 1){
						grid->writeLine(INFO_MSG,"Hallucinate will continue for "+std::to_string(hallucinate_count-1)+" moves.");
					}
					else{
						grid->writeLine(INFO_MSG,"Hallucinate ends.");
					}
				}
				else{
					grid->writeLine(INFO_MSG,"Hallucinate will continue for "+std::to_string(hallucinate_count-1)+" moves.");
				}
				grid->update();
			}
			if(move_count == player->hpMoves){
				move_count = 0;
				player->hp += 1;
			}
			prev_input = input;
			if(player->hp < 0 && running){
				grid->writeLine(INFO_MSG, "Player has been killed! Game ended! Please Exit!");
				grid->update();
				while(1){

				}
			}
			// wait for next input
			// lowercase so 'x' and 'X' are treated as the same
			input = getchar();
			if(input == 'h'){ //left
				approach_monster = detect_monster(*x-1,*y);

				if(approach_monster){
					Creature* monster = get_monster(*x-1,*y,dungeon,topHeight);
					if(monster->hp >= 0){
						display_damage(*x-1, *y, *x, *y, monster,score,screen_bottom,dungeon);
					}
					else{
						test = move(*x-1,*y,*x,*y,dungeon,topHeight);
						if(test == true){
							*x = *x - 1;						
						}
					}
				
				}
				else{
					test = move(*x-1,*y,*x,*y,dungeon,topHeight);
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
					if(monster->hp >= 0){
						display_damage(*x+1, *y, *x, *y, monster,score,screen_bottom,dungeon);
					}
					else{
						test = move(*x+1,*y,*x,*y,dungeon,topHeight);
						if(test == true){
							*x = *x + 1;						
						}
					}
				
				}
				else{
					test = move(*x+1,*y,*x,*y,dungeon,topHeight);
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
					if(monster->hp >= 0){
						display_damage(*x, *y+1,*x, *y,  monster,score,screen_bottom,dungeon);
					}
					else{
						test = move(*x,*y+1,*x,*y,dungeon,topHeight);
						if(test == true){
							*y = *y + 1;						
						}
					}
				
				}
				else{
					test = move(*x,*y+1,*x,*y,dungeon,topHeight);
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
					if(monster->hp >= 0){
						display_damage(*x, *y-1, *x, *y,monster,score,screen_bottom,dungeon);
					}
					else{
						test = move(*x,*y-1,*x,*y,dungeon,topHeight);
						if(test == true){
							*y = *y - 1;						
						}
					}
				
				}
				else{
					test = move(*x,*y-1,*x,*y,dungeon,topHeight);
					if(test == true){
						*y = *y - 1;						
					}
				}	
				approach_monster = false;
			}

			else if(input == 'y' || input == 'Y'){
				if(prev_input == 'E'){
					//running = false;
					grid->writeLine(screen_bottom -2 , "Game has ended because end game command is being entered.");
					grid->update();
					while(1){

					}
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
						for(int i = 0; i < dungeon->num_rooms; i++){
							int posleft = dungeon->rooms[i]->posX;
            				int posright = posleft + dungeon->rooms[i]->width-1;
            				int postop = dungeon->rooms[i]->posY + topHeight;
            				int posbottom = postop + dungeon->rooms[i]->height-1;
							if(*x < posright && *x > posleft && *y > postop && *y < posbottom){
								old = '.';
								break;
							}
							else if(*x < posright && *x > posleft && *y > postop && *y == posbottom){
								old = '+';
								break;
							}
							else if(*x < posright && *x > posleft && *y ==postop && *y < posbottom){
								old = '+';
								break;
							}	
							else if(*x < posright && *x == posleft && *y > postop && *y < posbottom){
								old = '+';
								break;
							}
							else if(*x == posright && *x > posleft && *y > postop && *y < posbottom){
								old = '+';
								break;
							}
						}
						if(old != '+' && old != '.'){
							old = '#';
						}
					}
				}
			}

			else if(input <= '9' && input >= '0'){// 目前只能支持一位数字
				int num = input - '0';
				if(num > player->item_size){
					grid->writeLine(INFO_MSG,"The item you specified does not exist.");
				}
				else{
					if(prev_input == 'd'){
						if(sword_worn == player->items[num-1]){
							sword_worn = NULL;
						} 
						else if(armor_worn == player->items[num-1]){
							armor_worn = NULL;
						}
						STACK.push_back(player->items[num-1]);
						player->items.erase(player->items.begin()+num-1);
						old = STACK.back()->type;
						player->item_size -=1;
						grid->writeLine(screen_bottom -2 , "");
					}
					else if(prev_input == 'r'){
						if(player->items[num-1]->type == '?'){
							if(player->items[num-1]->action->name.compare("BlessArmor") == 0){
								if(player->items[num-1]->action->cValue == 'a'){
									if(armor_worn != NULL){
										grid->writeLine(INFO_MSG,armor_worn->name+" cursed! "+std::to_string(player->items[num-1]->action->iValue)+" taken from its effectiveness.");
										armor_worn->ivalue +=  player->items[num-1]->action->iValue;
									}
									else{
										grid->writeLine(INFO_MSG,"Scroll of cursing does nothing because armor not being used.");
									}
								}
								else if(player->items[num-1]->action->cValue == 'w'){
									if(sword_worn != NULL){
										grid->writeLine(INFO_MSG,sword_worn->name+" cursed! "+std::to_string(player->items[num-1]->action->iValue)+" taken from its effectiveness.");
										sword_worn->ivalue +=  player->items[num-1]->action->iValue;
									}
									else{
										grid->writeLine(INFO_MSG,"Scroll of cursing does nothing because sword not being used.");
									}
								}
							}
							else if(player->items[num-1]->action->name.compare("Hallucinate") == 0){
								is_hallucinate = true;
								hallucinate_count = player->items[num-1]->action->iValue + 1;
								hallucinate_total = hallucinate_count;
							}
							player->items.erase(player->items.begin()+num-1);
							player->item_size -= 1;
						}
						else{
							grid->writeLine(INFO_MSG,"The item you tried to read is not a scroll.");
						}
					}
					else if(prev_input == 'T'){
						if(player->items[num-1]->type == ')'){
							sword_worn = player->items[num-1];
						}
						else{
							grid->writeLine(INFO_MSG,"The item you tried to wield is not a sword.");
						}
					}
					else if(prev_input == 'w'){
						if(player->items[num-1]->type == ']'){
							armor_worn = player->items[num-1];
						}
						else{
							grid->writeLine(INFO_MSG,"The item you tried to wear is not an armor.");
						}
					}
				}
			}

			else if(input == 'i'){
				grid->writeLine(screen_bottom -1 , "Player's Pack: ");
				std::string player_item_pack = "";
				for(int p =1; p <= player->item_size; p++){
					player_item_pack += std::to_string(p) + "   ";
					player_item_pack += player->items[p-1]->name;
					if(player->items[p-1] == armor_worn){
						player_item_pack += "(a)";
					}
					else if(player->items[p-1] == sword_worn){
						player_item_pack += "(w)";
					}
					if(player->items[p-1]->type == ']' || player->items[p-1]->type == ')'){
						player_item_pack += "   value:"+std::to_string(player->items[p-1]->ivalue);
					}
					player_item_pack += "         " ;
				}
				grid->writeLine(screen_bottom , player_item_pack);
			}

			else if(input == 'E' || input == 'd' || input == 'r' || input == 'w' || input == 'T'){
				// intended to leave for blank
			}
			else if(input == 'c'){
				if(armor_worn == NULL){
					grid->writeLine(screen_bottom -2 , "No armor is being worn.");
				}
				else{
					armor_worn = NULL;
				}
			}

			else if(input == '?'){
				grid->writeLine(screen_bottom - 2, "h,l,k,j,i,?,H,c,d,p,r,T,w,E. H <cmd> for more info");
			}
			
			else if(input == 'H'){
				input = getchar();
				if(input == 'c'){
					grid->writeLine(INFO_MSG,"c: Armor that is being worn is taken off and placed it in the pack.");
				} 
				else if(input == 'd'){
					grid->writeLine(INFO_MSG,"d<integer>: Drop item <integer> from the pack, where <integer>-1 is an index into the pack container. ");
				}
				else if(input == 'E'){
					grid->writeLine(INFO_MSG,"E<Y|y>: End the game");
				}
				else if(input == 'h'){
					grid->writeLine(INFO_MSG,"h: Move left 1 space.");
				}
				else if(input == 'l'){
					grid->writeLine(INFO_MSG,"l: Move right 1 space.");
				}
				else if(input == 'k'){
					grid->writeLine(INFO_MSG,"k: Move up 1 space.");
				}
				else if(input == 'j'){
					grid->writeLine(INFO_MSG,"k: Move down 1 space.");
				}
				else if(input == '?'){
					grid->writeLine(INFO_MSG,"?: Show the different commands in the info section of the display.");
				}
				else if(input == 'H'){
					grid->writeLine(INFO_MSG,"H: Give more detailed information about the specified command in the info section of the display.");
				}
				else if(input == 'i'){
					grid->writeLine(INFO_MSG,"i: Show the contents of the pack, printing the name for each item in the pack.");
				}
				else if(input == 'p'){
					grid->writeLine(INFO_MSG,"p<integer>: Pick up the item on the dungeon floor location that the player is standing on and add it to the pack container.");
				}
				else if(input == 'r'){
					grid->writeLine(INFO_MSG,"r<integer>: Read the scroll in the pack. The item specified by the integer must be a scroll that is in the pack. It causes the scroll to perform its actions");
				}
				else if(input == 'T'){
					grid->writeLine(INFO_MSG,"T<ingeter>: Take the sword identified by <integer> from the pack.");
				}
				else if(input == 'w'){
					grid->writeLine(INFO_MSG,"w<integer>: Take the armor identified by <integer> from the pack and make it the armor being worn.");
				}
			}

			else{
				std::string message = "Unknown key '";
					message += input;
					grid->writeLine(INFO_MSG, message + "'");
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
			grid->writeLine(0, "Remaining hp:" + std::to_string(player->hp) + "  Score:" + std::to_string(score));
			if(!is_hallucinate){
				grid->update();
			}
			if(running == false){
				while(1){
					
				}
			}
		} while (running && input != EOF);
	}

	
}