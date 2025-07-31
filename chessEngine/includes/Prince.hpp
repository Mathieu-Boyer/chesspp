#pragma once

#include "APiece.hpp"
#include <memory>

class Prince : public APiece
{
private:
    /* data */
public:
    Prince() = delete;
    virtual ~Prince() = default;
    Prince(const std::string &color);
   
    std::unique_ptr<APiece> clone() override;
    void onCapturedEffects(move, GameState &gameState) override;
    bool canAttackSquare(int from, int target, GameState &gameState) override;
    std::vector<int> getPseudoLegalMoves(GameState &gameState, int position) override;
};

