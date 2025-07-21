#pragma once

#include "APiece.hpp"
#include <memory>

class Knight : public APiece
{
private:
    /* data */
public:
    Knight() = delete;
    Knight(const std::string &color);
    std::unique_ptr<APiece> clone() override;
    std::vector<int> getPseudoLegalMoves(GameState &gameState, int position) override;
    bool canAttackSquare(int from, int target, GameState &gameState) override;

    ~Knight() = default;
};

