#pragma once

#include "APiece.hpp"
#include "Board.hpp"
#include <memory>

class King : public APiece
{
private:
    /* data */
    std::vector<int> isAllowedToCastle(int position, GameState &gameState);
public:
    King() = delete;
    King(const std::string &color);
    std::vector<int> getPseudoLegalMoves(GameState &gameState, int position) override;
    bool canAttackSquare(int from, int target, GameState &gameState) override;
    void endOfTurnEffects(move move, GameState &gameState) override;
    void specialMove(move move, GameState& gameState) override;
    std::unique_ptr<APiece> clone() override;
    ~King() = default;

    bool isInCheck(Board &board);
};

