#include "Cameleon.hpp"
#include "APiece.hpp"
#include "colors.hpp"

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

bool Cameleon::copyCanAttackSquare(char pieceChar ,int from, GameState &gameState, int position){
    const std::string &color = this->getColor();
    std::unique_ptr<APiece> toCpy = pieceFactory(color == "White" ? toupper(pieceChar) : tolower(pieceChar) );
    return toCpy->canAttackSquare(from , position , gameState);
}


std::vector<int> Cameleon::getPseudoLegalMoves(GameState &gameState, int position){
    const std::string lastMovedPiece = gameState.getLastMovedPiece();
    if (lastMovedPiece != "-" && (lastMovedPiece != "c" && lastMovedPiece != "C") &&  (lastMovedPiece != "k" && lastMovedPiece != "K"))
        copyMovesFromPiece(lastMovedPiece.front(), gameState, position);
    const std::string queenInfo = this->getColor() == "White" ? gameState.getWhiteQueenInfo() : gameState.getBlackQueenInfo();
    const std::string capturedPieces = (split(queenInfo, '='))[1];

    for (auto &capturedPiece : capturedPieces)
        copyMovesFromPiece(capturedPiece, gameState, position);

    return this->moveSet;
}

bool Cameleon::canAttackSquare(int from, int target, GameState &gameState){
    const std::string lastMovedPiece = gameState.getLastMovedPiece();
    if (lastMovedPiece != "-" && (lastMovedPiece != "c" && lastMovedPiece != "C") &&  (lastMovedPiece != "k" && lastMovedPiece != "K"))
        if(copyCanAttackSquare(lastMovedPiece.front(), from,  gameState, target)) return true;

    const std::string queenInfo = this->getColor() == "White" ? gameState.getWhiteQueenInfo() : gameState.getBlackQueenInfo();
    const std::string capturedPieces = (split(queenInfo, '='))[1];

    for (auto &capturedPiece : capturedPieces)
        if (copyCanAttackSquare(capturedPiece, from,  gameState, target)) return true;


    return false;
}

void Cameleon::onCaptureEffects(move, GameState &gameState, APiece *capturedPiece){

    if (capturedPiece->getName() != "Cameleon"){
        if(this->getColor() == "White")
            gameState.setWhiteQueenInfo(gameState.getWhiteQueenInfo() + capturedPiece->getRepresentation());
        else
            gameState.setBlackQueenInfo(gameState.getBlackQueenInfo() + capturedPiece->getRepresentation());
    }
    return;
}

void Cameleon::startOfTurnEffects(move , GameState &){
    return ;
}


std::unique_ptr<APiece> Cameleon::clone(){
    return std::make_unique<Cameleon>(*this);
}