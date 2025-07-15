#pragma once
#include <string>
#include <array>
#include <memory>
#include "APiece.hpp"

class Board
{
    private:
        std::array<std::unique_ptr<APiece, 64> data;
    public:
        void applyMove();
        // i'll add maps here to translate 2D moves such as A8 -> 0
        Board()  = delete;
        ~Board() = default;
        Board(const std::string &fenBoard)
};