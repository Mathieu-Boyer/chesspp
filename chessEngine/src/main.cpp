#include "iostream"
#include "Rook.hpp"

int main (){

    std::cout << "Yipeee" << std::endl;

    Rook rook;
    rook.describe();
    rook.setColor("Black");
    rook.describe();

    return 0;
}