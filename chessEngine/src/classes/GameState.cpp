#include "GameState.hpp"
#include "Board.hpp"

GameState::GameState(const std::string &fen, Board &board) : raw(fen) , board(board){
    decode();
    std::cout << data[1]  << std::endl;
    if (data[1] == "w")
        colorToMove = "White";
    else if (data[1] == "b")
        colorToMove = "Black";
    else
        throw std::runtime_error("The provided color does not exist.");
    
    
    board.setAllowedCastles(data[2]);
    if (data[3] != "-")
        board.setPossibleEnPassantNow(move::boardMap.at(data[3]));
    board.placePieces(data[0]);
    board.setColorToMove(colorToMove);
}


void GameState::decode(){
    data = split(raw, ' ');
}

std::string GameState::encode() {

    std::string fenString;
    std::string boardAsString ;
    int spaceCounter = 0;
    // int counter = 0;


for (int i = 0; i < 64; ++i) {
    const auto& piece = board.getData()[i];

    if (piece == nullptr) {
        spaceCounter++;
    }
    else {
        if (spaceCounter > 0) {
            boardAsString += std::to_string(spaceCounter);
            spaceCounter = 0;
        }
        boardAsString += piece->getRepresentation();
    }
    if ((i + 1) % 8 == 0) {
        if (spaceCounter > 0) {
            boardAsString += std::to_string(spaceCounter);
            spaceCounter = 0;
        }
        if (i < 63) {
            boardAsString += '/';
        }
    }
}
    this->data[0] = boardAsString;
    this->data[1] = this->data[1] == "w" ? "b" : "w";

    for (auto character : board.getdissAllowedCastles())
        this->data[2].erase(std::remove(this->data[2].begin(), this->data[2].end(), character), this->data[2].end());

    if ( this->data[2].empty()){
        this->data[2] = "-";
    }
    if (board.getPossibleEnPassantNextHalfMove())
        this->data[3] = move::inverseBoardMap.at(board.getPossibleEnPassantNextHalfMove());
    else
        this->data[3] = "-";

    for (auto&fenElement : data)
        fenString += fenElement + " ";

    
    return fenString;
}

Board &GameState::getBoard(){
    return board;
}