#include "GameState.hpp"
#include "Board.hpp"

GameState::GameState(const std::string &fen) : raw(fen) , board(std::make_unique<Board>()){
    decode();
    std::cout << data[1]  << std::endl;
    if (data[1] == "w")
        colorToMove = "White";
    else if (data[1] == "b")
        colorToMove = "Black";
    else
        throw std::runtime_error("The provided color does not exist.");
    
    
    board->setAllowedCastles(data[2]);
    if (data[3] != "-")
        board->setPossibleEnPassantNow(move::boardMap.at(data[3]));
    board->placePieces(data[0]);
    board->setColorToMove(colorToMove);

    if (board->checkMateSituation(this->colorToMove)){
        board->printASCII(*this);
        std::cout << (this->colorToMove == "White" ? "Black" : "White") << " won by mate.";
        std::exit(2);
    }

    if (board->staleMate(colorToMove, *this)){
        board->printASCII(*this);
        std::cout << "Stalemate" << std::endl;
        std::exit(3);
    }

    std::cout << colorToMove << std::endl;
    getRefToBoard().printASCII(*this);

    // std::cout << board.checkMateSituation(this->colorToMove) << " ?????? " << std::endl;
}

GameState::GameState(const GameState &gameState) : board(gameState.getRefToBoard().clone()){
    if (this != &gameState){
        this->colorToMove = gameState.colorToMove;
        this->data = gameState.data;
        this->raw = gameState.raw;
    }

    // std::cout << board.checkMateSituation(this->colorToMove) << " ?????? " << std::endl;
}

// GameState::GameState(const GameState& gameState): board(gameState.board){
//     if (this != &gameState){
//         this->raw = gameState.raw;
//         this->data = gameState.data;
//         this->colorToMove = gameState.colorToMove;
//         // this->board = Board::Board(gameState.board);
//     }
// }


void GameState::decode(){
    data = split(raw, ' ');
}

std::string GameState::encode() {

    std::string fenString;
    std::string boardAsString ;
    int spaceCounter = 0;
    // int counter = 0;


for (int i = 0; i < 64; ++i) {
    const auto& piece = board->getData()[i];

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

    for (auto character : board->getdissAllowedCastles())
        this->data[2].erase(std::remove(this->data[2].begin(), this->data[2].end(), character), this->data[2].end());

    if ( this->data[2].empty()){
        this->data[2] = "-";
    }
    if (board->getPossibleEnPassantNextHalfMove())
        this->data[3] = move::inverseBoardMap.at(board->getPossibleEnPassantNextHalfMove());
    else
        this->data[3] = "-";

    for (auto&fenElement : data)
        fenString += fenElement + " ";

    
    return fenString;
}

Board &GameState::getRefToBoard() const{
    return *board;
}