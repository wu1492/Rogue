#include "KeyboardListener.hpp"
#include <sstream>
#include <iostream>
#include <stdio.h>

KeyboardListener::KeyboardListener(ObjectDisplayGrid* _grid) : grid(_grid) {}

bool KeyboardListener::move(int x, int y, int old_x, int old_y, char* old) {
	if(grid->getchar(x,y) != ' ' && grid->getchar(x,y) != 'X'){
		grid->addObjectToDisplay(new GridChar(*old),old_x,old_y);
		*old = grid->getchar(x,y);
		grid->addObjectToDisplay(new GridChar('@'),x,y);
		return true;
	}
	return false;
}

void KeyboardListener::run(int x, int y) {
	running = true;
	char input;
	bool test = false;
	char old = '.';
	if(x == -1 || y == -1){
		do{
			input = getchar();
			if(input == 'E'){
				input = (getchar());
				if(input == 'y' || input == 'Y'){
					running = false;
				}
			}
		}while(running && input != EOF);
	}
	else{
		grid->writeLine(0, "");
		grid->update();
		do {
			// wait for next input
			// lowercase so 'x' and 'X' are treated as the same
			input = getchar();
			if(input == 'h'){
				test = move(x-1,y,x,y,&old);
				if(test == true){
					x=x-1;
				}
			}else if(input == 'l'){
				test = move(x+1,y,x,y,&old);
				if(test == true){
					x = x+1;
				}
			}else if(input == 'j'){
				test = move(x,y+1,x,y,&old);
				if(test == true){
					y=y+1;
				}
			}else if(input == 'k'){
				test = move(x,y-1,x,y,&old);
				if(test == true){
					y = y-1;
				}
			}else if(input == 'E'){
				input = getchar();
				if(input == 'y' || input == 'Y'){
					running = false;
				}
			}else{
				std::string message = "Unknown key '";
					message += input;
					grid->writeLine(0, message + "'");
			}
			grid->update();
		} while (running && input != EOF);
	}
}