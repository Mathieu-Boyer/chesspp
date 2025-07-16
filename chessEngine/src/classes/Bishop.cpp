#include "Bishop.hpp"
#include "APiece.hpp"

Bishop::Bishop(const std::string &color) : APiece("Bishop","B", color, 3 , 8, false , true){
    this->moveSet        = { -9, -7, 7, 9};
    this->captureMoveSet = moveSet;
    this->specialMoveSet = {};
    
}

std::unique_ptr<APiece> Bishop::clone(){
    return std::make_unique<Bishop>(*this);
}


// before doing anything , make a real construction system please