#pragma once

#include "APiece.hpp"
#include "Board.hpp"
#include "utils.hpp"
#include <memory>
#include <math.h>

class King : public APiece
{
private:
    std::vector<int> isAllowedToCastle(int position, GameState &gameState);
public:
    King() = delete;
    virtual ~King() = default;
    King(const std::string &color);
    
    std::unique_ptr<APiece> clone() override;
    void specialMove(move move, GameState& gameState) override;
    void endOfTurnEffects(move move, GameState &gameState) override;
    bool canAttackSquare(int from, int target, GameState &gameState) override;
    std::vector<int> getPseudoLegalMoves(GameState &gameState, int position) override;
};

