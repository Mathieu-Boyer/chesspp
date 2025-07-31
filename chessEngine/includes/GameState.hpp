#pragma once
#include "Board.hpp"
#include "move.hpp"
#include "colors.hpp"
#include "utils.hpp"
#include <vector>
#include <string>
#include <memory>
#include <algorithm>

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
    std::vector<std::string> data;
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

    bool moreThan1PieceCanCheck(const std::string &color);
    bool checkIngPieceCanBeCaptured(const std::string &color, int checkerPos);
    bool pieceCanInterpose(int pieceA, int pieceB, const std::string &pieceName, const std::string& interposeColor);

public:


    GameState() = delete;
    GameState(const std::string &fen);
    GameState(const GameState& gameState);
    ~GameState() = default;

    void applyMove(const move &move);

    void applyMoveSimulation(const move& move);

    std::string getColorToMove();
    std::vector<int> getPieceLegalMove(int position);
    std::vector<int> squareIsCompromised(const std::string &enemy, int target);

    int isDraw();
    bool staleMate();
    int checkGameStatus();
    bool checkMateSituation(const std::string &color);
    std::vector<int> kingIsInCheck(const std::string &color);

    void printASCII();
    void printASCII(const std::vector<int> &moves);
    std::string encode();
    
    Board& getRefToBoard() const;
    
    int getCurrentHalfMove();
    int getCurrentFullMove();
    int getPossibleEnPassantNow();
    std::string getWhiteQueenInfo();
    std::string getLastMovedPiece();
    std::string getBlackQueenInfo();
    std::string getAllowedCastles();
    std::string getMoveConstruction();
    std::string getdissAllowedCastles();
    int getPossibleEnPassantNextHalfMove();

    void setCurrentFullMove(int value);
    void setCurrentHalfMove(int value);
    void setPossibleEnPassantNow(int value);
    void setWhiteQueenInfo(std::string value);
    void setLastMovedPiece(std::string value);
    void setBlackQueenInfo(std::string value);
    void setMoveConstruction(std::string value);
    void setColorToMove(const std::string &color);
    void setPossibleEnPassantNextHalfMove(int value);
    void setAllowedCastles(const std::string &allowedCastles);
    void setdissAllowedCastles(const std::string &dissAllowedCastles);
};