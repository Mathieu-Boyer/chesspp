#include "GameState.hpp"

std::vector<int> GameState::kingIsInCheck(const std::string &color){
    Board &board = getRefToBoard();

    std::vector<int> compromised;

    if (color == "White")
        compromised = squareIsCompromised("Black", board.getWhiteKingPosition());
    else
        compromised = squareIsCompromised("White", board.getBlackKingPosition());

    if (compromised.size() > 0 && moveConstruction.back() != '+'){
        moveConstruction +=  "+";
    }
    return compromised;
}

bool GameState::moreThan1PieceCanCheck(const std::string &color){
    Board &board = getRefToBoard();
    if (color == "White")
        return squareIsCompromised("Black", board.getWhiteKingPosition()).size() > 1;
    else
        return squareIsCompromised("White", board.getBlackKingPosition()).size() > 1;
}


bool GameState::checkIngPieceCanBeCaptured(const std::string &color, int positionOfChecker){
    if (color == "White")
        return squareIsCompromised("Black", positionOfChecker).size() > 0; 
    else
        return squareIsCompromised("White", positionOfChecker).size() > 0;
}

bool diagonalInterpositionCheck(GameState& gameState, int pieceA, int pieceB, const std::string& interposeColor){
    
    int rankA = pieceA / 8;
    int rankB = pieceB / 8;
    int fileA = pieceA % 8;
    int fileB = pieceB % 8;

    if (std::abs(rankA - rankB) != std::abs(fileA - fileB))
        return false;

    int pieceDifference = std::abs(pieceA - pieceB);

    if (!(pieceDifference % 7 == 0 || pieceDifference % 9 == 0))
        return false;

    int orientation = (pieceDifference % 7 == 0) ? 7 : 9;
    int direction = (pieceA > pieceB ? -1 : 1);
    int step = orientation * direction;
    
    for (int i = pieceA + step; i != pieceB; i += step) {
        std::vector<int> piecesCanInterpose = gameState.squareIsCompromised(interposeColor, i);
        
        for (int piecePos : piecesCanInterpose) {
            GameState gameStateCpy(gameState);
            APiece *pieceToMove = gameStateCpy.getRefToBoard().getPieceAt(piecePos);
            
            if (pieceToMove) {
                std::string constructedRawMove = move::inverseBoardMap.at(piecePos) + "-" + move::inverseBoardMap.at(i);

                if (pieceToMove->getName() == "Pawn" && (pieceToMove->isOnRow(1, i) || pieceToMove->isOnRow(8, i))) {
                    constructedRawMove += "=";
                    constructedRawMove += (gameStateCpy.getColorToMove() == "White") ? "Q" : "q";
                }
                
                move moveToTest(constructedRawMove);
                gameStateCpy.applyMoveSimulation(moveToTest);

                if (gameStateCpy.kingIsInCheck(gameStateCpy.getColorToMove()).size() == 0) {
                    return true;
                }
            }
        }
    }
    
    return false;

}

bool orthogonalInterpositionCheck(GameState& gameState, int pieceA, int pieceB, const std::string& interposeColor) {
    int rankA = pieceA / 8;
    int rankB = pieceB / 8;
    int fileA = pieceA % 8;
    int fileB = pieceB % 8;

    if (!(rankA == rankB || fileA == fileB))
        return false;

    int step;
    if (rankA == rankB)
        step = (pieceA > pieceB) ? -1 : 1;
    else
        step = (pieceA > pieceB) ? -8 : 8;

    for (int i = pieceA + step; i != pieceB; i += step) {
        std::vector<int> piecesCanInterpose = gameState.squareIsCompromised(interposeColor, i);
        
        for (int piecePos : piecesCanInterpose) {
            GameState gameStateCpy(gameState);
            APiece *pieceToMove = gameStateCpy.getRefToBoard().getPieceAt(piecePos);
            
            if (pieceToMove) {
                std::string constructedRawMove = move::inverseBoardMap.at(piecePos) + "-" + move::inverseBoardMap.at(i);
                if (pieceToMove->getName() == "Pawn" && (pieceToMove->isOnRow(1, i) || pieceToMove->isOnRow(8, i))) {
                    constructedRawMove += "=";
                    constructedRawMove += (gameStateCpy.getColorToMove() == "White") ? "Q" : "q";
                }
                
                move moveToTest(constructedRawMove);
                gameStateCpy.applyMoveSimulation(moveToTest);

                if (gameStateCpy.kingIsInCheck(gameStateCpy.getColorToMove()).size() == 0) {
                    return true;
                }
            }
        }
    }
    
    return false;
}

bool GameState::pieceCanInterpose(int pieceA, int pieceB, const std::string &pieceName, const std::string& interposeColor){
    if (pieceName != "Queen" && pieceName != "Rook" && pieceName != "Bishop")
        return false;
    if (pieceName == "Bishop")
        return diagonalInterpositionCheck(*this, pieceA, pieceB, interposeColor);
    else if (pieceName == "Rook")
        return orthogonalInterpositionCheck(*this, pieceA, pieceB, interposeColor);
    else{
        return diagonalInterpositionCheck(*this, pieceA, pieceB, interposeColor) || orthogonalInterpositionCheck(*this, pieceA, pieceB, interposeColor);
        
    }
}


bool GameState::checkMateSituation(const std::string &color){

    Board &board = getRefToBoard();
    std::string enemy = enemyOf(color);
    int kingPosition = (color == "White" ? board.getWhiteKingPosition() : board.getBlackKingPosition());

    std::vector<int> kingCheckers = kingIsInCheck(color);
    if (kingCheckers.size() == 0)
        return false;
    if (getPieceLegalMove(kingPosition).size() > 0)
        return false;
    if (moreThan1PieceCanCheck(color)){

        if (board.tryMovingKingToPrince(*this))
            return false;

        moveConstruction.pop_back();
        moveConstruction +=  "#";
        return true;
    }
    if (checkIngPieceCanBeCaptured(enemy, kingCheckers[0]))
        return false;
    if (pieceCanInterpose(kingPosition, kingCheckers[0], board.getPieceAt(kingCheckers[0])->getName(), color))
        return false;

    if (board.tryMovingKingToPrince(*this))
        return false;
    moveConstruction.pop_back();
    moveConstruction +=  "#";
    return true;
}

int GameState::isDraw(){
    if (currentHalfMove >= 50)
        return gameStatus::halfMoveDraw;
    if (staleMate())
        return gameStatus::staleMate;
    return gameStatus::ongoing;
}

bool GameState::staleMate(){
    std::vector<int> kingCheckers = kingIsInCheck(colorToMove);
    Board &board = getRefToBoard();
    if (kingCheckers.size() > 0)
        return false;
    for (int i = 0; i < 64 ; i++){
        APiece *piece = board.getPieceAt(i);
        if (piece == nullptr || piece->getColor() != colorToMove)
            continue;
        if (getPieceLegalMove(i).size() > 0)
            return false;
    }

    return true;
}


int GameState::checkGameStatus(){
    int status = isDraw();
    // if (status != gameStatus::ongoing)
    //     return status;
    if (status == gameStatus::ongoing && checkMateSituation(this->colorToMove))
        status = gameStatus::checkmate;
    return status;

}