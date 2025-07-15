#include "Queen.hpp"
#include "APiece.hpp"

Queen::Queen(const std::string &color) : APiece("Queen", color, 10 , 8, false , true){
    this->moveSet        = { -9, -8, -7, 1, 7, 8 , 9 -1 };
    this->captureMoveSet = moveSet;
    this->specialMoveSet = {};
}

std::unique_ptr<APiece> Queen::clone(){
    return std::make_unique<Queen>(*this);
}