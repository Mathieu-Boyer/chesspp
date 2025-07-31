#pragma once

#include "APiece.hpp"
#include <memory>

class Pawn : public APiece
{
private:

public:
    Pawn() = delete;
    virtual ~Pawn() = default;
    Pawn(const std::string &color);
    
    std::unique_ptr<APiece> clone() override;
    void endOfTurnEffects(move, GameState &gameState) override;
    void specialEffects(move move, GameState &gameState) override;
    bool canAttackSquare(int from, int target, GameState& gamestate) override;
    std::vector<int> getPseudoLegalMoves(GameState &gameState, int position) override;
};

