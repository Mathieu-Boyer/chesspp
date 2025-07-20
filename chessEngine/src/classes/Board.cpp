#include "Board.hpp"
#include "King.hpp"
#include "colors.hpp"
#include "utils.hpp"
#include "GameState.hpp"

Board::Board(const Board& board){
    whiteKingPosition = board.whiteKingPosition;
    blackKingPosition = board.blackKingPosition;
    possibleEnPassantNextHalfMove = board.possibleEnPassantNextHalfMove;
    possibleEnPassantNow = board.possibleEnPassantNow;
    dissAllowedCastles = board.dissAllowedCastles;
    allowedCastles = board.allowedCastles;
    colorToMove = board.colorToMove;
    unsigned counter = 0;

    std::cout << "ILAUCH ZIOCysgcbnzuhcbz!cyzbczygcbzyègbnH A09XJ" << std::endl;
    for (auto &element : board.data){
        if (element != nullptr){
            this->data[counter] = element->clone();
            this->data[counter]->describe();
        }

        counter++;
    }
}

const std::array<std::unique_ptr<APiece>, 64> &Board::getData(){
    return data;
}


void Board::setColorToMove(const std::string &color){
    colorToMove = color;
}



void Board::placePieces(const std::string &fen) {

    unsigned counter = 0;
    for (auto &character : fen){
        if (character == '/')
            continue;
        if (std::isdigit(character)){
            counter += character - '0';
            // std::cout << counter << std::endl;
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

std::vector<int> Board::getPieceLegalMove(int position, GameState &gameState){

    if (position > 63 || position < 0)
        throw std::runtime_error("This square does not exist.");
    if (data[position] == nullptr)
        throw std::runtime_error("Selected square is empty.");

    if (data[position]->getColor() != colorToMove)
        throw std::runtime_error("This is not the turn of the piece you are trying to get the moves from.");
    auto pseudoLegal = data[position]->getPseudoLegalMoves(*this, position);
    std::vector<int> legalMoves;


    for (auto &moveToTry : pseudoLegal){
        // Board gameStateCpy.getBoard()(*this);
        std::cout << "pseudo legal :::: " << move::inverseBoardMap.at(moveToTry) << std::endl;
        GameState gameStateCpy(gameState);
        // Board &cpyBoard = gameStateCpy.getBoard();

        std::string constructedRawMove = move::inverseBoardMap.at(position)+"-"+move::inverseBoardMap.at(moveToTry);

        if (gameState.getRefToBoard().data[position] && gameState.getRefToBoard().data[position]->getName() == "Pawn" && (gameState.getRefToBoard().data[position]->isOnRow(1, moveToTry) || gameState.getRefToBoard().data[position]->isOnRow(8, moveToTry))){
            
            constructedRawMove += "=";
            if (colorToMove == "White")
                constructedRawMove += "Q";
            else
                constructedRawMove += "q";
        }
        std::cout << constructedRawMove << "<------" << std::endl;

        move move(constructedRawMove);

        
        std::cout << "////////////////////////" << std::endl;
        gameStateCpy.getRefToBoard().applyMoveSimulation(move);
        std::cout << "\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\" << std::endl;


        if (gameStateCpy.getRefToBoard().kingIsInCheck(colorToMove).size() == 0){

            legalMoves.push_back(moveToTry);

        // for (auto legalMove : legalMoves)
            std::cout << move::inverseBoardMap.at(position) <<"-"<< move::inverseBoardMap.at(moveToTry) << " Is supposed to Be Legal" << std::endl;
        }
    }
    return legalMoves;
}

void Board::setdissAllowedCastles(const std::string &dissAllowedCastles){
    this->dissAllowedCastles = dissAllowedCastles;
}

std::string Board::getdissAllowedCastles(){
    return dissAllowedCastles;
}

void Board::setAllowedCastles(const std::string &allowedCastles){
    this->allowedCastles = allowedCastles;
}

std::string Board::getAllowedCastles(){
    return allowedCastles;
}
// TODO move to utils later
bool squaresAreOnSameRow(int square1, int square2){
    return (square1 / 8) == (square2 / 8);
}


int Board::getPossibleEnPassantNextHalfMove(){
    return possibleEnPassantNextHalfMove;
}

std::unique_ptr<Board> Board::clone() const{
    return std::make_unique<Board> (*this);
}

int Board::getPossibleEnPassantNow(){
    return possibleEnPassantNow;
}


std::vector<int> Board::squareIsCompromised(const std::string &enemy, int position){

    std::vector<int> positionsOfAllCheckers;
    // std::cerr << enemy << move::inverseBoardMap.at(position) <<std::endl;;
    std::vector<std::string> horizontalPieces = enemy == "Black" ? (std::vector<std::string>){"q", "r"} : (std::vector<std::string>){"Q", "R"};
    std::vector<int> horizontalPiecesMoves = {-1 , -8, +1, +8};

    std::vector<std::string> diagonalPieces = enemy == "Black" ? (std::vector<std::string>){"q", "b"} : (std::vector<std::string>){"Q", "B"};
    std::vector<int> diagonalPiecesMoves = {-9, -7, 7, 9};

    std::vector<std::string> knight = enemy == "Black" ? (std::vector<std::string>){"n"} : (std::vector<std::string>){"N"};
    std::vector<int> knightMoves = {-17, -15, 7, 9, -6, 10, 17, 15, -10, 6};

    std::vector<std::string> king = enemy == "Black" ? (std::vector<std::string>){"k"} : (std::vector<std::string>){"K"};


    std::vector<std::string> pawn = enemy == "Black" ? (std::vector<std::string>){"p"} : (std::vector<std::string>){"P"};
    std::vector<int> pawnMoves = enemy == "Black" ? (std::vector<int>){-9, -7} : (std::vector<int>){7, 9};


    positionsOfAllCheckers = {};

    // TODO clean this up and put in a function + loop cause ewww
    auto foundCheckers = piecesCanCheck(position, 1, pawn, pawnMoves, *this, enemy);
    positionsOfAllCheckers.insert(positionsOfAllCheckers.end(),foundCheckers.begin(), foundCheckers.end());

    foundCheckers = piecesCanCheck(position, 8, horizontalPieces, horizontalPiecesMoves, *this, enemy);
    positionsOfAllCheckers.insert(positionsOfAllCheckers.end(),foundCheckers.begin(), foundCheckers.end());

    foundCheckers = piecesCanCheck(position, 8, diagonalPieces, diagonalPiecesMoves, *this, enemy);
    positionsOfAllCheckers.insert(positionsOfAllCheckers.end(),foundCheckers.begin(), foundCheckers.end());

    foundCheckers = piecesCanCheck(position, 1, knight, knightMoves, *this, enemy);
    positionsOfAllCheckers.insert(positionsOfAllCheckers.end(),foundCheckers.begin(), foundCheckers.end());

    // foundCheckers = piecesCanCheck(position, 1, king, horizontalPiecesMoves, *this, enemy);
    // positionsOfAllCheckers.insert(positionsOfAllCheckers.end(),foundCheckers.begin(), foundCheckers.end());

    // foundCheckers = piecesCanCheck(position, 1, king, diagonalPiecesMoves, *this, enemy);
    // positionsOfAllCheckers.insert(positionsOfAllCheckers.end(),foundCheckers.begin(), foundCheckers.end());
    


    return positionsOfAllCheckers;
}



void Board::applyCastle(const move &move){

    if (allowedCastles.find('K') != std::string::npos && move.to == move::boardMap.at("g1"))
        data[move::boardMap.at("f1")] = std::move(data[move::boardMap.at("h1")]);
    else if (allowedCastles.find('k') != std::string::npos && move.to == move::boardMap.at("g8"))
        data[move::boardMap.at("f8")] = std::move(data[move::boardMap.at("h8")]);
    else if (allowedCastles.find('Q') != std::string::npos && move.to == move::boardMap.at("c1"))
        data[move::boardMap.at("d1")] = std::move(data[move::boardMap.at("a1")]);
    else if (allowedCastles.find('q') != std::string::npos && move.to == move::boardMap.at("c8"))
        data[move::boardMap.at("d8")] = std::move(data[move::boardMap.at("a8")]);

    if (data[move.from]->getColor() == "White")
        dissAllowedCastles = "KQ";
    else
        dissAllowedCastles = "kq";
}

void removeCharFrom(char toRemove, std::string &string){
    std::cout << string << " " << toRemove << std::endl;
    string.erase(std::remove(string.begin(), string.end(), toRemove), string.end());
    std::cout << string << " " << toRemove << std::endl;

}



bool promotionAssertions(Board &board, move move){

    bool onFirstOrLastRank = board.getData()[move.from]->isOnRow(1, move.to) || board.getData()[move.from]->isOnRow(8, move.to);
    if (!onFirstOrLastRank){

        std::cout << move.from << "  " << move.to;

        return false;
    }

    std::cout << board.getData()[move.from]->getColor() << " " << move.promotion << "<---" << std::endl;
    if (board.getData()[move.from]->getColor() == "White"){
        if (move.promotion == '-')
            throw std::runtime_error("A pawn on the end of a board must provide the piece it wants to become.");
        if (move.promotion == std::tolower(move.promotion))
            throw std::runtime_error("You are trying to become a black piece for a white pawn promotion.");
    }
    if (board.getData()[move.from]->getColor() == "Black"){
        if (move.promotion == '-')
            throw std::runtime_error("A pawn on the end of a board must provide the piece it wants to become.");
        if (move.promotion == std::toupper(move.promotion))
            throw std::runtime_error("You are trying to become a black piece for a white pawn promotion.");
    }

    return true;
}



void Board::applyMoveSimulation(const move &move){
    if (data[move.from] == nullptr)
        throw std::runtime_error("The " + move::inverseBoardMap.at(move.from) + " 'From' square is empty");
    if (data[move.from]->getColor() != colorToMove)
        throw std::runtime_error("This is not the turn of the piece you are trying to move.");

////////// the thing to make sure of not doing each time
    // auto legalMoves = data[move.from]->getPseudoLegalMoves(*this, move.from);
    // auto legalMoves = getPieceLegalMove(move.from, gameState);

    // // gameState

    // for (auto &meow : legalMoves){
    //     std::cout << move::inverseBoardMap.at(move.from) << "-"<< move::inverseBoardMap.at(meow) << "<<<<<<<<<<<<<< " << std::endl;
    // }
    // auto legalMoves = getPieceLegalMove(move.from,);

    if (data[move.from]->getName() == "Pawn"){
        if (abs(move.from - move.to) == 16){
            if ((data[move.to - 1] != nullptr && squaresAreOnSameRow(move.to,move.to - 1) && data[move.to - 1]->getName() == "Pawn")){
                if (data[move.to - 1]->getColor() != data[move.from]->getColor())
                    possibleEnPassantNextHalfMove = data[move.from]->getColor() == "White" ?  move.to + 8 : move.to - 8;
            }
            if ((data[move.to + 1] != nullptr && squaresAreOnSameRow(move.to,move.to + 1) && data[move.to + 1]->getName() == "Pawn")){
                if (data[move.to + 1]->getColor() != data[move.from]->getColor())
                    possibleEnPassantNextHalfMove = data[move.from]->getColor() == "White" ?  move.to + 8 : move.to - 8;
            }
        }
    }

    // if (std::ranges::find(legalMoves, move.to) == legalMoves.end()){

    //     throw std::runtime_error("The move : " + move::inverseBoardMap.at(move.to) + " illegal ! you are going to jail.");
    //     exit(42);
    // }

    if (move.to == possibleEnPassantNow && data[move.from]->getName() == "Pawn"){
        data[move.from]->getColor() == "White" ? data[move.to + 8].reset() : data[move.to - 8].reset();
        possibleEnPassantNextHalfMove = 0;
        possibleEnPassantNow = 0;
    }

    if (data[move.from]->getName() == "King")
        applyCastle(move);
    if (data[move.from]->getName() == "Rook"){
        if (allowedCastles != "-"){
            if (data[move.from]->getColor() == "White"){
                if (move.from > whiteKingPosition)
                    dissAllowedCastles+="K";
                else
                    dissAllowedCastles+="Q";

            }else{
                if (move.from  > blackKingPosition)
                   dissAllowedCastles+="k";
                else
                    dissAllowedCastles+="q";
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
        if (colorToMove == "White")
            whiteKingPosition = move.to;
        else
            blackKingPosition = move.to;
    }

}

void Board::applyMove(const move &move, GameState &gameState){
    if (data[move.from] == nullptr)
        throw std::runtime_error("The " + move::inverseBoardMap.at(move.from) + " 'From' square is empty");
    if (data[move.from]->getColor() != colorToMove)
        throw std::runtime_error("This is not the turn of the piece you are trying to move.");

    


//////// the thing to make sure of not doing each time
    auto legalMoves = data[move.from]->getPseudoLegalMoves(*this, move.from);
    // auto legalMoves = getPieceLegalMove(move.from, gameState);

    // gameState

    std::cout << move::inverseBoardMap.at(move.from) << " hum " << legalMoves.size() << std::endl;

    for (auto &meow : legalMoves){
        std::cout << move::inverseBoardMap.at(move.from) << "-"<< move::inverseBoardMap.at(meow) << "<<<<<<<<<<<<<< " << std::endl;
    }
    // auto legalMoves = getPieceLegalMove(move.from,);

    if (data[move.from]->getName() == "Pawn"){
        if (abs(move.from - move.to) == 16){
            if ((data[move.to - 1] != nullptr && squaresAreOnSameRow(move.to,move.to - 1) && data[move.to - 1]->getName() == "Pawn")){
                if (data[move.to - 1]->getColor() != data[move.from]->getColor())
                    possibleEnPassantNextHalfMove = data[move.from]->getColor() == "White" ?  move.to + 8 : move.to - 8;
            }
            if ((data[move.to + 1] != nullptr && squaresAreOnSameRow(move.to,move.to + 1) && data[move.to + 1]->getName() == "Pawn")){
                if (data[move.to + 1]->getColor() != data[move.from]->getColor())
                    possibleEnPassantNextHalfMove = data[move.from]->getColor() == "White" ?  move.to + 8 : move.to - 8;
            }
        }
    }

    if (std::ranges::find(legalMoves, move.to) == legalMoves.end()){

        throw std::runtime_error("The move : " + move::inverseBoardMap.at(move.to) + " illegal ! you are going to jail.");
        exit(42);
    }

    if (move.to == possibleEnPassantNow && data[move.from]->getName() == "Pawn"){
        data[move.from]->getColor() == "White" ? data[move.to + 8].reset() : data[move.to - 8].reset();
        possibleEnPassantNextHalfMove = 0;
        possibleEnPassantNow = 0;
    }

    if (data[move.from]->getName() == "King")
        applyCastle(move);
    if (data[move.from]->getName() == "Rook"){
        if (allowedCastles != "-"){
            if (data[move.from]->getColor() == "White"){
                if (move.from > whiteKingPosition)
                    dissAllowedCastles+="K";
                else
                    dissAllowedCastles+="Q";

            }else{
                if (move.from  > blackKingPosition)
                   dissAllowedCastles+="k";
                else
                    dissAllowedCastles+="q";
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
        if (colorToMove == "White")
            whiteKingPosition = move.to;
        else
            blackKingPosition = move.to;
    }

}

std::vector<int> Board::kingIsInCheck(const std::string &color){

    // std::cout << "---->white king : "<< whiteKingPosition <<"<-----" << std::endl;
    // std::cout << "---->black king : "<< blackKingPosition <<"<-----" << std::endl;

    if (color == "White"){
        // std::cout << "Checking : white " << std::endl;
        return squareIsCompromised("Black", whiteKingPosition);
    }
    else{
        // std::cout << "Checking : black " << std::endl;

        return squareIsCompromised("White", blackKingPosition);
    }

}

bool Board::moreThan1PieceCanCheck(const std::string &color){

    if (color == "White"){
        // for (auto meow : squareIsCompromised("Black", whiteKingPosition))
        //     std::cout << "---->> "<< move::inverseBoardMap.at(meow) << std::endl;
        return squareIsCompromised("Black", whiteKingPosition).size() > 1;
    }
    else
        return squareIsCompromised("White", blackKingPosition).size() > 1;
    // for (auto waw : positionsOfAllCheckers){
    //     std::cout << move::inverseBoardMap.at(waw) << " aoeeee " << std::endl;
    // }
    // if (positionsOfAllCheckers.size() > 0)
    //     std::cout << " lafin " << std::endl;

    // return positionsOfAllCheckers.size() > 1;
}


bool Board::checkIngPieceCanBeCaptured(const std::string &color, int positionOfChecker){

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

bool diagonalInterpositionCheck(Board& board, int pieceA, int pieceB, const std::string& interposeColor){
    
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
        if (board.squareIsCompromised(interposeColor, i).size() > 0){
            // std::cout << "double Z" << std::endl;

            // for (auto meow : board.squareIsCompromised(interposeColor, i))
            //     std::cout <<move::inverseBoardMap.at(meow) << "\n";

            return true;
        }
    std::cout << "D" << std::endl;
    
    return false;
}

bool orthogonalInterpositionCheck(Board& board, int pieceA, int pieceB, const std::string& interposeColor){
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
        if (board.squareIsCompromised(interposeColor, i).size() > 0){
            // for (auto meow : board.squareIsCompromised(interposeColor, i))
            //     std::cout <<move::inverseBoardMap.at(meow) << "\n";
            return true;
        }

    }

    return false;
}

bool Board::pieceCanInterpose(int pieceA, int pieceB, const std::string &pieceName, const std::string& interposeColor){
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


bool Board::checkMateSituation(const std::string &color){
    std::string enemy = (color == "White" ? "Black" : "White");
    int kingPosition = (color == "White" ? whiteKingPosition : blackKingPosition);


    // std::cout << "I AM " << color << " ENEMY IS ////////// " << enemy << std::endl;
    // std::cout << "euuhhh salut -1" << std::endl;

    std::vector<int> kingCheckers = kingIsInCheck(color);
    if (kingCheckers.size() == 0)
        return false;
    // std::cout << "oh no.." << std::endl;
    // std::cout << "euuhhh salut 0" << std::endl;

    if (data[kingPosition]->getPseudoLegalMoves(*this, kingPosition).size() > 0)
        return false;
    
    // std::cout << "euuhhh salut 1" << color << std::endl;

    if (moreThan1PieceCanCheck(color))
        return true;

    // std::cout << "euuhhh salut 2" << std::endl;

    if (checkIngPieceCanBeCaptured(enemy, kingCheckers[0]))
        return false;
    // std::cout << "euuhhh salut 3" << std::endl;

    if (pieceCanInterpose(kingPosition, kingCheckers[0], data[kingCheckers[0]]->getName(), color))
        return false;

    // std::cout << "euuhhh salut 4" << std::endl;
    // std::cout << move::inverseBoardMap.at(blackKingPosition) << " <- b -- w -> " << move::inverseBoardMap.at(whiteKingPosition)<< std::endl;

    return true;
}

bool Board::staleMate(const std::string &color, GameState &gameState){
    std::vector<int> kingCheckers = kingIsInCheck(color);
    if (kingCheckers.size() > 0)
        return false;
    for (int i = 0; i < 64 ; i++){
        if (data[i] == nullptr || data[i]->getColor() != color)
            continue;
        if (getPieceLegalMove(i, gameState).size() > 0)
            return false;
    }

    return true;
}


void Board::printASCII(GameState &gameState){
    int counter = 0;
    for (auto &square : data){

        if ((counter == whiteKingPosition || counter == blackKingPosition) && (data[counter]->getColor() == colorToMove)){
            // if (staleMate(colorToMove, gameState))
            //     std::cout << PINK ;
            // else if (checkMateSituation(colorToMove))
            //     std::cout << RED;
            // else if (kingIsInCheck(colorToMove).size() > 0)
            //     std::cout << ORANGE;

            // std::cout << "\n" << std::endl;
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


void Board::printASCII(const std::vector<int> &moves){
{
        unsigned counter = 0;
        for (auto &square : data){
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

void Board::setWhiteKingPosition(int position){
    whiteKingPosition = position;
}
void Board::setBlackKingPosition(int position){
    blackKingPosition = position;
}

void Board::setPossibleEnPassantNow(int enPassantSquare){
    possibleEnPassantNow = enPassantSquare;
}


int Board::getWhiteKingPosition(){
    return whiteKingPosition;
}
int Board::getBlackKingPosition(){
    return blackKingPosition;
}