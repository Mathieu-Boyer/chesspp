#include "King.hpp"
#include "APiece.hpp"

King::King(const std::string &color) :  APiece("King", color, 0 , 1, false , false){
    this->moveSet        = { -9, -8, -7, 1, 7, 8 , 9 -1 };
    this->captureMoveSet = moveSet;
    this->specialMoveSet = {}; // this is where i will put the castle later.
}

std::unique_ptr<APiece> King::clone(){
    return std::make_unique<King>(*this);
}