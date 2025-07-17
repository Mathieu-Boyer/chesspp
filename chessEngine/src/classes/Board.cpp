#include "Board.hpp"
#include "King.hpp"
#include "colors.hpp"

Board::Board(const Board& board){

    unsigned counter = 0;
    for (auto &element : board.data){
        whiteKingPosition = board.whiteKingPosition;
        blackKingPosition = board.blackKingPosition;
        possibleEnPassantNextHalfMove = board.possibleEnPassantNextHalfMove;
        possibleEnPassantNow = board.possibleEnPassantNow;
        dissAllowedCastles = board.dissAllowedCastles;
        allowedCastles = board.allowedCastles;
        if (element != nullptr)
            this->data[counter] = element->clone();

        counter++;
    }
}

const std::array<std::unique_ptr<APiece>, 64> &Board::getData(){
    return data;
}


void Board::setColorToMove(const std::string &color){
    colorToMove = color;
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

std::vector<int> Board::getPieceLegalMove(int position){

    if (position > 63 || position < 0)
        throw std::runtime_error("This square does not exist.");
    if (data[position] == nullptr)
        throw std::runtime_error("Selected square is empty.");

    // if (data[position]->getColor() != colorToMove)
    //     throw std::runtime_error("This is not the turn of the piece you are trying to get the moves from.");
    return data[position]->getLegalMoves(*this, position);
}

void Board::setdissAllowedCastles(const std::string &dissAllowedCastles){
    this->dissAllowedCastles = dissAllowedCastles;
}

std::string Board::getdissAllowedCastles(){
    return dissAllowedCastles;
}

void Board::setAllowedCastles(const std::string &allowedCastles){
    this->allowedCastles = allowedCastles;
}

std::string Board::getAllowedCastles(){
    return allowedCastles;
}
// TODO move to utils later
bool squaresAreOnSameRow(int square1, int square2){
    return (square1 / 8) == (square2 / 8);
}


int Board::getPossibleEnPassantNextHalfMove(){
    return possibleEnPassantNextHalfMove;
}

int Board::getPossibleEnPassantNow(){
    return possibleEnPassantNow;
}

void Board::applyCastle(const move &move){
    if (allowedCastles.find('K') != std::string::npos && move.to == move::boardMap.at("g1"))
        data[move::boardMap.at("f1")] = std::move(data[move::boardMap.at("h1")]);
    else if (allowedCastles.find('k') != std::string::npos && move.to == move::boardMap.at("g8"))
        data[move::boardMap.at("f8")] = std::move(data[move::boardMap.at("h8")]);
    else if (allowedCastles.find('Q') != std::string::npos && move.to == move::boardMap.at("c1"))
        data[move::boardMap.at("d1")] = std::move(data[move::boardMap.at("a1")]);
    else if (allowedCastles.find('q') != std::string::npos && move.to == move::boardMap.at("c8"))
        data[move::boardMap.at("d8")] = std::move(data[move::boardMap.at("a8")]);

    if (data[move.from]->getColor() == "White")
        dissAllowedCastles = "KQ";
    else
        dissAllowedCastles = "kq";
}

void removeCharFrom(char toRemove, std::string &string){
    std::cout << string << " " << toRemove << std::endl;
    string.erase(std::remove(string.begin(), string.end(), toRemove), string.end());
    std::cout << string << " " << toRemove << std::endl;

}

void Board::applyMove(const move &move){
    if (data[move.from] == nullptr)
        throw std::runtime_error("The 'From' square is empty");
    // if (data[move.from]->getColor() != colorToMove)
    //     throw std::runtime_error("This is not the turn of the piece you are trying to move.");

    auto legalMoves = data[move.from]->getLegalMoves(*this, move.from);

    if (data[move.from]->getName() == "Pawn"){
        if (abs(move.from - move.to) == 16){
            if ((data[move.to - 1] != nullptr && squaresAreOnSameRow(move.to,move.to - 1) && data[move.to - 1]->getName() == "Pawn")){
                if (data[move.to - 1]->getColor() != data[move.from]->getColor())
                    possibleEnPassantNextHalfMove = data[move.from]->getColor() == "White" ?  move.to + 8 : move.to - 8;
            }
            if ((data[move.to + 1] != nullptr && squaresAreOnSameRow(move.to,move.to + 1) && data[move.to + 1]->getName() == "Pawn")){
                if (data[move.to + 1]->getColor() != data[move.from]->getColor())
                    possibleEnPassantNextHalfMove = data[move.from]->getColor() == "White" ?  move.to + 8 : move.to - 8;
            }
        }
    }

    if (std::ranges::find(legalMoves, move.to) == legalMoves.end())
        throw std::runtime_error("This move is illegal ! you are going to jail.");

    if (move.to == possibleEnPassantNow && data[move.from]->getName() == "Pawn"){
        data[move.from]->getColor() == "White" ? data[move.to + 8].reset() : data[move.to - 8].reset();
        possibleEnPassantNextHalfMove = 0;
        possibleEnPassantNow = 0;
    }

    if (data[move.from]->getName() == "King")
        applyCastle(move);
    if (data[move.from]->getName() == "Rook"){
        if (allowedCastles != "-"){
            std::cout << (move.from > whiteKingPosition) << allowedCastles << std::endl;
            if (data[move.from]->getColor() == "White"){
                if (move.from > whiteKingPosition)
                    // removeCharFrom('K', allowedCastles);
                    dissAllowedCastles+="K";
                else
                    dissAllowedCastles+="Q";

            }else{
                if (move.from  > blackKingPosition)
                   dissAllowedCastles+="k";
                else
                    dissAllowedCastles+="q";
            }
        }
            std::cout << allowedCastles << std::endl;

    }


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

void Board::setPossibleEnPassantNow(int enPassantSquare){
    possibleEnPassantNow = enPassantSquare;
}


int Board::getWhiteKingPosition(){
    return whiteKingPosition;
}
int Board::getBlackKingPosition(){
    return blackKingPosition;
}