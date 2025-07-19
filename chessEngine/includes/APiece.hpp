#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <memory>

#include "Board.hpp"
#include "utils.hpp"


class Board;
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
        // when board exists add the unique pointer board to pieces. + the following :
        // int currentPosition;
    public:

        std::vector<int> canCapture(Board &board, int position);
        std::vector<int> getPseudoLegalMoves(Board &board, int position);
        // when board exists , add the (applyMove + getPseudoLegalMoves + isMoveLegal) functions,
        void describe();
        void setColor(const std::string&);
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

};