#pragma once

#include "APiece.hpp"
#include <memory>

class Rook : public APiece
{
private:
    /* data */
public:
    Rook() = delete;
    Rook(const std::string &color);
    std::unique_ptr<APiece> clone();
    ~Rook() = default;
};

