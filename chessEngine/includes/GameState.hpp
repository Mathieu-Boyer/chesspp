#pragma once
#include "Board.hpp"
#include "move.hpp"
#include "colors.hpp"
#include "utils.hpp"
#include <vector>
#include <string>
#include <memory>



enum gameStatus{
    ongoing,
    check,
    checkmate,
    staleMate,
    halfMoveDraw
};

class GameState
{
private:
    std::string raw;
    std::vector<std::string> data; // i use a vector instead of fixed sized array here because i'll add rules later so i might need to store more infos.
    // when i will be sure of all the infos i need i'll make it fixed size.
    std::unique_ptr<Board> board;

    void decode();

    int currentHalfMove;
    int currentFullMove;

    std::string colorToMove;
    int possibleEnPassantNow;
    int possibleEnPassantNextHalfMove;
    std::string dissAllowedCastles;
    std::string allowedCastles;
    std::string moveConstruction;
    std::string whiteQueenInfos;
    std::string blackQueenInfos;
    std::string lastMovedPiece;

public:
    void applyMoveSimulation(const move& move);

    GameState() = delete;
    GameState(const std::string &fen);
    GameState(const GameState& gameState);
    ~GameState() = default;

    void applyMove(const move &move);


    std::vector<int> squareIsCompromised(const std::string &enemy, int target);
    std::vector<int> getPieceLegalMove(int position);
    std::string getColorToMove();

    bool pieceCanInterpose(int pieceA, int pieceB, const std::string &pieceName, const std::string& interposeColor);
    std::vector<int> kingIsInCheck(const std::string &color);
    bool moreThan1PieceCanCheck(const std::string &color);
    bool checkIngPieceCanBeCaptured(const std::string &color, int checkerPos);
    bool checkMateSituation(const std::string &color);
    bool staleMate();

    void printASCII();
    void printASCII(const std::vector<int> &moves);

    std::string encode();
    Board& getRefToBoard() const;


    void setColorToMove(const std::string &color);

    void setdissAllowedCastles(const std::string &dissAllowedCastles);
    std::string getdissAllowedCastles();

    void setAllowedCastles(const std::string &allowedCastles);

    std::string getAllowedCastles();

    int getPossibleEnPassantNextHalfMove();

    void setPossibleEnPassantNextHalfMove(int value);
    void setPossibleEnPassantNow(int value);

    int getPossibleEnPassantNow();


    void setCurrentHalfMove(int value);
    int getCurrentHalfMove();

    void setCurrentFullMove(int value);
    int getCurrentFullMove();

    int isDraw();
    int checkGameStatus();



    void setLastMovedPiece(std::string value);
    std::string getLastMovedPiece();

    void setMoveConstruction(std::string value);
    std::string getMoveConstruction();

    void setWhiteQueenInfo(std::string value);
    std::string getWhiteQueenInfo();

    void setBlackQueenInfo(std::string value);
    std::string getBlackQueenInfo();
};