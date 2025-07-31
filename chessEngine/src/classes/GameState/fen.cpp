#include "GameState.hpp"

void GameState::decode(){
    data = split(raw, ' ');

    if (data.size() != 8)
        throw std::runtime_error("Malformed FEN code. Please use the following format : [Board Representation] [color to move] [allowed castles] [half moves counter] [full moves counter] [last played piece] [queens informations].");
    for (auto& d : data)
        if (d.empty()) throw std::runtime_error("You provided an empty Fen element.");

    setPossibleEnPassantNextHalfMove(0);
    if (data[1] == "w")
        colorToMove = "White";
    else if (data[1] == "b")
        colorToMove = "Black";
    else
        throw std::runtime_error("The provided color does not exist.");

    allowedCastles = data[2];

    if (data[3] != "-")
        possibleEnPassantNow = move::boardMap.at(data[3]);

    currentHalfMove = std::stoi(data[4]);
    currentFullMove = std::stoi(data[5]);


    lastMovedPiece = data[6];
    std::vector<std::string> queensInfos = split(data[7], ';');

    if (queensInfos.empty()) throw std::runtime_error("Queen infos can't be empty.");
    for (auto& info : queensInfos) 
        if (info.empty()) throw std::runtime_error("You provided an empty queen info element.");
    whiteQueenInfos = queensInfos[0] ;
    blackQueenInfos = queensInfos[1] ;
    board->placePieces(data[0]);
    setColorToMove(colorToMove);
}

std::string GameState::encode() {

    std::string fenString;
    std::string boardAsString ;
    int spaceCounter = 0;

    for (int i = 0; i < 64; ++i) {
        const auto& piece = board->getData()[i];

        if (piece == nullptr) {
            spaceCounter++;
        }
        else {
            if (spaceCounter > 0) {
                boardAsString += std::to_string(spaceCounter);
                spaceCounter = 0;
            }
            boardAsString += piece->getRepresentation();
        }
        if ((i + 1) % 8 == 0) {
            if (spaceCounter > 0) {
                boardAsString += std::to_string(spaceCounter);
                spaceCounter = 0;
            }
            if (i < 63) {
                boardAsString += '/';
            }
        }
    }

    this->data[0] = boardAsString;
    this->data[1] = this->data[1] == "w" ? "b" : "w";

    for (auto character : getdissAllowedCastles())
        this->data[2].erase(std::remove(this->data[2].begin(), this->data[2].end(), character), this->data[2].end());

    if ( this->data[2].empty())
        this->data[2] = "-";

    if (getPossibleEnPassantNextHalfMove() )
        this->data[3] = move::inverseBoardMap.at(getPossibleEnPassantNextHalfMove());
    else
        this->data[3] = "-";
    if (this->data[1] == "w"){
        setCurrentFullMove(getCurrentFullMove() + 1);
        data[5] = std::to_string(currentFullMove);
    }
    data[4] = std::to_string(currentHalfMove);
    data[6] = lastMovedPiece;
    data[7] = whiteQueenInfos + ";" + blackQueenInfos;
    unsigned counter = 0;
    for (auto&fenElement : data){
        fenString += fenElement;
        if (counter != data.size() - 1)
            fenString += " ";
        counter++;
    }

    return fenString;
}