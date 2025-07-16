#include "APiece.hpp"

APiece::APiece(const std::string &name, const std::string &representation, const std::string &color, int value, int range, bool canJump, bool capturable) : _name(name), _color(color), _value(value), _range(range), _canJump(canJump) , _capturable(capturable), _representation(representation){}

void APiece::describe(){
    std::cout << "[ "<< _color << " " << _name << " ]" << " details : { " << "value : " << _value << ", range : " << _range << ", canJump : " << _canJump << ", capturable : " << _capturable << " }" << std::endl;
}

// void APiece::setColor(const std::string &color){
//     this->color = color;
// }

std::vector<int> APiece::getLegalMoves(Board &board, int position){
    std::vector<int> freeSquareMoves;

    // int moveIndex = 0;
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
                if (board.getData()[square] != nullptr)
                    break;
                freeSquareMoves.push_back(square);
            }
        }
    }

    return freeSquareMoves;
}


const std::string APiece::getName(){
    return _name;
}

const std::string APiece::getRepresentation(){
    return( _color == "White" ? _representation : tolower(_representation));
}