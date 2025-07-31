#include "Board.hpp"

bool validSquare(int square){
    return (square >= 0 && square < 64);
}

bool horizontalMove(int move){
    return (move == -1 || move == 1);
}

bool horizontalOverflow(int position, int square){
    return (position / 8 != square / 8);
}

bool diagonalMove(int move){
    return (move % 9 == 0 || move % 7 == 0);
}
bool validPromotionChar(char promotion){
    return ((promotion == 'Q' || promotion == 'R' || promotion == 'B' || promotion == 'N')
        || (promotion == 'q' || promotion == 'r' || promotion == 'b' || promotion == 'n'));
}

bool promotionAssertions(Board &board, move move){

    APiece *piece = board.getPieceAt(move.from);

    bool onFirstOrLastRank = piece->isOnRow(1, move.to) || piece->isOnRow(8, move.to);
    if (!onFirstOrLastRank){
        return false;
    }

    if (piece->getColor() == "White"){
        if (move.promotion == '-')
            throw std::runtime_error("A pawn on the end of a board must provide the piece it wants to become.");
        if (move.promotion == std::tolower(move.promotion))
            throw std::runtime_error("You are trying to become a black piece for a white pawn promotion.");
    }
    if (piece->getColor() == "Black"){
        if (move.promotion == '-')
            throw std::runtime_error("A pawn on the end of a board must provide the piece it wants to become.");
        if (move.promotion == std::toupper(move.promotion))
            throw std::runtime_error("You are trying to become a black piece for a white pawn promotion.");
    }

    if (!validPromotionChar(move.promotion))
        throw std::runtime_error("Pawn can't be promoted .");
    return true;
}
