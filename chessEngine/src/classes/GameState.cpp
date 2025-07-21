#include "GameState.hpp"
#include "Board.hpp"
#include "colors.hpp"

GameState::GameState(const std::string &fen) : raw(fen) , board(std::make_unique<Board>()){
    decode();
    std::cout << data[1]  << std::endl;
    if (data[1] == "w")
        colorToMove = "White";
    else if (data[1] == "b")
        colorToMove = "Black";
    else
        throw std::runtime_error("The provided color does not exist.");

    // setAllowedCastles(data[2]);
    allowedCastles = data[2];
    if (data[3] != "-"){
        // board->setPossibleEnPassantNow(move::boardMap.at(data[3]));
        possibleEnPassantNow =move::boardMap.at(data[3]);
    }
    board->placePieces(data[0]);
    setColorToMove(colorToMove);


    if (checkMateSituation(this->colorToMove)){
        printASCII();
        std::cout << (this->colorToMove == "White" ? "Black" : "White") << " won by mate.";
        std::exit(2);
    } 
    
    if (staleMate(colorToMove)){
        printASCII();
        std::cout << "Stalemate" << std::endl;
        std::exit(3);
    }

    // std::cout << colorToMove << std::endl;
    printASCII();

    // std::cout << board.checkMateSituation(this->colorToMove) << " ?????? " << std::endl;
}

GameState::GameState(const GameState &gameState) : board(gameState.getRefToBoard().clone()){
    if (this != &gameState){
        this->colorToMove = gameState.colorToMove;
        this->data = gameState.data;
        this->raw = gameState.raw;
    }

    // std::cout << board.checkMateSituation(this->colorToMove) << " ?????? " << std::endl;
}

// GameState::GameState(const GameState& gameState): board(gameState.board){
//     if (this != &gameState){
//         this->raw = gameState.raw;
//         this->data = gameState.data;
//         this->colorToMove = gameState.colorToMove;
//         // this->board = Board::Board(gameState.board);
//     }
// }


void GameState::decode(){
    data = split(raw, ' ');
}

std::string GameState::encode() {

    std::string fenString;
    std::string boardAsString ;
    int spaceCounter = 0;
    // int counter = 0;


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

    if ( this->data[2].empty()){
        this->data[2] = "-";
    }
    if (getPossibleEnPassantNextHalfMove())
        this->data[3] = move::inverseBoardMap.at(getPossibleEnPassantNextHalfMove());
    else
        this->data[3] = "-";

    for (auto&fenElement : data)
        fenString += fenElement + " ";

    
    return fenString;
}

Board &GameState::getRefToBoard() const{
    return *board;
}


std::vector<int> GameState::squareIsCompromised(const std::string &enemy, int target){


    Board &board = getRefToBoard();
    std::vector<int> positionsOfAllCheckers;

    for (int i = 0 ; i < 64; i++){
        APiece *currentPiece = board.getPieceAt(i);

        if (currentPiece == nullptr || currentPiece->getColor() != enemy || currentPiece->getName() == "King")
            continue;
        if (currentPiece->canAttackSquare(i, target, *this)){
            positionsOfAllCheckers.push_back(i);
        }
    }

    return positionsOfAllCheckers;
}



std::vector<int> GameState::getPieceLegalMove(int position){

    if (position > 63 || position < 0)
        throw std::runtime_error("This square does not exist.");

    Board &board = getRefToBoard();
    APiece *piece = board.getPieceAt(position);
    if (piece == nullptr)
        throw std::runtime_error("Selected square is empty.");

    // std::cout << move::inverseBoardMap.at(position) << std::endl;
    if (piece->getColor() != colorToMove)
        throw std::runtime_error("This is not the turn of the piece you are trying to get the moves from. (" + colorToMove + ")");
    auto pseudoLegal = piece->getPseudoLegalMoves(*this, position);
    std::vector<int> legalMoves;

    for (auto &moveToTry : pseudoLegal){
        GameState gameStateCpy(*this);
        APiece *pieceOfCpyBoard = gameStateCpy.getRefToBoard().getPieceAt(position);
        
        std::string constructedRawMove = move::inverseBoardMap.at(position)+"-"+move::inverseBoardMap.at(moveToTry);

        if (pieceOfCpyBoard && pieceOfCpyBoard->getName() == "Pawn" && (pieceOfCpyBoard->isOnRow(1, moveToTry) || pieceOfCpyBoard->isOnRow(8, moveToTry))){
            
            constructedRawMove += "=";
            if (colorToMove == "White")
                constructedRawMove += "Q";
            else
                constructedRawMove += "q";
        }
        // std::cout << constructedRawMove << "<------" << std::endl;

        move move(constructedRawMove);

        
        // std::cout << "////////////////////////" << std::endl;
        gameStateCpy.applyMoveSimulation(move);
        // std::cout << "\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\" << std::endl;


        if (gameStateCpy.kingIsInCheck(colorToMove).size() == 0){
            legalMoves.push_back(moveToTry);
            // std::cout << moveToTry << std::endl;
        // for (auto legalMove : legalMoves)
            // std::cout << move::inverseBoardMap.at(position) <<"-"<< move::inverseBoardMap.at(moveToTry) << " Is supposed to Be Legal" << std::endl;
        }
    }
    return legalMoves;
}




