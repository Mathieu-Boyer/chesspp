#pragma once

#include <string>
#include <map>
struct move {

    int from;
    int to;
    char promotion;

    static const std::map<std::string, int> boardMap ;
    static const std::map<int, std::string> inverseBoardMap ;

    move() = delete;
    move(const std::string &);

};
