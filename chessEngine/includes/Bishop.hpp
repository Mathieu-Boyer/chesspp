#pragma once

#include "APiece.hpp"
#include <memory>

class Bishop : public APiece
{
private:
    /* data */
public:
    Bishop() = delete;
    Bishop(const std::string &color);
    std::unique_ptr<APiece> clone();
    ~Bishop() = default;
};

