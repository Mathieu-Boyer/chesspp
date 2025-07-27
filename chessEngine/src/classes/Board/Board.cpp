#include "Board.hpp"
#include "King.hpp"
#include "colors.hpp"
#include "utils.hpp"
#include "GameState.hpp"
#include <memory>

Board::Board(const Board& board){

    whiteKingPosition = board.whiteKingPosition;
    blackKingPosition = board.blackKingPosition;

    unsigned counter = 0;

    for (auto &element : board.data){
        if (element != nullptr){
            this->data[counter] = element->clone();
        }
        counter++;
    }
}

const std::array<std::unique_ptr<APiece>, 64> &Board::getData(){
    return data;
}

int Board::princePosition(const std::string &colorToMove){
    for (unsigned i = 0; i < data.size(); i++){
        APiece *piece = getPieceAt(i);
        if (!piece || piece->getColor() != colorToMove)
            continue;
        if (piece->getName() == "Prince")
            return i;
    }
    return -1;
}

bool Board::tryMovingKingToPrince(GameState &gameState){
    int princePosition = this->princePosition(gameState.getColorToMove());
    int kingPosition = gameState.getColorToMove() == "White" ? getWhiteKingPosition() : getBlackKingPosition() ;
    if (princePosition == -1 || !(gameState.squareIsCompromised(enemyOf(gameState.getColorToMove()), princePosition).empty()))
        return false;
    else {
        data[princePosition] = std::move(data[kingPosition]);
        gameState.getColorToMove() == "White" ? setWhiteKingPosition(princePosition) : setBlackKingPosition(princePosition) ;
        gameState.setdissAllowedCastles(gameState.getColorToMove() == "White" ? "KQ" : "kq");
        gameState.setMoveConstruction(gameState.getMoveConstruction() + "->" + move::inverseBoardMap.at(princePosition));
        return true;
    }
}

void Board::placePieces(const std::string &fen) {

    unsigned counter = 0;
    for (auto &character : fen){
        if (character == '/')
            continue;
        if (std::isdigit(character)){
            counter += character - '0';
            continue;
        }

        data[counter] = pieceFactory(character);
        if (data[counter]->getRepresentation() == "K"){
            whiteKingPosition = counter;
        } else if (data[counter]->getRepresentation() == "k"){
            blackKingPosition = counter;
        }

        counter++;
    }
}

std::unique_ptr<Board> Board::clone() const{
    return std::make_unique<Board> (*this);
}

void Board::applyCastle(const move &move, GameState &gameState){

    if (gameState.getAllowedCastles().find('K') != std::string::npos && move.to == move::boardMap.at("g1"))
        data[move::boardMap.at("f1")] = std::move(data[move::boardMap.at("h1")]);
    else if (gameState.getAllowedCastles().find('k') != std::string::npos && move.to == move::boardMap.at("g8"))
        data[move::boardMap.at("f8")] = std::move(data[move::boardMap.at("h8")]);
    else if (gameState.getAllowedCastles().find('Q') != std::string::npos && move.to == move::boardMap.at("c1"))
        data[move::boardMap.at("d1")] = std::move(data[move::boardMap.at("a1")]);
    else if (gameState.getAllowedCastles().find('q') != std::string::npos && move.to == move::boardMap.at("c8"))
        data[move::boardMap.at("d8")] = std::move(data[move::boardMap.at("a8")]);

    data[move.to] = std::move(data[move.from]);
}

void Board::applyMove(const move &move, GameState& gameState){

    Board &board = gameState.getRefToBoard();
    APiece *currentPiece = board.getPieceAt(move.from);
    APiece *pieceOnTarget = board.getPieceAt(move.to);


    gameState.setLastMovedPiece(std::string(currentPiece->getRepresentation()));
    if (currentPiece->getName() != "Pawn")
        gameState.setMoveConstruction(currentPiece->getRepresentation());

    gameState.setMoveConstruction(gameState.getMoveConstruction() + move::inverseBoardMap.at(move.from));
    if (pieceOnTarget){
        currentPiece->onCaptureEffects(move, gameState, pieceOnTarget);
        pieceOnTarget->onCapturedEffects(move, gameState);
        gameState.setMoveConstruction(gameState.getMoveConstruction() + "x");
        gameState.setCurrentHalfMove(0);
    }
    else{
        gameState.setMoveConstruction(gameState.getMoveConstruction() + "-");
        gameState.setCurrentHalfMove(gameState.getCurrentHalfMove()+1);
    }

    gameState.setMoveConstruction(gameState.getMoveConstruction() + move::inverseBoardMap.at(move.to));

    currentPiece->specialEffects(move, gameState);

    if (std::ranges::find(currentPiece->getSpecialMoveSet(), move.from - move.to) != currentPiece->getSpecialMoveSet().end())
        currentPiece->specialMove(move, gameState);
    else
        data[move.to] = std::move(data[move.from]);

// currentPiece->describe();
    getPieceAt(move.to)->endOfTurnEffects(move, gameState);
}