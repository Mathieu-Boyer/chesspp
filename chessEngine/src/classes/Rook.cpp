#include "Rook.hpp"

Rook::Rook(const std::string &color) : APiece("Rook", "R", color, 5 , 8, false , true){
    this->moveSet        = {-1, -8, +1, +8};
    this->captureMoveSet = moveSet;
    this->specialMoveSet = {};
}

std::vector<int> Rook::getPseudoLegalMoves(GameState &gameState, int position){
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

bool Rook::canAttackSquare(int from, int target, GameState &gameState){
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

                if (square == target)
                    return true;
                if (pieceOnSquare != nullptr)
                    break;
            }
        }
    }
    return false;
}

void Rook::specialEffects(move move, GameState &gameState){

    Board &board = gameState.getRefToBoard();

    if (gameState.getAllowedCastles() != "-"){
        if (this->getColor() == "White"){
            if (move.from > board.getWhiteKingPosition())
                gameState.setdissAllowedCastles(gameState.getdissAllowedCastles() += "K");
            else
                gameState.setdissAllowedCastles(gameState.getdissAllowedCastles() += "Q");

        }else{
            if (move.from > board.getBlackKingPosition())
                gameState.setdissAllowedCastles(gameState.getdissAllowedCastles() += "k");
            else
                gameState.setdissAllowedCastles(gameState.getdissAllowedCastles() += "q");
        }
    }
}



std::unique_ptr<APiece> Rook::clone(){
    return std::make_unique<Rook>(*this);
}