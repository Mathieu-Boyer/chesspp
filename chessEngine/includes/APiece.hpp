#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <memory>


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


        virtual std::unique_ptr<APiece> clone() = 0 ;

        // when board exists add the unique pointer board to pieces. + the following :
        // int currentPosition;
    public:

        // when board exists , add the (applyMove + getLegalMoves + isMoveLegal) functions, 
        void describe();
        void setColor(const std::string&);

        APiece()           = delete;
        APiece(const std::string &name, const std::string &color, int value, int range, bool canJump, bool capturable);
        virtual ~APiece()  = default;

};