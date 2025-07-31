#pragma once

#include "APiece.hpp"
#include "colors.hpp"
#include <memory>

class Chameleon : public APiece
{
private:
    bool copyCanAttackSquare(char pieceChar ,int from, GameState &gameState, int position);
    void copyMovesFromPiece(char pieceChar , GameState &gameState, int position);

public:
    Chameleon() = delete;
    virtual ~Chameleon() = default;
    Chameleon(const std::string &color);

    std::unique_ptr<APiece> clone() override;
    void startOfTurnEffects(move move, GameState &GameState) override;
    void onCaptureEffects(move, GameState &, APiece *capturedPiece) override;
    bool canAttackSquare(int from, int target, GameState &gameState) override;
    std::vector<int> getPseudoLegalMoves(GameState &gameState, int position) override;
};

