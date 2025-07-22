#include <iostream>
// #include <cctype>
#include "GameState.hpp"
#include "move.hpp"
#include <string>

int main (int argc , char *argv[]){
    std::cout << "[ Chess++ | engine ]" << std::endl;

    if (argc == 1)
        playInTerminal();
    else if (argc != 3){
        std::cerr << "The call to Chess++ engine is not formated correctly, if you provide arguments please follow : ./chess++ [move] [current game's fen]\n";
        return 1;
    }
    executeNeededFunctionalities(argv[1] , argv[2]);
    return 0;
}