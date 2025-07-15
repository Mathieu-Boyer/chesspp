#include "Pawn.hpp"
#include "APiece.hpp"

Pawn::Pawn(const std::string &color) : APiece("Pawn", color, 1 , 1, false , true){
    
    this->moveSet        = color == "White" ? (std::vector<int>){-8, -16} : (std::vector<int>){8, 16};
    this->captureMoveSet = color == "White" ? (std::vector<int>){-9, -7} : (std::vector<int>){7, 9};
    this->specialMoveSet = {};
}

std::unique_ptr<APiece> Pawn::clone(){
    return std::make_unique<Pawn>(*this);
}