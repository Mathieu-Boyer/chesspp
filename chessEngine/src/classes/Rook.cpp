#include "Rook.hpp"
#include "APiece.hpp"



Rook::Rook() : APiece(){
    this->name = "Rook";
    this->capturable = true;
    this->moveSet = {-1, -8, +1, +8};
    this->captureMoveSet = moveSet;
    this->specialMoveSet = {};
    this->range = 8;
    this->value = 5;
    this->canJump = false;
}

 std::unique_ptr<APiece> Rook::clone(){
    return std::make_unique<Rook>(*this);
 }