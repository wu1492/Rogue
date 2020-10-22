#include "Hallucinate.hpp"

Hallucinate::Hallucinate(Item* _owner) : ItemAction(_owner){ 
    std::cout<<"Hallucinate::Hallucinate(" << owner->name << ")" << std::endl;
}
