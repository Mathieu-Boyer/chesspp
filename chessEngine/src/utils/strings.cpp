#include "utils.hpp"

std::vector<std::string> split(std::string string, char delimiter){
    std::vector<std::string> splitedString;
    for (auto part : std::views::split(string, delimiter))
        splitedString.push_back(std::string(part.begin(), part.end()));
    return splitedString;
}

std::string tolower(std::string string){
    std::string toReturn;
    for (auto &character : string)
        toReturn += tolower(character);
    return toReturn;
}