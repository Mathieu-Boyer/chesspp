#pragma once

#include "APiece.hpp"
#include <memory>

class Knight : public APiece
{
private:
    /* data */
public:
    Knight() = delete;
    Knight(const std::string &color);
    std::unique_ptr<APiece> clone();
    ~Knight() = default;
};

