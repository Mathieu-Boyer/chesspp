#include "GameState.hpp"

std::string GameState::getdissAllowedCastles(){
    return dissAllowedCastles;
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

std::string GameState::getColorToMove(){
    return colorToMove;
}

int GameState::getCurrentHalfMove(){
    return currentHalfMove;;
}

int GameState::getCurrentFullMove(){
    return currentFullMove;
}

std::string GameState::getWhiteQueenInfo(){
    return whiteQueenInfos;
}

std::string GameState::getBlackQueenInfo(){
    return blackQueenInfos;
}

std::string GameState::getLastMovedPiece(){
    return lastMovedPiece;
}

std::string GameState::getMoveConstruction(){
    return moveConstruction;
}

void GameState::setColorToMove(const std::string &color){
    colorToMove = color;
}

void GameState::setdissAllowedCastles(const std::string &dissAllowedCastles){
    this->dissAllowedCastles = dissAllowedCastles;
}

void GameState::setAllowedCastles(const std::string &allowedCastles){
    this->allowedCastles = allowedCastles;
}

void GameState::setPossibleEnPassantNow(int value){
    possibleEnPassantNow = value;
}

void GameState::setCurrentFullMove(int value){
    currentFullMove = value;
}

void GameState::setCurrentHalfMove(int value){
    currentHalfMove = value;
}

void GameState::setWhiteQueenInfo(std::string value){
    whiteQueenInfos = value;
}

void GameState::setBlackQueenInfo(std::string value){
    blackQueenInfos = value;
}

void GameState::setLastMovedPiece(std::string value){
        lastMovedPiece = value;
}

void GameState::setMoveConstruction(std::string value){
    moveConstruction = value;
}

void GameState::setPossibleEnPassantNextHalfMove(int value){
    possibleEnPassantNextHalfMove = value;
}

Board &GameState::getRefToBoard() const{
    return *board;
}