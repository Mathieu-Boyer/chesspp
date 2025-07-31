#pragma once

#include "APiece.hpp"
#include <memory>

class Knight : public APiece
{
private:

public:
    Knight() = delete;
    virtual ~Knight() = default;
    Knight(const std::string &color);
    
    std::unique_ptr<APiece> clone() override;
    bool canAttackSquare(int from, int target, GameState &gameState) override;
    std::vector<int> getPseudoLegalMoves(GameState &gameState, int position) override;

};

