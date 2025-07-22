#include <iostream>
// #include <cctype>
#include "GameState.hpp"
#include "move.hpp"
#include <string>

int main (int argc , char *argv[]){
    if (argc == 1){
        playInTerminal();
        return 0;
    }
    else if (argc != 3){
        std::cerr << "The call to Chess++ engine is not formated correctly, if you provide arguments please follow : ./chess++ [move] [current game's fen]\n";
        return 1;
    }
    executeNeededFunctionalities(argv[1] , argv[2]);
    return 0;
}