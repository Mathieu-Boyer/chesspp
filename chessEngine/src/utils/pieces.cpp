#include "utils.hpp"
#include <memory>
#include "Rook.hpp"
#include "Knight.hpp"
#include "King.hpp"
#include "Queen.hpp"
#include "Bishop.hpp"
#include "Pawn.hpp"
#include "Prince.hpp"

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

        case 's':
        case 'S':{
            Prince prince(std::islower(character) ? "Black" : "White");
            return prince.clone();
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


bool enemyKingNearby(Board &board, int positionOfmyKing, const std::string& enemyColor, std::vector<int> toCheck){
    for (auto& squareToCheck : toCheck){
            int square = positionOfmyKing + squareToCheck;
            if ((square) < 0 || (square) > 63 || ((squareToCheck == -1 || squareToCheck == 1) && (positionOfmyKing / 8 != square / 8)))
                continue;
            if (board.getData()[square] == nullptr)
                continue;
            if ((board.getData()[square]->getName() == "King") && board.getData()[square]->getColor() == enemyColor)
                return true;
    }
    return false;
}

bool isEmptyZone(int from, int to, Board &board){
    if (from == to)
        std::runtime_error("1 square is not considered a zone.");

    int step   = from < to ? +1 : -1;
    for (int i = from + step; i != to; i += step){
        APiece *piece = board.getPieceAt(i);
        if (piece != nullptr)
            return false;
    }
    return true;
}

bool isCompromizedZone(int from, int to, GameState& gameState, const std::string& enemy){

    if (from == to)
        std::runtime_error("1 square is not considered a zone.");

    int step   = from < to ? +1 : -1;
    for (int i = from + step; i != to; i += step){

        auto result = gameState.squareIsCompromised(enemy, i);
        if (result.size() > 0)
            return true;
    }

    return false;
}

std::string enemyOf(const std::string &color){
    return (color == "White" ? "Black" : "White");
}