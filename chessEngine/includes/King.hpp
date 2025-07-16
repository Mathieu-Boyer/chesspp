#pragma once

#include "APiece.hpp"
#include "Board.hpp"
#include <memory>

class King : public APiece
{
private:
    /* data */
public:
    King() = delete;
    King(const std::string &color);
    std::unique_ptr<APiece> clone();
    ~King() = default;

    bool isInCheck(Board &board);
};

