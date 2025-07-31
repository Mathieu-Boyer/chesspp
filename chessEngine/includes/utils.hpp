#pragma once

#include <string>
#include <vector>
#include <ranges>
#include <memory>
#include <algorithm>
#include <memory>
#include "move.hpp"

class Board;
class APiece;
class GameState;

std::string tolower(std::string string);
bool knightMoveOverFlow(int position, int move);
bool diagonalMoveOverFlow(int position, int move);
std::unique_ptr<APiece> pieceFactory(char character);
std::vector<std::string> split(std::string string, char delimiter);

bool pawnCheck(const std::string &representation, Board &board);
bool enemyKingNearby(Board &board, int positionOfmyKing, const std::string& enemyColor, std::vector<int> toCheck);
std::vector<int> piecesCanCheck(int position, int maxRange, const std::vector<std::string> &slidePieces, std::vector<int> toCheck , Board &board,  const std::string& enemyColor);

bool validSquare(int square);
bool diagonalMove(int move);
bool horizontalMove(int move);
bool horizontalOverflow(int position, int square);

bool isEmptyZone(int from, int to, Board &board);
bool isCompromizedZone(int from, int to, GameState& gameState, const std::string& enemy);
std::string enemyOf(const std::string &color);

bool squaresAreOnSameRow(int square1, int square2);
bool promotionAssertions(Board &board, move move);
void removeCharFrom(char toRemove, std::string &string);

void playInTerminal();
void applyMoveAndGenerateNewFen(const std::string &rawMove, const std::string &currentFen);
void fetchLegalMoves(const std::string &rawMove, const std::string &currentFen);
void executeNeededFunctionalities(const std::string &rawMove, const std::string &currentFen);
