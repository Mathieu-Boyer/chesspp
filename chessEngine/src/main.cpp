#include "iostream"
#include "Rook.hpp"
#include "APiece.hpp"
#include "Knight.hpp"

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

        }
    }
}

int main (){

    std::cout << "Yipeee" << std::endl;


    std::vector<std::unique_ptr<APiece>> pieces;

    createPiecesFromString("RNNR", pieces);

     for (auto &piece : pieces){
        piece->describe();
        piece->setColor("Black");
        piece->describe();
    }

    return 0;
}