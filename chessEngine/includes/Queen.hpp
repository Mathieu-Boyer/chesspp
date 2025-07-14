#pragma once

#include "APiece.hpp"
#include <memory>

class Queen : public APiece
{
private:
    /* data */
public:
    Queen();
    std::unique_ptr<APiece> clone();
    ~Queen() = default;
};

