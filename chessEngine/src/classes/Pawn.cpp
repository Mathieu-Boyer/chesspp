#include "Pawn.hpp"
#include "APiece.hpp"

Pawn::Pawn(const std::string &color) : APiece("Pawn", "P", color, 1 , 1, false , true){
    
    this->moveSet        = color == "White" ? (std::vector<int>){-8, -16} : (std::vector<int>){8, 16};
    this->captureMoveSet = color == "White" ? (std::vector<int>){-9, -7} : (std::vector<int>){7, 9};
    this->specialMoveSet = {};
}



std::vector<int> Pawn::getPseudoLegalMoves(GameState &gameState, int position){
    std::vector<int> freeSquareMoves;
    Board &board = gameState.getRefToBoard();

    if (!(isOnRow(2, position) || isOnRow(7, position)) && this->moveSet.size() > 1)
        this->moveSet.pop_back();

    for (auto& move : moveSet){
        int square = (position + move);
        APiece *pieceOnSquare = board.getPieceAt(square);

        if (!validSquare(square))
            continue;
        if (horizontalMove(move) && horizontalOverflow(position, square))
            continue;
        if (diagonalMove(move) && diagonalMoveOverFlow(position , square))
            continue;

        if (std::abs(move) == 16 && board.getPieceAt(square + (this->captureMoveSet[0])) != nullptr)
            break;

        // i think the one below is useless for pawns but i'll still make sure later.
        // if (pieceOnSquare != nullptr && (pieceOnSquare->getCapturable()) && (this->getColor() != pieceOnSquare->getColor()) && (std::ranges::find(captureMoveSet, moveSet[moveIndex]) != captureMoveSet.end()))
        //         freeSquareMoves.push_back(square);

        if (pieceOnSquare != nullptr)
            break;

        freeSquareMoves.push_back(square);
    }

    auto foundCaptures = canCapture(gameState, position);
    freeSquareMoves.insert(freeSquareMoves.end(), foundCaptures.begin(), foundCaptures.end());

    return freeSquareMoves;
}


bool Pawn::canAttackSquare(int from, int target, GameState& GameState) {

    for (auto& move : captureMoveSet){
        int square = (from + move);
        APiece *pieceOnSquare = GameState.getRefToBoard().getPieceAt(square);
        if (pieceOnSquare == nullptr)
            continue;
        if (!validSquare(square))
            continue;
        if (horizontalMove(move) && horizontalOverflow(from, square))
            continue;
        if (diagonalMove(move) && diagonalMoveOverFlow(from , square))
            continue;
        // i think the one below is useless for pawns but i'll still make sure later.
        // if (pieceOnSquare != nullptr && (pieceOnSquare->getCapturable()) && (this->getColor() != pieceOnSquare->getColor()) && (std::ranges::find(captureMoveSet, moveSet[moveIndex]) != captureMoveSet.end()))
        //         freeSquareMoves.push_back(square);
        if (square == target)
            return true;
    }

    return false;
}


std::unique_ptr<APiece> Pawn::clone(){
    return std::make_unique<Pawn>(*this);
}