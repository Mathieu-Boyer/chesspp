#include "King.hpp"
#include "APiece.hpp"

King::King() : APiece(){
    this->name           = "King";
    this->color          = "ColorLess";
    this->capturable     = false;
    this->moveSet        = { -9, -8, -7, 1, 7, 8 , 9 -1 };
    this->captureMoveSet = moveSet;
    this->specialMoveSet = {}; // this is where i will put the castle later.
    this->range          = 1;
    this->value          = 0;
    this->canJump        = false;
}

std::unique_ptr<APiece> King::clone(){
    return std::make_unique<King>(*this);
}