#include "GameState.hpp"
#include "Board.hpp"

GameState::GameState(const std::string &fen) : raw(fen) {
    decode();
    board.placePieces(data[0]);
}


void GameState::decode(){
    data = split(raw, ' ');
    for (auto &d : data)
        std::cout << d << " " ;
}

std::string GameState::encode(Board) {
    return "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
}

Board GameState::getBoard(){
    return board;
}