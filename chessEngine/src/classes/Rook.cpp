#include "Rook.hpp"
#include "APiece.hpp"

Rook::Rook(const std::string &color) : APiece("Rook", color, 5 , 8, false , true){
    this->moveSet        = {-1, -8, +1, +8};
    this->captureMoveSet = moveSet;
    this->specialMoveSet = {};
}

std::unique_ptr<APiece> Rook::clone(){
    return std::make_unique<Rook>(*this);
}