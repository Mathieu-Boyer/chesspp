#pragma once

#include "APiece.hpp"
#include <memory>

class Queen : public APiece
{
private:
    /* data */
public:
    Queen() = delete;
    Queen(const std::string &color);
    std::unique_ptr<APiece> clone();
    ~Queen() = default;
};

