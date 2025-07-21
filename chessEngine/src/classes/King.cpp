#include "King.hpp"
#include "APiece.hpp"
#include "math.h"
#include "utils.hpp"

King::King(const std::string &color) :  APiece("King","K", color, 0 , 1, false , false){
    this->moveSet        = { -9, -8, -7, 1, 7, 8 , 9, -1 };
    this->captureMoveSet = moveSet;
    this->specialMoveSet = {}; // this is where i will put the castle later.
}


// std::vector<int> King::isAllowedToCastle(int position, Board& board){
//     std::vector<int> toReturn;

//     std::string castlesToFind = this->getColor() == "White" ? "KQ" : "kq";
//     if (board.kingIsInCheck(this->getColor()).size() > 0)
//         return {};

//     for (auto& castle : castlesToFind){
//         if (board.getAllowedCastles().find(castle) != std::string::npos){
//             if ((castle == 'K' || castle == 'k') && isEmptyZone(position, position + 3, board) && !isCompromizedZone(position, position + 3, board, enemyOf(this->getColor())))
//                 toReturn.push_back(position + 2);
//             else if ((castle == 'Q' || castle == 'q') && isEmptyZone(position, position - 4, board) && !isCompromizedZone(position, position -4, board, enemyOf(this->getColor())))
//                 toReturn.push_back(position - 2);
//         }
//     }

//     return toReturn;
// }


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

    // auto foundCastles = isAllowedToCastle(position, board);
    // freeSquareMoves.insert(freeSquareMoves.end(), foundCastles.begin(), foundCastles.end());

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


// std::vector<int> piecesCanCheck(int position, int maxRange, const std::vector<std::string> &slidePieces, std::vector<int> toCheck, Board &board, const std::string& enemyColor){
//     std::vector<int> allCheckers;

//     for (auto& squareToCheck : toCheck)
//         for (int n = 1 ; n <= maxRange ; n++){
//             bool isDiagonalDir = squareToCheck == 7 || squareToCheck == 9 || squareToCheck == -7 || squareToCheck == -9;
//             int square = position + squareToCheck * n;

//             if ((square) < 0 || (square) > 63 || ((squareToCheck == -1 || squareToCheck == 1) && (position / 8 != square / 8)))
//                 break;
//             // std::cout << "checking ----> "<< move::inverseBoardMap.at(square) << std::endl;
//             if (board.getData()[square] == nullptr || ((board.getData()[square]->getName() == "King")))
//                 continue;
//             // if ((board.getData()[position] != nullptr) && (board.getData()[position]->getName() == "King") && (board.getData()[square]->getName() == "King"))
//             //     break;
//             // if (board.getData()[position] != nullptr && board.getData()[position]->getColor() == enemyColor)
//             //     break;
//             if (board.getData()[square]->getColor() != enemyColor)
//                 break;
//             if (board.getData()[square]->getName() == "Pawn" && (board.getData()[position] == nullptr || (board.getData()[square]->canCapture(board,square).size() == 0)))
//                 break;
//             if (board.getData()[square]->getName() == "Knight" && knightMoveOverFlow(position , square))
//                 break;
//             if (isDiagonalDir && (board.getData()[square]->getName() == "Pawn" || board.getData()[square]->getName() == "Bishop" || board.getData()[square]->getName() == "Queen" ) && diagonalMoveOverFlow(position , square))
//                 break;
//             auto slidingPiecesIterator = std::ranges::find((slidePieces), board.getData()[square]->getRepresentation());
//             if (slidingPiecesIterator == slidePieces.end())
//                 break;

//             // if ()
//             // for (auto meow : squareIsCompromised("Black", whiteKingPosition))
//             // std::cout << "---->> "<< move::inverseBoardMap.at(square) << std::endl;
//             allCheckers.push_back(square);
//             break;
//         }
//     return allCheckers;
// }



std::unique_ptr<APiece> King::clone(){
    return std::make_unique<King>(*this);
}