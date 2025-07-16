#pragma once

#include <string>
#include <vector>
#include <ranges>

class APiece;

std::vector<std::string> split(std::string string, char delimiter);
std::unique_ptr<APiece> pieceFactory(char character);
std::string tolower(std::string string);
bool knightMoveOverFlow(int position, int move);