#include "Queen.hpp"
#include "APiece.hpp"

Queen::Queen(const std::string &color) : APiece("Queen", "Q", color, 10 , 8, false , true){
    this->moveSet        = { -9, -8, -7, 1, 7, 8 , 9 , -1 };
    this->captureMoveSet = moveSet;
    this->specialMoveSet = {};
}


std::vector<int> Queen::getPseudoLegalMoves(GameState &gameState, int position){
    std::vector<int> freeSquareMoves;
    Board &board = gameState.getRefToBoard();

    for (auto& move : moveSet){
        if (move != 0){
            for(int n = 1; n <= this->getRange() ; ++n){
                int square = (position + (n * move));
                APiece *pieceOnSquare = board.getPieceAt(square);
                if (!validSquare(square))
                    break;
                if (horizontalMove(move) && horizontalOverflow(position, square))
                    break;
                if (diagonalMove(move) && diagonalMoveOverFlow(position , square))
                    break;

                if (pieceOnSquare != nullptr && (pieceOnSquare->getCapturable()) && (this->getColor() != pieceOnSquare->getColor()))
                        freeSquareMoves.push_back(square);

                if (pieceOnSquare != nullptr)
                    break;
                freeSquareMoves.push_back(square);
            }
        }
    }

    return freeSquareMoves;
}

bool Queen::canAttackSquare(int from, int target, GameState &gameState){
    Board &board = gameState.getRefToBoard();

    for (auto& move : captureMoveSet){
        if (move != 0){
            for(int n = 1; n <= this->getRange() ; ++n){
                int square = (from + (n * move));
                APiece *pieceOnSquare = board.getPieceAt(square);
                if (!validSquare(square))
                    break;
                if (horizontalMove(move) && horizontalOverflow(from, square))
                    break;
                if (diagonalMove(move) && diagonalMoveOverFlow(from , square))
                    break;
                if (square == target)
                    return true;
                if (pieceOnSquare != nullptr)
                    break;
            }
        }
    }
    return false;
}

std::unique_ptr<APiece> Queen::clone(){
    return std::make_unique<Queen>(*this);
}