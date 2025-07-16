#pragma once

#include <string>
#include <map>
struct move {

    int from;
    int to;

    static const std::map<std::string, int> boardMap ;

    move() = delete;
    move(const std::string &);

};
