#include "GameState.hpp"

void GameState::setColorToMove(const std::string &color){
    colorToMove = color;
}

void GameState::setdissAllowedCastles(const std::string &dissAllowedCastles){
    this->dissAllowedCastles = dissAllowedCastles;
}

std::string GameState::getdissAllowedCastles(){
    return dissAllowedCastles;
}

void GameState::setAllowedCastles(const std::string &allowedCastles){
    this->allowedCastles = allowedCastles;
}

std::string GameState::getAllowedCastles(){
    return allowedCastles;
}


int GameState::getPossibleEnPassantNextHalfMove(){
    return possibleEnPassantNextHalfMove;
}

int GameState::getPossibleEnPassantNow(){
    return possibleEnPassantNow;
}
void GameState::setPossibleEnPassantNextHalfMove(int value){
    possibleEnPassantNextHalfMove = value;
}

void GameState::setPossibleEnPassantNow(int value){
    possibleEnPassantNow = value;
}

std::string GameState::getColorToMove(){
    return colorToMove;
}


void GameState::setCurrentHalfMove(int value){
    currentHalfMove = value;
}

int GameState::getCurrentHalfMove(){
    return currentHalfMove;;
}

void GameState::setCurrentFullMove(int value){
    currentFullMove = value;
}

int GameState::getCurrentFullMove(){
    return currentFullMove;
}