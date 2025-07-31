#include "Knight.hpp"

Knight::Knight(const std::string &color) :  APiece("Knight", "N", color, 3 , 1, true , true){
    this->moveSet        = { -17, -15, -6, 10, 17, 15, 6, -10 };
    this->captureMoveSet = moveSet;
    this->specialMoveSet = {};
}



std::vector<int> Knight::getPseudoLegalMoves(GameState &gameState, int position){
    std::vector<int> freeSquareMoves;
    Board &board = gameState.getRefToBoard();

    for (auto& move : moveSet){
        int square = (position + move);
        APiece *pieceOnSquare = board.getPieceAt(square);

        if (!validSquare(square))
            continue;
        if (knightMoveOverFlow(position, square))
            continue;

        if (pieceOnSquare != nullptr && (pieceOnSquare->getCapturable()) && (this->getColor() != pieceOnSquare->getColor()))
            freeSquareMoves.push_back(square);

        
        if (pieceOnSquare != nullptr)
            continue;

        freeSquareMoves.push_back(square);
    }

    return freeSquareMoves;
}


bool Knight::canAttackSquare(int from, int target, GameState &){
    std::vector<int> freeSquareMoves;

    for (auto& move : moveSet){
        int square = (from + move);

        if (!validSquare(square))
            continue;
        if (knightMoveOverFlow(from, square))
            continue;

        if (square == target)
            return true;
    }

    return false;
}

std::unique_ptr<APiece> Knight::clone(){
    return std::make_unique<Knight>(*this);
}