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


std::string currentFen = "3bK3/2k5/5q2/5P11/611/8/8/8 w - - 6 54";

    // boardStart.printASCII();

    while (true){
        try {
            // Board board{};
            GameState gameState(currentFen);
            Board &board = gameState.getRefToBoard();
            // gameState.getRefToBoard().printASCII(gameState);

            std::cout << currentFen << std::endl;

            std::string rawMove;

            std::cin >> rawMove;
            move moveToTry(rawMove);
            if (moveToTry.from != -1 && moveToTry.to == -1)
                board.printASCII(board.getPieceLegalMove(moveToTry.from, gameState));
            else if (moveToTry.from >= 0 && moveToTry.to >= 0){
                board.applyMove(moveToTry);
                // std::cout << board.checkMateSituation(gameStateStart.getColorToMove()) << " ?????? " << std::endl;
            
                currentFen = gameState.encode();

                // gameState.getRefToBoard().printASCII();
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