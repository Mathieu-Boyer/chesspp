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