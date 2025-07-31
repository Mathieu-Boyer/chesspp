#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <memory>

#include "Board.hpp"
#include "utils.hpp"
#include "GameState.hpp"

class Board;
class GameState;;
class APiece
{
    private:
        std::string _name;
        std::string _color;
        int _value;
        int _range;
        bool _canJump;
        bool _capturable;

    protected:
        std::vector<int> moveSet;
        std::vector<int> captureMoveSet;
        std::vector<int> specialMoveSet;
        std::string _representation;
    public:

        APiece()           = delete;
        APiece(const std::string &name, const std::string &representation, const std::string &color, int value, int range, bool canJump, bool capturable);
        virtual ~APiece()  = default;

        virtual std::unique_ptr<APiece> clone() = 0 ;
        virtual void specialMove(move move, GameState &gameState);
        virtual void specialEffects(move move, GameState &gameState);
        virtual void endOfTurnEffects(move move, GameState &GameState);
        virtual void onCapturedEffects(move move, GameState &gameState);
        virtual void startOfTurnEffects(move move, GameState &GameState);
        virtual bool canAttackSquare(int from, int target, GameState &GameState) = 0;
        virtual std::vector<int> getPseudoLegalMoves(GameState &gameState, int position) = 0;
        virtual void onCaptureEffects(move move, GameState &gameState, APiece *capturedPiece);

        std::vector<int> canCapture(GameState &gameState, int position); // is only used for pawns this will be removed because it is an artifact of the old program's architecture.

        void describe();
        bool isOnRow(int row, int position);

        int getRange();
        bool getCanJump();
        bool getCapturable();
        const std::string getName();
        const std::string getColor();
        const std::string getRepresentation();
        const std::vector<int> &getSpecialMoveSet();
};