#include <curses.h>
#include "ObjectDisplayGrid.hpp"
#ifdef _WIN32
	#include <windows.h>
#endif

void ObjectDisplayGrid::getObjectDisplayGrid(int gameHeight, int width, int topHeight){
    //std::cout << "ObjectDisplayGrid::getObjectDisplayGrid(" << gameHeight << ',' << width << ',' << topHeight << ')' << std::endl;
}
void ObjectDisplayGrid::setTopMessageHeight(int _topHeight){
    topHeight = _topHeight;
    //std::cout << "ObjectDisplayGrid::setTopMessageHeight(" << topHeight << ')'<< std::endl;
}

ObjectDisplayGrid::ObjectDisplayGrid(int _width, int _topHeight, int _gameHeight,int _bottomHeight,int _messages) : width(_width), topHeight(_topHeight), gameHeight(_gameHeight),bottomHeight(_bottomHeight),messages(_messages) {	
	// create the 2D array of grid characters
	// note if you want to write messages instead, ncurses
	objectGrid = new GridChar**[width];
	height = topHeight+gameHeight+bottomHeight;
	for (int i = 0; i < width; i++) {
		objectGrid[i] = new GridChar*[height];
		for (int j = 0; j < height; j++) {
			objectGrid[i][j] = NULL;
		}
	}

	#ifdef _WIN32
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD size = { (short)width, (short)(height + messages) };
		SMALL_RECT DisplayArea = { 0, 0, (short)(size.X - 1), (short)(size.Y - 1) };
		SetConsoleScreenBufferSize(handle, size);
		SetConsoleWindowInfo(handle, TRUE, &DisplayArea);
	#endif	
	
	// initializes ncurses
	initscr();
	// makes characters typed immediately available, instead of waiting for enter to be pressed
	cbreak(); 
	// stops typed characters from being shown, makes it easier to get keypresses
	noecho();
	// clears the screen to start
	clear();
}

ObjectDisplayGrid::~ObjectDisplayGrid() {
	// free memory from the dynamically sized object grid
	for (int i = 0; i < width; i++) {
		// delete all character objects in the grid
		for (int j = 0; j < height; j++) {
			delete objectGrid[i][j];
		}
		// delete the column
		delete[] objectGrid[i];
	}
	// delete the array of columns
	delete[] objectGrid;
	objectGrid = NULL;

	// free ncurses data
	endwin();
}

void ObjectDisplayGrid::addObjectToDisplay(GridChar* ch, int x, int y) {
	// note grid objects start from 0,0 and go until width,height
	// x between 0 and width
	if ((0 <= x) && (x < width)) {
		// y between 0 and height
		if ((0 <= y) && (y < height)) {
			// delete existing character if present
			if (objectGrid[x][y] != NULL) {
				delete objectGrid[x][y];
			}

			// add new character to the internal character list
			objectGrid[x][y] = ch;
			// draws the character on the screen, note it is relative to 0,0 of the terminal
			mvaddch(y, x, ch->getChar());
		}
	}
}

char ObjectDisplayGrid::getchar(int x, int y){
	return objectGrid[x][y]->getChar();	
}

void ObjectDisplayGrid::update() {
	// refreshes ncurses
	refresh();
}

void ObjectDisplayGrid::writeLine(int line, std::string message) {
	// messages start from 0, height and go until width,(height + messages)
	mvaddstr(height + line, 0, message.c_str());
	// clear after what we wrote to EOL
	clrtoeol();
}