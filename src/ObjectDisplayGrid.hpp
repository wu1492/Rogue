#ifndef _OBJECTDISPLAYGRID_H_
#define _OBJECTDISPLAYGRID_H_
#include <iostream>

class ObjectDisplayGrid{
    private:
        int gameHeight;
        int width;
        int topHeight;

    public:
        void getObjectDisplayGrid(int gameHeight, int width, int topHeight);
        void setTopMessageHeight(int _topHeight);
        
};

#endif