#pragma once

#include "APiece.hpp"
#include <memory>

class Prince : public APiece
{
private:
    /* data */
public:
    Prince() = delete;
    Prince(const std::string &color);
    std::vector<int> getPseudoLegalMoves(GameState &gameState, int position) override;
    bool canAttackSquare(int from, int target, GameState &gameState) override;
    std::unique_ptr<APiece> clone() override;
    void onCaptureEffects(move, GameState &gameState) override;
    ~Prince() = default;
};

