#pragma once

#include "APiece.hpp"
#include <memory>

class Rook : public APiece
{
private:
    /* data */
public:
    Rook() = delete;
    virtual ~Rook() = default;
    Rook(const std::string &color);
    
    std::unique_ptr<APiece> clone() override;
    void specialEffects(move move, GameState &gameState) override ;
    bool canAttackSquare(int from, int target, GameState &gameState) override;
    std::vector<int> getPseudoLegalMoves(GameState &gameState, int position) override;
};

