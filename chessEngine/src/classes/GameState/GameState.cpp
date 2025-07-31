#include "GameState.hpp"


GameState::GameState(const std::string &fen) : raw(fen) , board(std::make_unique<Board>()){
    decode();
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
        this->blackQueenInfos = gameState.blackQueenInfos;
        this->whiteQueenInfos = gameState.whiteQueenInfos;
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
        throw std::runtime_error("The move : " + move::inverseBoardMap.at(move.to) + " illegal !");
    }
    this->board->applyMove(move, *this);
}

void GameState::applyMoveSimulation(const move &move){
    this->board->applyMove(move, *this);
}