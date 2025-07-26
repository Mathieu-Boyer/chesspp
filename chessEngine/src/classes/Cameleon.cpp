#include "Cameleon.hpp"
#include "APiece.hpp"

Cameleon::Cameleon(const std::string &color) : APiece("Cameleon", "C", color, 10 , 1, false , true){
    this->moveSet        = {};
    this->captureMoveSet = {};
    this->specialMoveSet = {};
}

void Cameleon::copyMovesFromPiece(char pieceChar , GameState &gameState, int position){
    const std::string &color = this->getColor();
    std::unique_ptr<APiece> toCpy = pieceFactory(color == "White" ? toupper(pieceChar) : tolower(pieceChar) );
    const std::vector<int> movesToCpy = toCpy->getPseudoLegalMoves(gameState, position);
    this->moveSet.insert(moveSet.end(), movesToCpy.begin(), movesToCpy.end());
}


std::vector<int> Cameleon::getPseudoLegalMoves(GameState &gameState, int position){
    const std::string lastMovedPiece = gameState.getLastMovedPiece();
    if (lastMovedPiece != "-" && (lastMovedPiece != "c" && lastMovedPiece != "C") )
        copyMovesFromPiece(lastMovedPiece.front(), gameState, position);
    const std::string queenInfo = this->getColor() == "White" ? gameState.getWhiteQueenInfo() : gameState.getBlackQueenInfo();
    const std::string capturedPieces = (split(queenInfo, '='))[1];

    for (auto &capturedPiece : capturedPieces)
        copyMovesFromPiece(capturedPiece, gameState, position);

    return this->moveSet;
}

bool Cameleon::canAttackSquare(int from, int target, GameState &gameState){
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

void Cameleon::onCaptureEffects(move, GameState &gameState, APiece *capturedPiece){

    if(this->getColor() == "White")
        gameState.setWhiteQueenInfo(gameState.getWhiteQueenInfo() + capturedPiece->getRepresentation());
    else
        gameState.setBlackQueenInfo(gameState.getBlackQueenInfo() + capturedPiece->getRepresentation());
    return;
}

void Cameleon::startOfTurnEffects(move , GameState &){
    return ;
}


std::unique_ptr<APiece> Cameleon::clone(){
    return std::make_unique<Cameleon>(*this);
}