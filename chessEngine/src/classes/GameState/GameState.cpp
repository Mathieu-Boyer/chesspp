#include "GameState.hpp"
#include "Board.hpp"
#include "colors.hpp"

GameState::GameState(const std::string &fen) : raw(fen) , board(std::make_unique<Board>()){
    decode();
    // printASCII();
}

GameState::GameState(const GameState &gameState) : board(gameState.getRefToBoard().clone()){
        this->colorToMove = gameState.colorToMove;
        this->data = gameState.data;
        this->raw = gameState.raw;

        this->currentHalfMove =  gameState.currentHalfMove;
        this->currentFullMove =  gameState.currentFullMove;

        this->colorToMove =  gameState.colorToMove;
        this->possibleEnPassantNow =  gameState.possibleEnPassantNow;
        this->possibleEnPassantNextHalfMove =  gameState.possibleEnPassantNextHalfMove;
        this->dissAllowedCastles =  gameState.dissAllowedCastles;
        this->allowedCastles =  gameState.allowedCastles;
}


void GameState::decode(){
    data = split(raw, ' ');

    setPossibleEnPassantNextHalfMove(0);
    if (data[1] == "w")
        colorToMove = "White";
    else if (data[1] == "b")
        colorToMove = "Black";
    else
        throw std::runtime_error("The provided color does not exist.");

    allowedCastles = data[2];

    if (data[3] != "-"){
        possibleEnPassantNow = move::boardMap.at(data[3]);
    }

    currentHalfMove = std::stoi(data[4]);
    currentFullMove = std::stoi(data[5]);
    board->placePieces(data[0]);
    setColorToMove(colorToMove);
}

std::string GameState::encode() {

    std::string fenString;
    std::string boardAsString ;
    int spaceCounter = 0;

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

    for (auto character : getdissAllowedCastles())
        this->data[2].erase(std::remove(this->data[2].begin(), this->data[2].end(), character), this->data[2].end());

    if ( this->data[2].empty()){
        this->data[2] = "-";
    }
    if (getPossibleEnPassantNextHalfMove() )
        this->data[3] = move::inverseBoardMap.at(getPossibleEnPassantNextHalfMove());
    else
        this->data[3] = "-";

    if (this->data[1] == "w"){
        setCurrentFullMove(getCurrentFullMove() + 1);
        data[5] = std::to_string(currentFullMove);
    }

    data[4] = std::to_string(currentHalfMove);
    for (auto&fenElement : data)
        fenString += fenElement + " ";

    return fenString;
}

Board &GameState::getRefToBoard() const{
    return *board;
}

std::vector<int> GameState::squareIsCompromised(const std::string &enemy, int target){

    Board &board = getRefToBoard();
    std::vector<int> positionsOfAllCheckers;

    for (int i = 0 ; i < 64; i++){
        APiece *currentPiece = board.getPieceAt(i);

        if (currentPiece == nullptr || currentPiece->getColor() != enemy || currentPiece->getName() == "King")
            continue;
        if (currentPiece->canAttackSquare(i, target, *this)){
            positionsOfAllCheckers.push_back(i);
        }
    }

    return positionsOfAllCheckers;
}



std::vector<int> GameState::getPieceLegalMove(int position){
    if (position > 63 || position < 0)
        throw std::runtime_error("This square does not exist.");

    Board &board = getRefToBoard();
    APiece *piece = board.getPieceAt(position);

    if (piece == nullptr)
        throw std::runtime_error("Selected square is empty.");

    if (piece->getColor() != colorToMove)
        throw std::runtime_error("This is not the turn of the piece you are trying to get the moves from. (" + colorToMove + ")");

    auto pseudoLegal = piece->getPseudoLegalMoves(*this, position);
    std::vector<int> legalMoves;

    for (auto &moveToTry : pseudoLegal){
        GameState gameStateCpy(*this);
        APiece *pieceOfCpyBoard = gameStateCpy.getRefToBoard().getPieceAt(position);

        std::string constructedRawMove = move::inverseBoardMap.at(position)+"-"+move::inverseBoardMap.at(moveToTry);
        if (pieceOfCpyBoard && pieceOfCpyBoard->getName() == "Pawn" && (pieceOfCpyBoard->isOnRow(1, moveToTry) || pieceOfCpyBoard->isOnRow(8, moveToTry))){
            constructedRawMove += "=";
            if (colorToMove == "White")
                constructedRawMove += "Q";
            else
                constructedRawMove += "q";
        }
        move move(constructedRawMove);
        gameStateCpy.applyMoveSimulation(move);
        if (gameStateCpy.kingIsInCheck(colorToMove).size() == 0){
            legalMoves.push_back(moveToTry);
        }
    }
    return legalMoves;
}

void GameState::applyMove(const move &move){

    Board &board = getRefToBoard();
    APiece *piece = board.getPieceAt(move.from);

    if (piece == nullptr)
        throw std::runtime_error("The " + move::inverseBoardMap.at(move.from) + " 'From' square is empty");

    auto legalMoves = getPieceLegalMove(move.from);
    if (std::ranges::find(legalMoves, move.to) == legalMoves.end()){
        throw std::runtime_error("The move : " + move::inverseBoardMap.at(move.to) + " illegal ! you are going to jail.");
    }
    this->board->applyMove(move, *this);
}

void GameState::applyMoveSimulation(const move &move){
    this->board->applyMove(move, *this);
}