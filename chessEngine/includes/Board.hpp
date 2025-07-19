#pragma once
#include <string>
#include <array>
#include <memory>
#include "APiece.hpp"
#include "utils.hpp"
#include "move.hpp"


class GameState;
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

        Board()  = default;
        Board(const Board&);
        Board(Board&&)  = default;

        // Board()  = default;
        ~Board() = default;
        void placePieces(const std::string &fenBoard);
        void setColorToMove(const std::string &color);
        void printASCII(GameState &gameState);
        void printASCII(const std::vector<int> &moves);

        std::vector<int> getPieceLegalMove(int position,GameState &gameState);
        void setWhiteKingPosition(int position);
        void setBlackKingPosition(int position);
        void setPossibleEnPassantNow(int enPassantSquare);
        void setdissAllowedCastles(const std::string &);
        void setAllowedCastles(const std::string &);


        std::vector<int> squareIsCompromised(const std::string &enemy, int position);
        void applyCastle(const move &move);
        std::string getAllowedCastles();
        std::string getdissAllowedCastles();
        int getWhiteKingPosition();
        int getBlackKingPosition();
        int getPossibleEnPassantNextHalfMove();
        int getPossibleEnPassantNow();

        bool pieceCanInterpose(int pieceA, int pieceB, const std::string &pieceName, const std::string& interposeColor);

        std::vector<int> kingIsInCheck(const std::string &color);
        bool moreThan1PieceCanCheck(const std::string &color);
        bool checkIngPieceCanBeCaptured(const std::string &color, int checkerPos);
        bool checkMateSituation(const std::string &color);
        bool staleMate(const std::string &color, GameState &gameState);

        std::unique_ptr<Board> clone() const;
        // std::vector<int> positionsOfAllCheckers{};
};