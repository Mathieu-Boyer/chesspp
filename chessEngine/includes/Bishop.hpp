#pragma once

#include "APiece.hpp"
#include <memory>

class Bishop : public APiece
{
private:
    /* data */
public:
    Bishop() = delete;
    Bishop(const std::string &color);
    bool canAttackSquare(int from, int target, GameState &gameState) override;
    std::unique_ptr<APiece> clone() override;
    std::vector<int> getPseudoLegalMoves(GameState &gameState, int position) override;
    ~Bishop() = default;
};