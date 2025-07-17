#pragma once
#include <string>
#include <array>
#include <memory>
#include "APiece.hpp"
#include "utils.hpp"
#include "move.hpp"


class Board
{
    private:
        std::array<std::unique_ptr<APiece>, 64> data;
        int whiteKingPosition;
        int blackKingPosition;
        std::string colorToMove;
        int possibleEnPassantNow;
        int possibleEnPassantNextHalfMove;
        std::string dissAllowedCastles;
        std::string allowedCastles;
    public:
        void applyMove(const move& move);
        const std::array<std::unique_ptr<APiece>, 64> &getData();
        // i'll add maps here to translate 2D moves such as A8 -> 0
        Board()  = default;
        Board(const Board&) ;
        Board(Board&&)  = default;

        // Board()  = default;
        ~Board() = default;
        void placePieces(const std::string &fenBoard);
        void setColorToMove(const std::string &color);
        void printASCII();
        void printASCII(const std::vector<int> &moves);

        std::vector<int> getPieceLegalMove(int position);
        void setWhiteKingPosition(int position);
        void setBlackKingPosition(int position);
        void setPossibleEnPassantNow(int enPassantSquare);
        void setdissAllowedCastles(const std::string &);
        void setAllowedCastles(const std::string &);


        bool squareIsCompromised(const std::string &enemy, int position);
        void applyCastle(const move &move);
        std::string getAllowedCastles();
        std::string getdissAllowedCastles();
        int getWhiteKingPosition();
        int getBlackKingPosition();
        int getPossibleEnPassantNextHalfMove();
        int getPossibleEnPassantNow();
        
};