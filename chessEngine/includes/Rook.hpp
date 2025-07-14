#pragma once

#include "APiece.hpp"
#include <memory>

class Rook : public APiece
{
private:
    /* data */
public:
    Rook();
    std::unique_ptr<APiece> clone();
    ~Rook() = default;
};

