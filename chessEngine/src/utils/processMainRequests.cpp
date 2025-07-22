#include <iostream>
#include "GameState.hpp"
#include "move.hpp"
#include <string>

void playInTerminal(){
    std::string currentFen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

    while (true){
        try {
            GameState gameState(currentFen);
            gameState.printASCII();
            int status = gameState.checkGameStatus();
            std::cout << currentFen << std::endl;
            if (status != gameStatus::ongoing)
                return ;

            std::string rawMove;
            std::cin >> rawMove;

            move moveToTry(rawMove);
            if (moveToTry.from != -1 && moveToTry.to == -1)
                gameState.printASCII(gameState.getPieceLegalMove(moveToTry.from));
            else if (moveToTry.from >= 0 && moveToTry.to >= 0){
                gameState.applyMove(moveToTry);
                currentFen = gameState.encode();
            }
            else
                throw std::runtime_error("Move not correctly formated");
        }catch(const std::exception& e){
            std::cerr << e.what() << std::endl;
        }
    }
}


void applyMoveAndGenerateNewFen(const std::string &rawMove, const std::string &currentFen){
        try {
            GameState gameState(currentFen);
            int status = gameState.checkGameStatus();
            if (status != gameStatus::ongoing){
                std::cout << "Game status : " << status << std::endl;
                std::cout << "New FEN : " << currentFen << std::endl;
                return ;
            }

            move moveToTry(rawMove);
            gameState.applyMove(moveToTry);
            std::string newFen = gameState.encode();

            std::cout << "Game status : " << status << std::endl;
            std::cout << "New FEN : " << newFen << std::endl;
        }catch(const std::exception& e){
            std::cerr << e.what() << std::endl;
        }
}

void fetchLegalMoves(const std::string &rawMove, const std::string &currentFen){
        std::vector<int> fetchedMove;
        try {
            GameState gameState(currentFen);
            int status = gameState.checkGameStatus();
            if (status != gameStatus::ongoing)
                return ;

            move moveToTry(rawMove);
            fetchedMove = gameState.getPieceLegalMove(moveToTry.from);
        }catch(const std::exception& e){
            std::cerr << e.what() << std::endl;
            return;
        }
        std::cout << "[ ";
        for (auto &move : fetchedMove)
                std::cout << move::inverseBoardMap.at(move) << " ";
        std::cout << "]" << std::endl;
}

void executeNeededFunctionalities(const std::string &rawMove, const std::string &currentFen){
    if (rawMove.empty() || currentFen.empty()){
        std::cerr << "Arguments can't be empty" << std::endl;
        return;
    }

    if (rawMove.size() == 2)
        fetchLegalMoves(rawMove, currentFen);
    else if (rawMove.size() == 5 || rawMove.size() == 7)
        applyMoveAndGenerateNewFen(rawMove, currentFen);
    else
        std::cerr << "Format Error please enter a valid move" << std::endl;
}
