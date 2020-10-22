#ifndef DISPLAYABLE_H_
#define DISPLAYABLE_H_

#include <iostream>
class Displayable{
    public:
        int visible;
        int maxhit;
        int posX;
        int posY;
        int hp;
        int hpMoves;
        char type;
        int width;
        int height;
        int ivalue; //int value
        
        Displayable();
        void setInvisible();
        void setVisible();
        void setMaxHit(int maxHit);
        void setHpMove(int hpMoves);
        void setHp(int Hp);
        void setType(char t);
        void setIntValue(int v);
        virtual void setPosX(int x);
        virtual void setPosY(int y);
        void setWidth(int x);
        void setHeight(int y);
};

#endif /* DISPLAYABLE_H_ */