void GameState::applyMoveSimulation(const move &move){


    Board &board = getRefToBoard();
    APiece *piece = board.getPieceAt(move.from);

    if (piece == nullptr)
        throw std::runtime_error("The " + move::inverseBoardMap.at(move.from) + " 'From' square is empty");
    if (piece->getColor() != colorToMove)
        throw std::runtime_error("This is not the turn of the piece you are trying to move.");

////////// the thing to make sure of not doing each time
    // auto legalMoves = piece->getPseudoLegalMoves(*this, move.from);
    // auto legalMoves = getPieceLegalMove(move.from, gameState);

    // // gameState

    // for (auto &meow : legalMoves){
    //     std::cout << move::inverseBoardMap.at(move.from) << "-"<< move::inverseBoardMap.at(meow) << "<<<<<<<<<<<<<< " << std::endl;
    // }
    // auto legalMoves = getPieceLegalMove(move.from,);


    if (piece->getName() == "Pawn"){
        if (abs(move.from - move.to) == 16){
            if ((board.getData()[move.to - 1] != nullptr && squaresAreOnSameRow(move.to, move.to - 1) && board.getData()[move.to - 1]->getName() == "Pawn")){
                if (board.getData()[move.to - 1]->getColor() != piece->getColor())
                    possibleEnPassantNextHalfMove = piece->getColor() == "White" ?  move.to + 8 : move.to - 8;
            }
            if ((board.getData()[move.to + 1] != nullptr && squaresAreOnSameRow(move.to,move.to + 1) && board.getData()[move.to + 1]->getName() == "Pawn")){
                if (board.getData()[move.to + 1]->getColor() != piece->getColor())
                    possibleEnPassantNextHalfMove = piece->getColor() == "White" ?  move.to + 8 : move.to - 8;
            }
        }
    }

    // if (std::ranges::find(legalMoves, move.to) == legalMoves.end()){

    //     throw std::runtime_error("The move : " + move::inverseBoardMap.at(move.to) + " illegal ! you are going to jail.");
    //     exit(42);
    // }

    if (move.to == possibleEnPassantNow && piece->getName() == "Pawn"){
        piece->getColor() == "White" ? board.clearPieceAt(move.to + 8) : board.clearPieceAt(move.to - 8);

        
        possibleEnPassantNextHalfMove = 0;
        possibleEnPassantNow = 0;
    }

    if (piece->getName() == "King")
        board.applyCastle(move, *this);
    if (piece->getName() == "Rook"){
        if (allowedCastles != "-"){
            if (piece->getColor() == "White"){
                if (move.from > board.getWhiteKingPosition())
                    dissAllowedCastles+="K";
                else
                    dissAllowedCastles+="Q";

            }else{
                if (move.from  > board.getBlackKingPosition())
                   dissAllowedCastles+="k";
                else
                    dissAllowedCastles+="q";
            }
        }
    }

    if (piece->getName() == "Pawn"){

        if (promotionAssertions(board, move)){
            board.setPieceAt(move.from , pieceFactory(move.promotion));
        }

    }

    // std::unique_ptr<APiece> &fromSlot = ;

    board.setPieceAt(move.to, std::move(board.accessPieceSlot(move.from)));

    

    if (board.getPieceAt(move.to)->getName() == "King"){
        if (colorToMove == "White")
            board.setWhiteKingPosition(move.to);
        else
            board.setBlackKingPosition(move.to);
    }
}
/// /////////////////////////////// sepppppp
std::vector<int> GameState::kingIsInCheck(const std::string &color){

    // std::cout << "---->white king : "<< whiteKingPosition <<"<-----" << std::endl;
    // std::cout << "---->black king : "<< blackKingPosition <<"<-----" << std::endl;

    Board &board = getRefToBoard();

    if (color == "White"){
        // std::cout << "Checking : white " << std::endl;
    // std::cout << move::inverseBoardMap.at(board.getWhiteKingPosition()) << std::endl;

        return squareIsCompromised("Black", board.getWhiteKingPosition());
    }
    else{
        // std::cout << "Checking : black " << std::endl;
    // std::cout << move::inverseBoardMap.at(board.getBlackKingPosition()) << std::endl;

        return squareIsCompromised("White", board.getBlackKingPosition());
    }

}

