#include "iostream"
#include "Rook.hpp"
#include "APiece.hpp"
#include "Knight.hpp"
#include "King.hpp"
#include "Queen.hpp"
#include "Bishop.hpp"

void createPiecesFromString(std::string string, std::vector<std::unique_ptr<APiece>> &pieces){
    for (auto &character : string){

        switch (character)
        {
            case 'R':{
                Rook rook;
                pieces.push_back(rook.clone());
                break;
            }

            case 'N':{
                Knight knight;
                pieces.push_back(knight.clone());
                break;
            }

            case 'K':{
                King king;
                pieces.push_back(king.clone());
                break;
            }

            case 'Q':{
                Queen queen;
                pieces.push_back(queen.clone());
                break;
            }

            case 'B':{
                Bishop bishop;
                pieces.push_back(bishop.clone());
                break;
            }
        }
    }
}

int main (){

    std::cout << "Yipeee" << std::endl;


    std::vector<std::unique_ptr<APiece>> pieces;

    createPiecesFromString("R N K Q B", pieces);

     for (auto &piece : pieces){
        piece->describe();
        piece->setColor("Black");
        piece->describe();
    }

    return 0;
}