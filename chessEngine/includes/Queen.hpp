#pragma once

#include "APiece.hpp"
#include <memory>

class Queen : public APiece
{
private:
    /* data */
public:
    Queen() = delete;
    Queen(const std::string &color);
    std::vector<int> getPseudoLegalMoves(GameState &gameState, int position) override;
    bool canAttackSquare(int from, int target, GameState &gameState) override;
    std::unique_ptr<APiece> clone() override;
    ~Queen() = default;
};

