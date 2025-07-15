#pragma once

#include "APiece.hpp"
#include <memory>

class Pawn : public APiece
{
private:
    /* data */
public:
    Pawn() = delete;
    Pawn(const std::string &color);
    std::unique_ptr<APiece> clone();
    ~Pawn() = default;
};

