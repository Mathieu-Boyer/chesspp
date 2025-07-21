#include "APiece.hpp"
#include "utils.hpp"

APiece::APiece(const std::string &name, const std::string &representation, const std::string &color, int value, int range, bool canJump, bool capturable) : _name(name), _color(color), _value(value), _range(range), _canJump(canJump) , _capturable(capturable), _representation(representation){}

void APiece::describe(){
    std::cout << "[ "<< _color << " " << _name << " ]" << " details : { " << "value : " << _value << ", range : " << _range << ", canJump : " << _canJump << ", capturable : " << _capturable << " }" << std::endl;
}

// void APiece::setColor(const std::string &color){
//     this->color = color;
// }

bool APiece::isOnRow(int row, int position){
    // std::cout << position << std::endl;
    return (row == (position / 8) + 1);
}

const std::string APiece::getColor(){
    return _color;
}

bool APiece::getCapturable(){
    return _capturable;
}


std::vector<int> APiece::canCapture(GameState &gameState, int position){
    std::vector<int> allowedCaptures;

    Board &board = gameState.getRefToBoard();
    for (auto &captureMove :  captureMoveSet){
        int square = position + captureMove;
        if (square < 0 || square > 63)
            continue;
        if (this->_name == "Pawn" && (position + moveSet[0]) / 8 != square / 8)
            break;

        APiece *pieceOnSquare = board.getPieceAt(square);
        if (pieceOnSquare != nullptr && pieceOnSquare->getColor() != _color && pieceOnSquare->getCapturable())
            allowedCaptures.push_back(position + captureMove);
        if (square == gameState.getPossibleEnPassantNow())
            allowedCaptures.push_back(position + captureMove);
    }


    return allowedCaptures;
}


// bool APiece::canAttackSquare(int from, int target, GameState &gameState){

//     // std::cout << "color" << std::endl;
//     Board &board = gameState.getRefToBoard();

//     // const auto &moves = gameState.getPieceLegalMove(from);
//     APiece *piece = board.getPieceAt(from);
//     auto moves = piece->getPseudoLegalMoves(gameState, from);
//     if (std::find(moves.begin(), moves.end(), target) != moves.end()){
//         piece->describe();
//         std::cout << move::inverseBoardMap.at(from) << " is attacking " << move::inverseBoardMap.at(target) << std::endl;
//     }


//     // std::cout << std::boolalpha << move::inverseBoardMap.at(from) << "-" << move::inverseBoardMap.at(target) <<( std::find(moves.begin(), moves.end(), target) != moves.end()) << std::endl;
//     return std::find(moves.begin(), moves.end(), target) != moves.end();
// }

// std::vector<int> APiece::getPseudoLegalMoves(GameState &gameState, int position){
//     std::vector<int> freeSquareMoves;

//     if (this->_name == "Pawn"){
//         if (!(isOnRow(2, position) || isOnRow(7, position)) && this->moveSet.size() > 1)
//             this->moveSet.pop_back();
//         auto foundCaptures = canCapture(board, position);

//         // for (auto& lala : foundCaptures)
//             // std::cout << move::inverseBoardMap.at(lala) << " <----- is pseudo legal"<< std::endl;
//         freeSquareMoves.insert(freeSquareMoves.begin(), foundCaptures.begin(), foundCaptures.end());
//     }



//     if (this->_name == "King"){

//         auto foundCastles = isAllowedToCastle(this->_color, position, board);
//         freeSquareMoves.insert(freeSquareMoves.begin(), foundCastles.begin(), foundCastles.end());
//             // break;
//     }
//     int moveIndex = 0;
//     for (auto& move : moveSet){
//         if (move != 0){
//             for(int n = 1; n <= _range ; ++n){
//                 int square = (position + (n * move));
//                 APiece *pieceOnSquare = board.getPieceAt(square);

//                 if (square < 0 || square > 63)
//                     break;
//                 if ((move == -1 || move == 1) && (position / 8 != square / 8))
//                     break;
//                 if (this->_name == "Knight" && knightMoveOverFlow(position, square))
//                     break;
//                 if ((((move != -1 && move != 1 && move != -8 && move != 8)) && diagonalMoveOverFlow(position , square)) && (this->getName() == "Bishop" || this->getName() == "Queen" || this->getName() == "King"))
//                     break;
//                 if (this->getName() == "Pawn" && std::abs(move) == 16 && board.getPieceAt(square + (this->_color == "White" ? 8 : -8)) != nullptr){
//                         // std::cout << move::inverseBoardMap.at(square) << "<----- " << std::endl;
//                         break;
//                 }

//                 if (this->_name == "King" && ((board.squareIsCompromised((this->_color == "White" ? "Black" : "White"), square).size() > 0) || (enemyKingNearby(board , square, this->_color == "White" ? "Black" : "White", {-9, -7, 7, 9, -1 , -8, +1, +8}).size() > 0))){
//                         break;
//                 }
//                 if (pieceOnSquare != nullptr && (pieceOnSquare->getCapturable()) && (this->_color != pieceOnSquare->getColor()) && (std::ranges::find(captureMoveSet, moveSet[moveIndex]) != captureMoveSet.end()))
//                         freeSquareMoves.push_back(square);

//                 if (pieceOnSquare != nullptr)
//                     break;
//                 freeSquareMoves.push_back(square);
//             }
//         }
//         moveIndex++;
//     }

//     return freeSquareMoves;
// }


const std::string APiece::getName(){
    return _name;
}

int APiece::getRange(){
    return _range;
}


bool APiece::getCanJump(){
    return _canJump;
}

const std::string APiece::getRepresentation(){
    return( _color == "White" ? _representation : tolower(_representation));
}