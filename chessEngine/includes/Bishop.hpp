#pragma once

#include "APiece.hpp"
#include <memory>

class Bishop : public APiece
{
private:

public:
    Bishop() = delete;
    virtual ~Bishop() = default;
    Bishop(const std::string &color);

    std::unique_ptr<APiece> clone() override;
    bool canAttackSquare(int from, int target, GameState &gameState) override;
    std::vector<int> getPseudoLegalMoves(GameState &gameState, int position) override;
};