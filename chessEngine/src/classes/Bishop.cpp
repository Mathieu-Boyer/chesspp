#include "Bishop.hpp"
#include "APiece.hpp"

Bishop::Bishop() : APiece(){
    this->name           = "Bishop";
    this->color          = "ColorLess";
    this->capturable     = false;
    this->moveSet        = { -9, -7, 7, 9};
    this->captureMoveSet = moveSet;
    this->specialMoveSet = {};
    this->range          = 8;
    this->value          = 3;
    this->canJump        = false;
}

std::unique_ptr<APiece> Bishop::clone(){
    return std::make_unique<Bishop>(*this);
}