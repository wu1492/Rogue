#ifndef _PASSAGE_H_
#define _PASSAGE_H_

#include "Structure.hpp"
#include <vector>

class Passage : public Structure{
    private: 

    public:
        int id1; // move out of private for sake of dungeon function
        int id2; // move out of private for sake of dungeon function
        std::string name; // move out of private for sake of dungeon function
        std::vector<int> posxs;
        int num_posx;
        int num_posy;
        std::vector<int> posys;
        Passage();  //Monster( )
        virtual void setPosX(int);
        virtual void setPosY(int);
        void setName(std::string new_name);
        void setID(int room1, int room2);

};

#endif