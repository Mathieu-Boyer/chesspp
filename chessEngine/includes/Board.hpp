#pragma once
#include <string>
#include <array>
#include <memory>
#include "APiece.hpp"
#include "utils.hpp"
#include "move.hpp"
#include "GameState.hpp"
#include "colors.hpp"

class GameState;
class Board
{
    private:
        std::array<std::unique_ptr<APiece>, 64> data;
        int whiteKingPosition;
        int blackKingPosition;
        int princePosition(const std::string &colorToMove);

    public:
        void applyMove(const move& move, GameState &GameState);
        const std::array<std::unique_ptr<APiece>, 64> &getData();

        Board()  = default;
        Board(const Board&);
        Board(Board&&)  = default;
        ~Board() = default;

        bool tryMovingKingToPrince(GameState &GameState);
        void placePieces(const std::string &fenBoard);
        void setWhiteKingPosition(int position);
        void setBlackKingPosition(int position);
        void applyCastle(const move &move, GameState &GameState);
        int getWhiteKingPosition();
        int getBlackKingPosition();
        APiece *getPieceAt(int position);
        const APiece *getPieceAt(int position) const;
        void setPieceAt(int position, std::unique_ptr<APiece> piece);
        void clearPieceAt(int position);
        std::unique_ptr<APiece> &accessPieceSlot(int pos);
        std::unique_ptr<Board> clone() const;
};