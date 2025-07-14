#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <memory>


class APiece
{
    protected:
        std::string name;
        std::string color;
        int value;
        int range;
        std::vector<int> moveSet;
        std::vector<int> captureMoveSet;
        std::vector<int> specialMoveSet;
        bool capturable;
        bool canJump;

        virtual std::unique_ptr<APiece> clone() = 0 ;

        // when board exists add the unique pointer board to pieces. + the following :
        // int currentPosition;
    public:

        // when board exists , add the (applyMove + getLegalMoves + isMoveLegal) functions, 
        void describe();
        void setColor(const std::string&);

        APiece()           = default;
        virtual ~APiece()  = default;

};