#pragma once

#include "APiece.hpp"
#include <memory>

class Pawn : public APiece
{
private:
    /* data */
public:
    Pawn() = delete;
    Pawn(const std::string &color);
    std::unique_ptr<APiece> clone() override;
    std::vector<int> getPseudoLegalMoves(GameState &gameState, int position) override;
    bool canAttackSquare(int from, int target, GameState& gamestate) override;
    // void startOfTurnEffects(GameState &) override;
    void endOfTurnEffects(move, GameState &gameState) override;
    void specialEffects(move move, GameState &gameState) override;
    ~Pawn() = default;
};

