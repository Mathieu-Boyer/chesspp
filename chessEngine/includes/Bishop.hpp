#pragma once

#include "APiece.hpp"
#include <memory>

class Bishop : public APiece
{
private:
    /* data */
public:
    Bishop();
    std::unique_ptr<APiece> clone();
    ~Bishop() = default;
};

