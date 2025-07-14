#include "Knight.hpp"
#include "APiece.hpp"

Knight::Knight() : APiece(){
    this->name           = "Knight";
    this->color          = "ColorLess";
    this->capturable     = true;
    this->moveSet        = { -17, -15, -6, 10, 17, 15, 6, -10 };
    this->captureMoveSet = moveSet;
    this->specialMoveSet = {};
    this->range          = 1;
    this->value          = 3;
    this->canJump        = true;
}

std::unique_ptr<APiece> Knight::clone(){
    return std::make_unique<Knight>(*this);
}