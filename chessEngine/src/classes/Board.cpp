#include "Board.hpp"
#include "King.hpp"
#include "colors.hpp"

Board::Board(const Board& board){

    unsigned counter = 0;
    for (auto &element : board.data){
        whiteKingPosition = board.whiteKingPosition;
        blackKingPosition = board.blackKingPosition;
        if (element != nullptr)
            this->data[counter] = element->clone();

        counter++;
    }
}

const std::array<std::unique_ptr<APiece>, 64> &Board::getData(){
    return data;
}



void Board::placePieces(const std::string &fen) {

    unsigned counter = 0;
    for (auto &character : fen){
        if (character == '/')
            continue;
        if (std::isdigit(character)){
            counter += character - '0';
            // std::cout << counter << std::endl;
            continue;
        }

        data[counter] = pieceFactory(character);
        if (data[counter]->getRepresentation() == "K"){
            whiteKingPosition = counter;
        } else if (data[counter]->getRepresentation() == "k"){
            blackKingPosition = counter;
        }

        counter++;
    }
}

void Board::applyMove(const move &move){

    if (data[move.from] == nullptr)
        throw std::runtime_error("The 'From' square is empty");
    auto legalMoves = data[move.from]->getLegalMoves(*this, move.from);
    if (std::ranges::find(legalMoves, move.to) == legalMoves.end())
        throw std::runtime_error("This move is illegal ! you are going to jail.");

    data[move.to] = std::move(data[move.from]);
    // data[move.from] = nullptr;
}

void Board::printASCII(){
    int counter = 0;
    for (auto &square : data){

        if ((counter == whiteKingPosition || counter == blackKingPosition) && dynamic_cast<King*>(data[counter].get())){
            if (dynamic_cast<King*>(data[counter].get())->isInCheck(*this))
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


void Board::printASCII(const std::vector<int> &moves){
{
        unsigned counter = 0;
        for (auto &square : data){
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

void Board::setWhiteKingPosition(int position){
    whiteKingPosition = position;
}
void Board::setBlackKingPosition(int position){
    blackKingPosition = position;
}


int Board::getWhiteKingPosition(){
    return whiteKingPosition;
}
int Board::getBlackKingPosition(){
    return blackKingPosition;
}