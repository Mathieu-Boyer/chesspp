#include "Board.hpp"

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

APiece *Board::getPieceAt(int position){
    if (!validSquare(position))
        return nullptr;
    return data[position].get();
}

const APiece *Board::getPieceAt(int position) const{
    if (!validSquare(position))
        return nullptr;
    return data[position].get();
}

void Board::setPieceAt(int position, std::unique_ptr<APiece> piece){
    data[position] = std::move(piece);
}

std::unique_ptr<APiece> &Board::accessPieceSlot(int pos) {
    return data[pos];
}
void Board::clearPieceAt(int position){
    data[position].reset();
}