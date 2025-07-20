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
    std::cout << position << std::endl;
    return (row == (position / 8) + 1);
}

const std::string APiece::getColor(){
    return _color;
}

bool APiece::getCapturable(){
    return _capturable;
}


std::vector<int> APiece::canCapture(Board &board, int position){
    std::vector<int> allowedCaptures;

    for (auto &captureMove :  captureMoveSet){
        int square = position + captureMove;
        if (square < 0 || square > 63)
            continue;
        if (this->_name == "Pawn" && (position + moveSet[0]) / 8 != square / 8)
            break;
        // std::cout << "    " << square << "    " << std::endl;
        if (board.getData()[square] != nullptr && board.getData()[square]->getColor() != _color && board.getData()[square]->getCapturable())
            allowedCaptures.push_back(position + captureMove);
        if (square == board.getPossibleEnPassantNow())
            allowedCaptures.push_back(position + captureMove);
    }


    return allowedCaptures;
}


bool isEmptyZone(int from, int to, Board &board){
    if (from == to)
        std::runtime_error("1 square is not considered a zone.");
    int step   = from < to ? +1 : -1;
    for (int i = from + step; i != to; i += step)
        if (board.getData()[i] != nullptr)
            return false;
    return true;
}


bool isCompromizedZone(int from, int to, Board &board, const std::string& enemy){
    if (from == to)
        std::runtime_error("1 square is not considered a zone.");

    int step   = from < to ? +1 : -1;
    for (int i = from + step; i != to; i += step){
        auto result = board.squareIsCompromised(enemy, i);
        // std::cout << "is " << move::inverseBoardMap.at(i) << " compromised ? " << result << std::endl;
        if (result.size() > 0)
            return true;
    }

    return false;
}


std::vector<int> isAllowedToCastle(const std::string &color,int position, Board& board){
    std::vector<int> toReturn;
    std::string castlesToFind = color == "White" ? "KQ" : "kq";


    if (board.kingIsInCheck(board.getData()[position]->getColor()).size() > 0)
        return {};

    for (auto& castle : castlesToFind){
        if (board.getAllowedCastles().find(castle) != std::string::npos){
            if ((castle == 'K' || castle == 'k') && isEmptyZone(position, position + 3, board) && !isCompromizedZone(position, position + 3, board, color == "White" ? "Black" : "White"))
                toReturn.push_back(position + 2);
            else if ((castle == 'Q' || castle == 'q') && isEmptyZone(position, position - 4, board) && !isCompromizedZone(position, position -4, board, color == "White" ? "Black" : "White"))
                toReturn.push_back(position - 2);
        }
    }

    return toReturn;
}

std::vector<int> APiece::getPseudoLegalMoves(Board &board, int position){
    std::vector<int> freeSquareMoves;

    if (this->_name == "Pawn"){
        if (!(isOnRow(2, position) || isOnRow(7, position)) && this->moveSet.size() > 1)
            this->moveSet.pop_back();
        auto foundCaptures = canCapture(board, position);

        for (auto& lala : foundCaptures)
            std::cout << move::inverseBoardMap.at(lala) << " <----- is pseudo legal"<< std::endl;
        freeSquareMoves.insert(freeSquareMoves.begin(), foundCaptures.begin(), foundCaptures.end());
    }



    if (this->_name == "King"){

        auto foundCastles = isAllowedToCastle(this->_color, position, board);
        freeSquareMoves.insert(freeSquareMoves.begin(), foundCastles.begin(), foundCastles.end());
            // break;
    }
    int moveIndex = 0;
    for (auto& move : moveSet){
        if (move != 0){
            for(int n = 1; n <= _range ; ++n){
                int square = (position + (n * move));
                if (square < 0 || square > 63)
                    break;
                if ((move == -1 || move == 1) && (position / 8 != square / 8))
                    break;
                
                if (this->_name == "Knight" && knightMoveOverFlow(position, square))
                    break;
                if ((((move != -1 && move != 1 && move != -8 && move != 8)) && diagonalMoveOverFlow(position , square)) && (this->getName() == "Bishop" || this->getName() == "Queen" || this->getName() == "King"))
                    break;
                if (this->getName() == "Pawn" && std::abs(move) == 16 && board.getData()[square + (this->_color == "White" ? 8 : -8)] != nullptr){
                        std::cout << move::inverseBoardMap.at(square) << "<----- " << std::endl;
                        break;
                }

                if (this->_name == "King" && ((board.squareIsCompromised((this->_color == "White" ? "Black" : "White"), square).size() > 0) || (enemyKingNearby(board , square, this->_color == "White" ? "Black" : "White", {-9, -7, 7, 9, -1 , -8, +1, +8}).size() > 0))){
                        break;
                }
                if (board.getData()[square] != nullptr && (board.getData()[square]->getCapturable()) && (this->_color != board.getData()[square]->getColor()) && (std::ranges::find(captureMoveSet, moveSet[moveIndex]) != captureMoveSet.end()))
                        freeSquareMoves.push_back(square);

                if (board.getData()[square] != nullptr)
                    break;
                freeSquareMoves.push_back(square);
            }
        }
        moveIndex++;
    }

    return freeSquareMoves;
}


const std::string APiece::getName(){
    return _name;
}

bool APiece::getCanJump(){
    return _canJump;
}

const std::string APiece::getRepresentation(){
    return( _color == "White" ? _representation : tolower(_representation));
}