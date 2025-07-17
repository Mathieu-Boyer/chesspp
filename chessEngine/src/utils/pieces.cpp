#include "utils.hpp"
#include <memory>
#include "Rook.hpp"
#include "Knight.hpp"
#include "King.hpp"
#include "Queen.hpp"
#include "Bishop.hpp"
#include "Pawn.hpp"

std::unique_ptr<APiece> pieceFactory(char character){
    switch (character)
    {
        case 'r':
        case 'R':{
            Rook rook(std::islower(character) ? "Black" : "White");
            return rook.clone();
        }
        case 'n':
        case 'N':{
            Knight knight(std::islower(character) ? "Black" : "White");
            return knight.clone() ;
        }

        case 'k':
        case 'K':{
            King king(std::islower(character) ? "Black" : "White");
            return king.clone();
        }

        case 'q':
        case 'Q':{
            Queen queen(std::islower(character) ? "Black" : "White");
            return queen.clone();
        }

        case 'b':
        case 'B':{
            Bishop bishop(std::islower(character) ? "Black" : "White");
            return bishop.clone();
        }

        case 'p':
        case 'P':{
            Pawn pawn(std::islower(character) ? "Black" : "White");
            return pawn.clone();
        }

        default :
            return nullptr;
    }
}

bool diagonalMoveOverFlow(int position, int to){
    int file = position % 8;

    if (to < 0 || to >= 64) return false;
    int fileDiff = std::abs((to % 8) - file);
    int rankDiff = std::abs((to / 8) - (position / 8));

    if ((fileDiff != rankDiff)) {
        return true;
    }
    return false;
}

bool knightMoveOverFlow(int position, int to){
    int file = position % 8;

    if (to < 0 || to >= 64) return false;
    int fileDiff = std::abs((to % 8) - file);
    int rankDiff = std::abs((to / 8) - (position / 8));

    if ((fileDiff == 1 && rankDiff == 2) || (fileDiff == 2 && rankDiff == 1)) {
        return false;
    }
    return true;
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
            if ((pieces[square]->getName() == "Bishop" || pieces[square]->getName() == "Queen" || pieces[square]->getName() == "King") && (((squareToCheck != -1 && squareToCheck != 1) && (squareToCheck != -8 && squareToCheck != 8) ) && diagonalMoveOverFlow(position , square)))
                break;
            auto slidingPiecesIterator = std::ranges::find((slidePieces), pieces[square]->getRepresentation());
            if (slidingPiecesIterator == slidePieces.end())
                break;
            return true;
        }
    return false;
}