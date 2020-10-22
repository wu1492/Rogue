#include "Action.hpp"

void Action::setMessage(std::string _msg){
    msg = _msg;
    std::cout << "Action::setMessage(" << msg << ')'<< std::endl;
}
void Action::setIntValue(int v){
    iValue = v;
    std::cout << "Action::setIntValue(" << v << ')'<< std::endl;
}
void Action::setCharValue(char c){
    cValue = 'a';
    std::cout << "Action::setCharValue(" << c << ')'<< std::endl;
}