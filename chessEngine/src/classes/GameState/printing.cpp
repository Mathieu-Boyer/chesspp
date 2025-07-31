#include "GameState.hpp"

void GameState::printASCII(){
    int counter = 0;
    Board &board = getRefToBoard();
    for (auto &square : board.getData()){

        if ((counter == board.getWhiteKingPosition() || counter == board.getBlackKingPosition()) && (board.getPieceAt(counter)->getColor() == colorToMove)){
            if (staleMate())
                std::cout << PINK ;
            else if (checkMateSituation(colorToMove))
                std::cout << RED;
            else if (kingIsInCheck(colorToMove).size() > 0)
                std::cout << ORANGE;
        }

        if (square == nullptr){
            std::cout << " . ";
        }else{
            std::cout << " " << square->getRepresentation() << " " << RESET_COLOR;
        }
        counter++;
        if (counter % 8 == 0)
            std::cout << std::endl;
    }
    std::cout << std::endl;
}


void GameState::printASCII(const std::vector<int> &moves){
{
        unsigned counter = 0;
        Board &board = getRefToBoard();

        for (auto &square : board.getData()){
            if (std::ranges::find(moves, counter) != moves.end()){
                std::cout << " x ";
            }
            else if (square == nullptr){
                std::cout << " . ";
            }else{
                std::cout << " " << square->getRepresentation() << " ";
            }

            counter++;
            if (counter % 8 == 0)
                std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}
