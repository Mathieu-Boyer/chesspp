#include "Pawn.hpp"
#include "APiece.hpp"

Pawn::Pawn(const std::string &color) : APiece("Pawn", "P", color, 1 , 1, false , true){
    
    this->moveSet        = color == "White" ? (std::vector<int>){-8 , -16} : (std::vector<int>){8 , 16};
    this->captureMoveSet = color == "White" ? (std::vector<int>){-9, -7} : (std::vector<int>){7, 9};
    this->specialMoveSet = {};
}

std::vector<int> Pawn::getPseudoLegalMoves(GameState &gameState, int position){
    std::vector<int> freeSquareMoves;
    Board &board = gameState.getRefToBoard();

    auto foundCaptures = canCapture(gameState, position);
    freeSquareMoves.insert(freeSquareMoves.end(), foundCaptures.begin(), foundCaptures.end());
    
    for (auto& move : moveSet){
        int square = (position + move);

        if (!validSquare(square))
            continue;

        APiece *pieceOnSquare = board.getPieceAt(square);

        if (horizontalMove(move) && horizontalOverflow(position, square))
            continue;
        
        if ((((this->getColor() == "Black" && !isOnRow(2, position)) || (this->getColor() == "White" && !isOnRow(7, position)))) && (std::abs(move) == 16)){
            continue;
        }

        if (pieceOnSquare != nullptr)
            break;

        freeSquareMoves.push_back(square);
    }

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

        if (square == target)
            return true;
    }

    return false;
}


void Pawn::specialEffects(move move, GameState &gameState){
    Board &board = gameState.getRefToBoard();

    if (abs(move.from - move.to) == 16){
        if ((board.getPieceAt(move.to - 1) != nullptr && squaresAreOnSameRow(move.to,move.to - 1) && board.getPieceAt(move.to - 1)->getName() == "Pawn")){
            if (board.getPieceAt(move.to - 1)->getColor() != this->getColor())
                gameState.setPossibleEnPassantNextHalfMove(this->getColor() == "White" ?  move.to + 8 : move.to - 8);
        }
        if ((board.getPieceAt(move.to + 1) != nullptr && squaresAreOnSameRow(move.to,move.to + 1) && board.getPieceAt(move.to + 1)->getName() == "Pawn")){
            if (board.getPieceAt(move.to + 1)->getColor() != this->getColor())
                gameState.setPossibleEnPassantNextHalfMove(this->getColor() == "White" ?  move.to + 8 : move.to - 8);
        }
    }
    // maybe move to special move later :
    if (move.to == gameState.getPossibleEnPassantNow()){
        this->getColor() == "White" ? board.clearPieceAt(move.to + 8) : board.clearPieceAt(move.to - 8);
        gameState.setPossibleEnPassantNextHalfMove(0);
        gameState.setPossibleEnPassantNow(0);
    }

    if (promotionAssertions(board, move)){
            auto promotedPiece = pieceFactory(move.promotion);
            board.setPieceAt(move.from, std::move(promotedPiece));
            gameState.setMoveConstruction(gameState.getMoveConstruction() + "=" + move.promotion);
    }
    return;
}

void Pawn::endOfTurnEffects(move, GameState &gameState){
    gameState.setCurrentHalfMove(0);
}

std::unique_ptr<APiece> Pawn::clone(){
    return std::make_unique<Pawn>(*this);
}