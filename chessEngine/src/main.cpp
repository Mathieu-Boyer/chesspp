#include <iostream>
#include <cctype>
#include "APiece.hpp"
#include "utils.hpp"
#include "Knight.hpp"
#include "King.hpp"
#include "Queen.hpp"
#include "Bishop.hpp"
#include "Pawn.hpp"
#include "Rook.hpp"
#include "GameState.hpp"
#include "move.hpp"


void createPiecesFromString(std::string string, std::vector<std::unique_ptr<APiece>> &pieces){
    for (auto &character : string){

        switch (character)
        {
            case 'r':
            case 'R':{
                Rook rook(std::islower(character) ? "Black" : "White");
                pieces.push_back(rook.clone());
                break;
            }
            case 'n':
            case 'N':{
                Knight knight(std::islower(character) ? "Black" : "White");
                pieces.push_back(knight.clone());
                break;
            }

            case 'k':
            case 'K':{
                King king(std::islower(character) ? "Black" : "White");
                pieces.push_back(king.clone());
                break;
            }

            case 'q':
            case 'Q':{
                Queen queen(std::islower(character) ? "Black" : "White");
                pieces.push_back(queen.clone());
                break;
            }

            case 'b':
            case 'B':{
                Bishop bishop(std::islower(character) ? "Black" : "White");
                pieces.push_back(bishop.clone());
                break;
            }

            case 'p':
            case 'P':{
                Pawn pawn(std::islower(character) ? "Black" : "White");
                pieces.push_back(pawn.clone());
                break;
            }
        }
    }
}

void printIntVector(const std::vector<int> &toPrint){
    for (auto& el : toPrint)
        std::cout << "move : " << el << " " << std::endl;
}

int main (){

    std::cout << "[ Chess++ | engine ]" << std::endl;

    // GameState gameState2("rnbq1bnr/pppppppp/8/8/11212N/2kK4/PPPPPPPQ/RNBQ1BNR w KQkq - 0 1");
    // std::cout << gameState.encode();
    // int pos = 39;

    // if ()
    // board.getData()[pos]->describe();
    // board.printASCII(board.getData()[pos]->getLegalMoves(board, pos));
    
    
    std::string currentFen = "r3kbnr/ppp1pppp/3p4/4P3/8/8/PPPP1PPP/RNBQK2R w KQkq - 0 1";
    // std::string currentFen = "rnbqkbnr/ppp1pppp/8/8/3p4/4P3/PPPP1PPP/RNBQKBNR w KQkq - 0 1";

    Board boardStart;

    GameState gameStateStart(currentFen, boardStart);
                std::cout << currentFen << std::endl;

    gameStateStart.getBoard().printASCII();
    while (true){
        try {
            Board board{};
            GameState gameState(currentFen, board);

            std::cout << currentFen << std::endl;

            std::string rawMove;
            std::cin >> rawMove;
            move moveToTry(rawMove);
            if (moveToTry.from != -1 && moveToTry.to == -1)
                board.printASCII(board.getPieceLegalMove(moveToTry.from));
            else if (moveToTry.from >= 0 && moveToTry.to >= 0){
                board.applyMove(moveToTry);
                currentFen = gameState.encode();
                gameState.getBoard().printASCII();

            }
            else
                throw std::runtime_error("Move not correctly formated");
        }catch(const std::exception& e){
            std::cerr << e.what() << std::endl;
        }

    }
    // std::vector<std::unique_ptr<APiece>> pieces;

    // createPiecesFromString("RrNnKkQqBbPp", pieces);

    //  for (auto &piece : pieces){
    //     piece->describe();
    //     // piece->setColor("Black");
    //     // piece->describe();
    // }

    return 0;
}