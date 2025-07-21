#pragma once

#include "APiece.hpp"
#include "Board.hpp"
#include <memory>

class King : public APiece
{
private:
    /* data */
    std::vector<int> isAllowedToCastle(int position, Board& board);
public:
    King() = delete;
    King(const std::string &color);
    std::vector<int> getPseudoLegalMoves(GameState &gameState, int position) override;
    bool canAttackSquare(int from, int target, GameState &gameState) override;
    std::unique_ptr<APiece> clone() override;
    ~King() = default;

    bool isInCheck(Board &board);
};