bool GameState::moreThan1PieceCanCheck(const std::string &color){

    Board &board = getRefToBoard();

    if (color == "White"){
        // for (auto meow : squareIsCompromised("Black", whiteKingPosition))
        //     std::cout << "---->> "<< move::inverseBoardMap.at(meow) << std::endl;
        return squareIsCompromised("Black", board.getWhiteKingPosition()).size() > 1;
    }
    else
        return squareIsCompromised("White", board.getBlackKingPosition()).size() > 1;
    // for (auto waw : positionsOfAllCheckers){
    //     std::cout << move::inverseBoardMap.at(waw) << " aoeeee " << std::endl;
    // }
    // if (positionsOfAllCheckers.size() > 0)
    //     std::cout << " lafin " << std::endl;

    // return positionsOfAllCheckers.size() > 1;
}


bool GameState::checkIngPieceCanBeCaptured(const std::string &color, int positionOfChecker){
    // int checkerPos = positionsOfAllCheckers[0];
    // if (color == "White")
        // squareIsCompromised("Black", checkerPos);
    // else


    if (color == "White"){
        // std::cout << "can black take in " << move::inverseBoardMap.at(positionOfChecker) << std::endl;

        return squareIsCompromised("Black", positionOfChecker).size() > 0; 
    }
    else{
        // std::cout << "can white take in " << move::inverseBoardMap.at(positionOfChecker) << std::endl;
        // for (auto test : squareIsCompromised("White", positionOfChecker)){
        //     // std::cout << move::inverseBoardMap.at(test) << ":::";
        // }
        return squareIsCompromised("White", positionOfChecker).size() > 0;
    }


    // for (auto waw : positionsOfAllCheckers){
    //     std::cout << move::inverseBoardMap.at(waw) << " aoeeee " << std::endl;
    // }
    // if (positionsOfAllCheckers.size() > 0)
    //     std::cout << " lafin " << std::endl;

    // if (color == "White")
    // squareIsCompromised(color, checkerPos);
    // else


    // return positionsOfAllCheckers.size() > 0;
}

bool diagonalInterpositionCheck(GameState& gameState, int pieceA, int pieceB, const std::string& interposeColor){
    
    int rankA = pieceA / 8;
    int rankB = pieceB / 8;
    int fileA = pieceA % 8;
    int fileB = pieceB % 8;

    
    // std::cout << "A" << std::endl;
    if (std::abs(rankA - rankB) != std::abs(fileA - fileB))
        return false;
    // std::cout << "B" << std::endl;

    // int diff = std::abs(pieceA - pieceB);

    int pieceDifference = std::abs(pieceA - pieceB);

    if (!(pieceDifference % 7 == 0 || pieceDifference % 9 == 0))
        return false;
    // std::cout << "C" << std::endl;

    int orientation = (pieceDifference % 7 == 0) ? 7 : 9;
    int direction = (pieceA > pieceB ? -1 : 1);
    int step = orientation * direction;

    for (int i = pieceA + step; i != pieceB; i += step)
        if (gameState.squareIsCompromised(interposeColor, i).size() > 0){
            // std::cout << "double Z" << std::endl;

            // for (auto meow : board.squareIsCompromised(interposeColor, i))
            //     std::cout <<move::inverseBoardMap.at(meow) << "\n";

            return true;
        }
    // std::cout << "D" << std::endl;
    
    return false;
}

bool orthogonalInterpositionCheck(GameState& gameState, int pieceA, int pieceB, const std::string& interposeColor){
    int rankA = pieceA / 8;
    int rankB = pieceB / 8;
    // int fileA = pieceA % 8;
    // int fileB = pieceB % 8;

    // std::cout << "ichi" << std::endl;

    if (!(rankA == rankB))
        return false;

    int pieceDifference = std::abs(pieceA - pieceB);

    // std::cout << "ni" << std::endl;

    if (!(pieceDifference % 1 == 0 || pieceDifference % 8 == 0))
        return false;

    int orientation = (pieceDifference % 1 == 0) ? 1 : 8;
    int direction = (pieceA > pieceB ? -1 : 1);
    int step = orientation * direction;
    // std::cout << "Nyan" << std::endl;

    for (int i = pieceA + step; i != pieceB; i += step){
        // std::cout << (move::inverseBoardMap.at(i)) << std::endl;
        if (gameState.squareIsCompromised(interposeColor, i).size() > 0){
            // for (auto meow : board.squareIsCompromised(interposeColor, i))
            //     std::cout <<move::inverseBoardMap.at(meow) << "\n";
            return true;
        }

    }

    return false;
}

