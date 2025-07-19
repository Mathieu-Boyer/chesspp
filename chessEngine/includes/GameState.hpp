#pragma once
#include "Board.hpp"
#include "utils.hpp"
#include <vector>
#include <string>
#include <memory>


class GameState
{
private:
    std::string raw;
    std::vector<std::string> data; // i use a vector instead of fixed sized array here because i'll add rules later so i might need to store more infos.
    // when i will be sure of all the infos i need i'll make it fixed size.
    std::unique_ptr<Board> board;
    std::string colorToMove;
    void decode();

public:
    GameState() = delete;
    GameState(const std::string &fen);
    GameState(const GameState& gameState);
    ~GameState() = default;
    
    std::string getColorToMove();

    std::string encode();
    Board& getRefToBoard() const;
    
};