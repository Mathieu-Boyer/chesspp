#include "APiece.hpp"

APiece::APiece(const std::string &name, const std::string &representation, const std::string &color, int value, int range, bool canJump, bool capturable) : _name(name), _color(color), _value(value), _range(range), _canJump(canJump) , _capturable(capturable), _representation(representation){}

void APiece::describe(){
    std::cout << "[ "<< _color << " " << _name << " ]" << " details : { " << "value : " << _value << ", range : " << _range << ", canJump : " << _canJump << ", capturable : " << _capturable << " }" << std::endl;
}

bool APiece::isOnRow(int row, int position){
    return (row == (position / 8) + 1);
}

std::vector<int> APiece::canCapture(GameState &gameState, int position){
    std::vector<int> allowedCaptures;

    Board &board = gameState.getRefToBoard();
    for (auto &captureMove :  captureMoveSet){
        int square = position + captureMove;
        if (square < 0 || square > 63)
            continue;
        if (this->_name == "Pawn" && (position + moveSet[0]) / 8 != square / 8)
            continue;

        APiece *pieceOnSquare = board.getPieceAt(square);
        if (pieceOnSquare != nullptr && pieceOnSquare->getColor() != _color && pieceOnSquare->getCapturable())
            allowedCaptures.push_back(position + captureMove);
        if (square == gameState.getPossibleEnPassantNow())
            allowedCaptures.push_back(position + captureMove);
    }

    return allowedCaptures;
}

void APiece::specialEffects(move , GameState &){
    return;
}

void APiece::startOfTurnEffects(move, GameState &){
    return;
}


void APiece::endOfTurnEffects(move, GameState &){
    return;
}

void APiece::specialMove(move , GameState &){
    return;
}

void APiece::onCaptureEffects(move, GameState &, APiece *){
    return;
}

void APiece::onCapturedEffects(move, GameState &){
    return ;
}