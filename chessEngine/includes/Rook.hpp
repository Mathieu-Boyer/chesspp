#pragma once

#include "APiece.hpp"
#include <memory>

class Rook : public APiece
{
private:
    /* data */
public:
    Rook() = delete;
    Rook(const std::string &color);
    std::vector<int> getPseudoLegalMoves(GameState &gameState, int position) override;
    bool canAttackSquare(int from, int target, GameState &gameState) override;
    void specialEffects(move move, GameState &gameState) override ;
    std::unique_ptr<APiece> clone() override;

    ~Rook() = default;
};