bool GameState::pieceCanInterpose(int pieceA, int pieceB, const std::string &pieceName, const std::string& interposeColor){
    if (pieceName != "Queen" && pieceName != "Rook" && pieceName != "Bishop")
        return false;
    
    if (pieceName == "Bishop")
        return diagonalInterpositionCheck(*this, pieceA, pieceB, interposeColor);
    else if (pieceName == "Rook")
        return orthogonalInterpositionCheck(*this, pieceA, pieceB, interposeColor);
    else{
        return diagonalInterpositionCheck(*this, pieceA, pieceB, interposeColor) || orthogonalInterpositionCheck(*this, pieceA, pieceB, interposeColor);
        
    }
}


bool GameState::checkMateSituation(const std::string &color){

    Board &board = getRefToBoard();
    std::string enemy = enemyOf(color);
    int kingPosition = (color == "White" ? board.getWhiteKingPosition() : board.getBlackKingPosition());


    // std::cout << "I AM " << color << " ENEMY IS ////////// " << enemy << std::endl;
    // std::cout << "euuhhh salut -1" << std::endl;

    std::vector<int> kingCheckers = kingIsInCheck(color);
    if (kingCheckers.size() == 0)
        return false;
    // std::cout << "oh no.." << std::endl;
    std::cout << "euuhhh salut 0" << std::endl;

    if (getPieceLegalMove(kingPosition).size() > 0)
        return false;
    
    std::cout << "euuhhh salut 1" << color << std::endl;

    if (moreThan1PieceCanCheck(color))
        return true;

    std::cout << "euuhhh salut 2" << std::endl;

    if (checkIngPieceCanBeCaptured(enemy, kingCheckers[0]))
        return false;
    std::cout << "euuhhh salut 3" << std::endl;

    if (pieceCanInterpose(kingPosition, kingCheckers[0], board.getPieceAt(kingCheckers[0])->getName(), color))
        return false;

    std::cout << "euuhhh salut 4" << std::endl;
    // std::cout << move::inverseBoardMap.at(blackKingPosition) << " <- b -- w -> " << move::inverseBoardMap.at(whiteKingPosition)<< std::endl;

    return true;
}

bool GameState::staleMate(const std::string &color){
    // std::cout << "brruuuuuh " << color << std::endl;
    std::vector<int> kingCheckers = kingIsInCheck(color);
    Board &board = getRefToBoard();
    if (kingCheckers.size() > 0)
        return false;
    for (int i = 0; i < 64 ; i++){
        APiece *piece = board.getPieceAt(i);
        if (piece == nullptr || piece->getColor() != color)
            continue;
        if (getPieceLegalMove(i).size() > 0)
            return false;
    }

    return true;
}





void GameState::printASCII(){
    int counter = 0;
    Board &board = getRefToBoard();
    for (auto &square : board.getData()){

        if ((counter == board.getWhiteKingPosition() || counter == board.getBlackKingPosition()) && (board.getPieceAt(counter)->getColor() == colorToMove)){
            if (staleMate(colorToMove))
                std::cout << PINK ;
            else if (checkMateSituation(colorToMove))
                std::cout << RED;
            else if (kingIsInCheck(colorToMove).size() > 0)
                std::cout << ORANGE;

            // std::cout << "\n";
            // if (dynamic_cast<King*>(data[counter].get())->isInCheck(*this))
        }

        if (square == nullptr){
            std::cout << " . ";
        }else{
            std::cout << " " << square->getRepresentation() << " " << RESET_COLOR;
        }



        counter++;
        if (counter % 8 == 0)
            std::cout << std::endl;
    }

    std::cout << std::endl;
}


void GameState::printASCII(const std::vector<int> &moves){
{

        unsigned counter = 0;

        Board &board = getRefToBoard();

        for (auto &square : board.getData()){
            if (std::ranges::find(moves, counter) != moves.end()){
                std::cout << " x ";
            }
            else if (square == nullptr){
                std::cout << " . ";
            }else{
                std::cout << " " << square->getRepresentation() << " ";
            }

            counter++;
            if (counter % 8 == 0)
                std::cout << std::endl;
        }

        std::cout << std::endl;

    }
}

void GameState::setColorToMove(const std::string &color){
    colorToMove = color;
}

void GameState::setdissAllowedCastles(const std::string &dissAllowedCastles){
    this->dissAllowedCastles = dissAllowedCastles;
}

std::string GameState::getdissAllowedCastles(){
    return dissAllowedCastles;
}

void GameState::setAllowedCastles(const std::string &allowedCastles){
    this->allowedCastles = allowedCastles;
}

std::string GameState::getAllowedCastles(){
    return allowedCastles;
}


int GameState::getPossibleEnPassantNextHalfMove(){
    return possibleEnPassantNextHalfMove;
}

int GameState::getPossibleEnPassantNow(){
    return possibleEnPassantNow;
}
void GameState::setPossibleEnPassantNextHalfMove(int value){
    possibleEnPassantNextHalfMove = value;
}

void GameState::setPossibleEnPassantNow(int value){
    possibleEnPassantNow = value;
}

std::string GameState::getColorToMove(){
    return colorToMove;
}
