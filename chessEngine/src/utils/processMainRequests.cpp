#include <iostream>
#include "GameState.hpp"
#include "move.hpp"
#include <string>

void playInTerminal(){

    std::cout << "[ Chess++ | engine ]" << std::endl;
    // std::string currentFen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    // std::string currentFen = "rnk2Qnr/pppqp1pp/4B3/4P3/3p2b1/8/PPPP1PPP/RNB1K1NR b KQ - 0 7";

    std::string currentFen = "rnbqkbnr/pppppppp/s7/Q7/5Q2/14Q2/QPPPPPPP/RNBQKBNR w KQkq - 0 1";



    

    
    while (true){
        try {
            GameState gameState(currentFen);
            int status = gameState.checkGameStatus();
            gameState.printASCII();
            std::cout << currentFen << std::endl;
            std::cout << status << std::endl;

            if (status != gameStatus::ongoing){

                return ;
            }

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

            gameState.setColorToMove(enemyOf(gameState.getColorToMove()));
            status = gameState.checkGameStatus();
            std::string newFen = gameState.encode();

             

            
            std::cout << "{\n\"game_status\" : " << status << ",\n";
            std::cout << "\"new_FEN\" : \"" << newFen << "\",\n";
            std::cout << "\"applied_move\" : \"" << gameState.getMoveConstruction() << "\"\n}";
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

        std::cout << "{\n\"allowed_move\" : " ;
        std::cout << "[ ";

        unsigned counter = 0;
        for (auto &move : fetchedMove){
            
            std::cout << move;
            if (counter != fetchedMove.size() - 1)
                std::cout << ", ";

            counter++;
        }
        std::cout << "]\n}";
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
