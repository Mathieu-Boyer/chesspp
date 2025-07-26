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

        std::vector<int> canCapture(GameState &gameState, int position);
        virtual std::vector<int> getPseudoLegalMoves(GameState &gameState, int position) = 0;
        virtual bool canAttackSquare(int from, int target, GameState &GameState) = 0;
        virtual void specialEffects(move move, GameState &gameState);
        virtual void startOfTurnEffects(move move, GameState &GameState);
        virtual void endOfTurnEffects(move move, GameState &GameState);
        virtual void specialMove(move move, GameState &gameState);
        virtual void onCaptureEffects(move move, GameState &gameState, APiece *capturedPiece);

        virtual void onCapturedEffects(move move, GameState &gameState);


        void describe();
        const std::string getRepresentation();
        virtual std::unique_ptr<APiece> clone() = 0 ;
        const std::string getName();
        bool getCanJump();
        const std::string getColor();
        bool getCapturable();
        APiece()           = delete;
        APiece(const std::string &name, const std::string &representation, const std::string &color, int value, int range, bool canJump, bool capturable);
        bool isOnRow(int row, int position);
        virtual ~APiece()  = default;
        const std::vector<int> &getSpecialMoveSet();
        int getRange();
};