#include "APiece.hpp"


const std::vector<int> &APiece::getSpecialMoveSet(){
    return specialMoveSet;
}

const std::string APiece::getName(){
    return _name;
}

int APiece::getRange(){
    return _range;
}


bool APiece::getCanJump(){
    return _canJump;
}

const std::string APiece::getColor(){
    return _color;
}

bool APiece::getCapturable(){
    return _capturable;
}

const std::string APiece::getRepresentation(){
    return( _color == "White" ? _representation : tolower(_representation));
}
