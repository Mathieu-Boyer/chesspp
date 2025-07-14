#include "APiece.hpp"

void APiece::describe(){
    std::cout << "[ " << name << " ]" << " details : { " << "value : " << value << ", range : " << range << ", canJump : " << canJump << ", capturable : " << capturable << " }";
}