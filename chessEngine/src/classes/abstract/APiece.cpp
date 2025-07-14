#include "APiece.hpp"

void APiece::describe(){
    std::cout << "[ "<< color << " " << name << " ]" << " details : { " << "value : " << value << ", range : " << range << ", canJump : " << canJump << ", capturable : " << capturable << " }" << std::endl;
}

void APiece::setColor(const std::string &color){
    this->color = color;
}