#include "GameState.hpp"
#include "Board.hpp"

GameState::GameState(const std::string &fen, Board &board) : raw(fen) , board(board){
    decode();
    board.placePieces(data[0]);
}


void GameState::decode(){
    data = split(raw, ' ');
}

std::string GameState::encode() {

    std::string fenString;
    std::string boardAsString ;
    int spaceCounter = 0;
    int counter = 0;
    for (auto& piece : this->board.getData()){
        if (piece == nullptr){
            if (spaceCounter > 0 && spaceCounter % 8 == 0){
                boardAsString += '/';
                boardAsString += (char)('0' + spaceCounter);
                spaceCounter = 0;
            }
            spaceCounter++;
            counter++;
            continue;
        }
        if (spaceCounter > 0){
            boardAsString += '/';
            boardAsString += (char)('0' + spaceCounter);
            spaceCounter = 0;
        }

        if (counter > 0 && counter % 8 == 0){
            boardAsString += '/';
        }
        boardAsString += piece->getRepresentation();
        counter++;
    }

    this->data[0] = boardAsString;

    for (auto&fenElement : data)
        fenString += fenElement + " ";
    return fenString;
}

Board &GameState::getBoard(){
    return board;
}