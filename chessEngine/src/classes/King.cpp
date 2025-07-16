#include "King.hpp"
#include "APiece.hpp"
#include "math.h"

King::King(const std::string &color) :  APiece("King","K", color, 0 , 1, false , false){
    this->moveSet        = { -9, -8, -7, 1, 7, 8 , 9 -1 };
    this->captureMoveSet = moveSet;
    this->specialMoveSet = {}; // this is where i will put the castle later.
}

std::unique_ptr<APiece> King::clone(){
    return std::make_unique<King>(*this);
}

bool pawnCheck(const std::string &representation, Board &board){
    int position = representation == "K" ? board.getWhiteKingPosition() : board.getBlackKingPosition();
    std::array<int, 2> toCkeck = representation == "k" ? (std::array<int, 2>){7, 9} : (std::array<int, 2>){-9, -7};
    auto &pieces = board.getData();

    for (auto& square : toCkeck)
        if ((pieces[position + square] != nullptr) && ((representation == "K" && pieces[position + square]->getRepresentation() == "p") || (representation == "k" && pieces[position + square]->getRepresentation() == "P")))
            return true;
    return false;
}

bool piecesCanCheck(int position, int maxRange, const std::vector<std::string> &slidePieces, std::vector<int> toCheck , Board &board){

    auto &pieces = board.getData();

    for (auto& squareToCheck : toCheck)

        for (int n = 1 ; n <= maxRange ; n++){
            int square = position + squareToCheck * n;
            if ((square) < 0 || (square) > 63 || ((squareToCheck == -1 || squareToCheck == 1) && (position / 8 != square / 8)))
                break;
            if (pieces[square] == nullptr)
                continue;
            if (pieces[square]->getName() == "Knight" && knightMoveOverFlow(position , square))
                break;
            auto slidingPiecesIterator = std::ranges::find((slidePieces), pieces[square]->getRepresentation());
            if (slidingPiecesIterator == slidePieces.end())
                break;
            return true;
        }
    return false;
}

bool King::isInCheck(Board &board){
    const std::string &representation = getRepresentation();
    int position = representation == "K" ? board.getWhiteKingPosition() : board.getBlackKingPosition();
    std::vector<std::string> horizontalPieces = representation == "K" ? (std::vector<std::string>){"q", "r"} : (std::vector<std::string>){"Q", "R"};
    std::vector<int> horizontalPiecesMoves = {-1 , -8, +1, +8};

    std::vector<std::string> diagonalPieces = representation == "K" ? (std::vector<std::string>){"q", "b"} : (std::vector<std::string>){"Q", "B"};
    std::vector<int> diagonalPiecesMoves = {-9, -7, 7, 9};

    std::vector<std::string> knight = representation == "K" ? (std::vector<std::string>){"n"} : (std::vector<std::string>){"N"};
    std::vector<int> knightMoves = {-17, -15, 7, 9, -6, 10, 17, 15, -10, 6};

    if (pawnCheck(representation, board))
        return true;
    if (piecesCanCheck(position, 8, horizontalPieces, horizontalPiecesMoves, board) || piecesCanCheck(position, 8, diagonalPieces, diagonalPiecesMoves, board))
        return true;
    if (piecesCanCheck(position, 1, knight, knightMoves, board))
        return true;
    
    return false;
}
