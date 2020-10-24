#ifndef _OBJECTDISPLAYGRID_H_
#define _OBJECTDISPLAYGRID_H_
#include <iostream>
#include <string>
#include "GridChar.hpp"

class ObjectDisplayGrid{
    private:
        int gameHeight;
        int width;
        int topHeight;
        int bottomHeight;
        int height;
        int messages;
        GridChar*** objectGrid;

    public:
        void getObjectDisplayGrid(int gameHeight, int width, int topHeight);
        void setTopMessageHeight(int _topHeight);
        char getchar(int x, int y);
        ObjectDisplayGrid(int _width, int _topHeight, int _gameHeight,int _bottomHeight,int _messages);
        ~ObjectDisplayGrid();
        virtual void update();
        virtual void addObjectToDisplay(GridChar* ch, int x, int y);
        virtual void writeLine(int line, std::string message);
};

#endif