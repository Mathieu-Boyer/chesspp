#pragma once
#include <string>
#include <array>
#include <memory>
#include "APiece.hpp"
#include "utils.hpp"

class Board
{
    private:
        std::array<std::unique_ptr<APiece>, 64> data;
        int whiteKingPosition;
        int blackKingPosition;
    public:
        void applyMove();
        const std::array<std::unique_ptr<APiece>, 64> &getData();
        // i'll add maps here to translate 2D moves such as A8 -> 0
        Board()  = default;
        Board(const Board&) ;
        Board(Board&&)  = default;
        // Board()  = default;
        ~Board() = default;
        void placePieces(const std::string &fenBoard);
        void printASCII();
        void printASCII(const std::vector<int> &moves);


        void setWhiteKingPosition(int position);
        void setBlackKingPosition(int position);

        int getWhiteKingPosition();
        int getBlackKingPosition();
};