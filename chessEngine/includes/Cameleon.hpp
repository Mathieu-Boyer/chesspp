#pragma once

#include "APiece.hpp"
#include <memory>

class Cameleon : public APiece
{
private:
    /* data */
public:
    Cameleon() = delete;
    Cameleon(const std::string &color);


    void onCaptureEffects(move, GameState &, APiece *capturedPiece) override;
    void copyMovesFromPiece(char pieceChar , GameState &gameState, int position);
    std::vector<int> getPseudoLegalMoves(GameState &gameState, int position) override;
    bool canAttackSquare(int from, int target, GameState &gameState) override;
    std::unique_ptr<APiece> clone() override;
    void startOfTurnEffects(move move, GameState &GameState) override;
    ~Cameleon() = default;
};

