#include "Knight.hpp"
#include "APiece.hpp"

Knight::Knight(const std::string &color) :  APiece("Knight", "N", color, 3 , 1, true , true){
    this->moveSet        = { -17, -15, -6, 10, 17, 15, 6, -10 };
    this->captureMoveSet = moveSet;
    this->specialMoveSet = {};
}

std::unique_ptr<APiece> Knight::clone(){
    return std::make_unique<Knight>(*this);
}