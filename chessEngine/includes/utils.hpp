#pragma once

#include <string>
#include <vector>
#include <ranges>

class APiece;
class Board;

std::vector<std::string> split(std::string string, char delimiter);
std::unique_ptr<APiece> pieceFactory(char character);
std::string tolower(std::string string);
bool knightMoveOverFlow(int position, int move);
bool diagonalMoveOverFlow(int position, int move);

bool pawnCheck(const std::string &representation, Board &board);
bool piecesCanCheck(int position, int maxRange, const std::vector<std::string> &slidePieces, std::vector<int> toCheck , Board &board);