#include "Queen.hpp"
#include "APiece.hpp"

Queen::Queen() : APiece(){
    this->name           = "Queen";
    this->color          = "ColorLess";
    this->capturable     = false;
    this->moveSet        = { -9, -8, -7, 1, 7, 8 , 9 -1 };
    this->captureMoveSet = moveSet;
    this->specialMoveSet = {};
    this->range          = 8;
    this->value          = 10;
    this->canJump        = false;
}

std::unique_ptr<APiece> Queen::clone(){
    return std::make_unique<Queen>(*this);
}