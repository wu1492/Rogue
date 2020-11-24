#ifndef ACTION_H_
#define ACTION_H_

#include <iostream>
#include <string>

class Action{
    public:
        std::string msg;
        int iValue; // int value
        char cValue; // char value
        std::string name;
        void setMessage(std::string msg);
        void setIntValue(int v);
        void setCharValue(char c);
};

#endif /* ACTION_H_ */