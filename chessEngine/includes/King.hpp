#pragma once

#include "APiece.hpp"
#include <memory>

class King : public APiece
{
private:
    /* data */
public:
    King();
    std::unique_ptr<APiece> clone();
    ~King() = default;
};

