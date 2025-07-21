#include "Board.hpp"
#include "King.hpp"
#include "colors.hpp"
#include "utils.hpp"
#include "GameState.hpp"
#include <memory>

Board::Board(const Board& board){
    whiteKingPosition = board.whiteKingPosition;
    blackKingPosition = board.blackKingPosition;
    // possibleEnPassantNextHalfMove = board.possibleEnPassantNextHalfMove;
    // possibleEnPassantNow = board.possibleEnPassantNow;
    // dissAllowedCastles = board.dissAllowedCastles;
    // allowedCastles = board.allowedCastles;
    // colorToMove = board.colorToMove;
    unsigned counter = 0;

    // std::cout << "ILAUCH ZIOCysgcbnzuhcbz!cyzbczygcbzyègbnH A09XJ" << std::endl;
    for (auto &element : board.data){
        if (element != nullptr){
            this->data[counter] = element->clone();
            // this->data[counter]->describe();
        }

        counter++;
    }
}

const std::array<std::unique_ptr<APiece>, 64> &Board::getData(){
    return data;
}




void Board::placePieces(const std::string &fen) {

    unsigned counter = 0;
    for (auto &character : fen){
        if (character == '/')
            continue;
        if (std::isdigit(character)){
            counter += character - '0';
            continue;
        }

        data[counter] = pieceFactory(character);
        if (data[counter]->getRepresentation() == "K"){
            whiteKingPosition = counter;
        } else if (data[counter]->getRepresentation() == "k"){
            blackKingPosition = counter;
        }

        counter++;
    }
}



std::unique_ptr<Board> Board::clone() const{
    return std::make_unique<Board> (*this);
}







void Board::applyCastle(const move &move, GameState &gameState){

    
    if (gameState.getAllowedCastles().find('K') != std::string::npos && move.to == move::boardMap.at("g1"))
        data[move::boardMap.at("f1")] = std::move(data[move::boardMap.at("h1")]);
    else if (gameState.getAllowedCastles().find('k') != std::string::npos && move.to == move::boardMap.at("g8"))
        data[move::boardMap.at("f8")] = std::move(data[move::boardMap.at("h8")]);
    else if (gameState.getAllowedCastles().find('Q') != std::string::npos && move.to == move::boardMap.at("c1"))
        data[move::boardMap.at("d1")] = std::move(data[move::boardMap.at("a1")]);
    else if (gameState.getAllowedCastles().find('q') != std::string::npos && move.to == move::boardMap.at("c8"))
        data[move::boardMap.at("d8")] = std::move(data[move::boardMap.at("a8")]);

    if (data[move.from]->getColor() == "White")
        gameState.setdissAllowedCastles("KQ");
    else
        gameState.setdissAllowedCastles("kq");
}

void removeCharFrom(char toRemove, std::string &string){
    std::cout << string << " " << toRemove << std::endl;
    string.erase(std::remove(string.begin(), string.end(), toRemove), string.end());
    std::cout << string << " " << toRemove << std::endl;

}






void Board::applyMove(const move &move, GameState& gameState){
    if (data[move.from] == nullptr)
        throw std::runtime_error("The " + move::inverseBoardMap.at(move.from) + " 'From' square is empty");
    // if (data[move.from]->getColor() != colorToMove)
    //     throw std::runtime_error("This is not the turn of the piece you are trying to move.");

//////// the thing to make sure of not doing each time
    auto legalMoves = data[move.from]->getPseudoLegalMoves(gameState, move.from);
    // auto legalMoves = getPieceLegalMove(move.from, gameState);

    // gameState

    // std::cout << move::inverseBoardMap.at(move.from) << " hum " << legalMoves.size() << std::endl;

    // for (auto &meow : legalMoves){
    //     std::cout << move::inverseBoardMap.at(move.from) << "-"<< move::inverseBoardMap.at(meow) << "<<<<<<<<<<<<<< " << std::endl;
    // }
    // auto legalMoves = getPieceLegalMove(move.from,);

    if (data[move.from]->getName() == "Pawn"){
        if (abs(move.from - move.to) == 16){
            if ((data[move.to - 1] != nullptr && squaresAreOnSameRow(move.to,move.to - 1) && data[move.to - 1]->getName() == "Pawn")){
                if (data[move.to - 1]->getColor() != data[move.from]->getColor())
                    gameState.setPossibleEnPassantNextHalfMove(data[move.from]->getColor() == "White" ?  move.to + 8 : move.to - 8);
            }
            if ((data[move.to + 1] != nullptr && squaresAreOnSameRow(move.to,move.to + 1) && data[move.to + 1]->getName() == "Pawn")){
                if (data[move.to + 1]->getColor() != data[move.from]->getColor())
                    gameState.setPossibleEnPassantNextHalfMove(data[move.from]->getColor() == "White" ?  move.to + 8 : move.to - 8);
            }
        }
    }

    if (std::ranges::find(legalMoves, move.to) == legalMoves.end()){

        throw std::runtime_error("The move : " + move::inverseBoardMap.at(move.to) + " illegal ! you are going to jail.");
        exit(42);
    }

    if (move.to == gameState.getPossibleEnPassantNow() && data[move.from]->getName() == "Pawn"){
        data[move.from]->getColor() == "White" ? data[move.to + 8].reset() : data[move.to - 8].reset();
        gameState.setPossibleEnPassantNextHalfMove(0);
        gameState.setPossibleEnPassantNow(0);
    }

    if (data[move.from]->getName() == "King")
        applyCastle(move, gameState);
    if (data[move.from]->getName() == "Rook"){
        if (gameState.getAllowedCastles() != "-"){
            if (data[move.from]->getColor() == "White"){
                if (move.from > whiteKingPosition)
                    gameState.setdissAllowedCastles(gameState.getdissAllowedCastles() += "K");
                else
                    gameState.setdissAllowedCastles(gameState.getdissAllowedCastles() += "Q");

            }else{
                if (move.from > blackKingPosition)
                   gameState.setdissAllowedCastles(gameState.getdissAllowedCastles() += "k");
                else
                    gameState.setdissAllowedCastles(gameState.getdissAllowedCastles() += "q");
            }
        }
    }

    if (data[move.from]->getName() == "Pawn"){

        if (promotionAssertions(*this, move)){
            auto promotedPiece = pieceFactory(move.promotion);
            data[move.from] = std::move(promotedPiece);
        }

    }

    data[move.to] = std::move(data[move.from]);

    if (data[move.to] && data[move.to]->getName() == "King"){
        if (gameState.getColorToMove() == "White")
            whiteKingPosition = move.to;
        else
            blackKingPosition = move.to;
    }

}


void Board::setWhiteKingPosition(int position){
    // std::cout << whiteK
    whiteKingPosition = position;
}
void Board::setBlackKingPosition(int position){
    blackKingPosition = position;
}

// void Board::setPossibleEnPassantNow(int enPassantSquare){
//     possibleEnPassantNow = enPassantSquare;
// }


int Board::getWhiteKingPosition(){
    return whiteKingPosition;
}
int Board::getBlackKingPosition(){
    return blackKingPosition;
}

APiece *Board::getPieceAt(int position){
    if (!validSquare(position))
        return nullptr;
    return data[position].get();
}

const APiece *Board::getPieceAt(int position) const{
    if (!validSquare(position))
        return nullptr;
    return data[position].get();
}

void Board::setPieceAt(int position, std::unique_ptr<APiece> piece){
    data[position] = std::move(piece);
}

std::unique_ptr<APiece> &Board::accessPieceSlot(int pos) {
    return data[pos];
}
void Board::clearPieceAt(int position){
    data[position].reset();
}