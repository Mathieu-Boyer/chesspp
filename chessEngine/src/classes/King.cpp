#include "King.hpp"
#include "APiece.hpp"
#include "math.h"
#include "utils.hpp"

King::King(const std::string &color) :  APiece("King","K", color, 0 , 1, false , false){
    this->moveSet        = { -9, -8, -7, 1, 7, 8 , 9, -1 };
    this->captureMoveSet = moveSet;
    this->specialMoveSet = {-2, 2};
}


std::vector<int> King::isAllowedToCastle(int position, GameState &gameState){
    std::vector<int> toReturn;
    Board &board = gameState.getRefToBoard();

    std::string castlesToFind = this->getColor() == "White" ? "KQ" : "kq";
    if (gameState.kingIsInCheck(this->getColor()).size() > 0)
        return {};

    for (auto& castle : castlesToFind){
        if (gameState.getAllowedCastles().find(castle) != std::string::npos){
            if ((castle == 'K' || castle == 'k') && isEmptyZone(position, position + 3, board) && !isCompromizedZone(position, position + 3, gameState, enemyOf(this->getColor())))
                toReturn.push_back(position + 2);
            else if ((castle == 'Q' || castle == 'q') && isEmptyZone(position, position - 4, board) && !isCompromizedZone(position, position -4, gameState, enemyOf(this->getColor())))
                toReturn.push_back(position - 2);
        }
    }

    return toReturn;
}


std::vector<int> King::getPseudoLegalMoves(GameState &gameState, int position){
    std::vector<int> freeSquareMoves;
    Board &board = gameState.getRefToBoard();

    for (auto& move : moveSet){
        int square = (position +  move);
        APiece *pieceOnSquare = board.getPieceAt(square);

        if (!validSquare(square))
            continue;
        if (horizontalMove(move) && horizontalOverflow(position, square))
            continue;
        if (diagonalMove(move) && diagonalMoveOverFlow(position , square))
            continue;
        if (enemyKingNearby(gameState.getRefToBoard(), square, enemyOf(this->getColor()), this->captureMoveSet))
            continue;

        if (pieceOnSquare != nullptr && (pieceOnSquare->getCapturable()) && (this->getColor() != pieceOnSquare->getColor()))
            freeSquareMoves.push_back(square);
        if (pieceOnSquare != nullptr)
            continue;

        freeSquareMoves.push_back(square);
    }

    auto foundCastles = isAllowedToCastle(position, gameState);
    freeSquareMoves.insert(freeSquareMoves.end(), foundCastles.begin(), foundCastles.end());

    return freeSquareMoves;
}


bool King::canAttackSquare(int from, int target, GameState &){
    std::vector<int> freeSquareMoves;
    for (auto& move : captureMoveSet){
        int square = (from +  move);

        if (!validSquare(square))
            continue;
        if (horizontalMove(move) && horizontalOverflow(from, square))
            continue;
        if (diagonalMove(move) && diagonalMoveOverFlow(from , square))
            continue;
        if (square == target)
            return true;
    }

    return false;
}

void King::endOfTurnEffects(move move, GameState &gameState){

    if (this->getColor() == "White"){
        gameState.getRefToBoard().setWhiteKingPosition(move.to);
        gameState.setdissAllowedCastles("KQ");
    }
    else{
        gameState.getRefToBoard().setBlackKingPosition(move.to);
        gameState.setdissAllowedCastles("kq");
    }
}

void King::specialMove(move move, GameState& gameState){
    gameState.getRefToBoard().applyCastle(move, gameState);
}


std::unique_ptr<APiece> King::clone(){
    return std::make_unique<King>(*this);
}