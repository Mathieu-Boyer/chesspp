#pragma once

#include "APiece.hpp"
#include <memory>

class Queen : public APiece
{
private:

public:
    Queen() = delete;
    virtual ~Queen() = default;
    Queen(const std::string &color);
    
    std::unique_ptr<APiece> clone() override;
    bool canAttackSquare(int from, int target, GameState &gameState) override;
    std::vector<int> getPseudoLegalMoves(GameState &gameState, int position) override;
};

