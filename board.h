#ifndef BOARD_H
#define BOARD_H

#include <map>
#include <string>
#include <vector>
#include "piece.h"

class Board
{
public:
    Board();
    void FEN2Board();
    void board2FEN();
    void setPieceAt(Piece* piece, std::string notation);
    void setPieceAt(Piece* piece, int i, int j) { setPieceAt(piece, getNotation(i, j)); }
    Piece* getPieceAt(std::string notation) { return piecePlacement[notation]; }
    Piece* getPieceAt(int i, int j) { return piecePlacement[getNotation(i, j)]; }
    char getPieceCharAt(std::string notation) { return getPieceAt(notation)->abbreviation; }
    char getPieceCharAt(int i, int j) { return getPieceAt(i, j)->abbreviation; }
    std::vector<int> getIndices(std::string notation);
    std::string getNotation(int i, int j);
    char getPieceColorAt(std::string notation);
    char getPieceColorAt(int i, int j);
    bool move(std::string origin, std::string destination);
    std::string getDestination(std::string origin, int fileDirection, int rankDirection);
    std::vector<std::string> getAttackingSquares(char color);
    std::string getFEN() { return fen; }
    char getActiveColor() { return activeColor; }
    std::string getCastlability() { return castlability; }
    int getHalfmoveClock() { return halfmoveClock; }
    int getFullmoveNumber() { return fullmoveNumber; }
    std::string enPassantTarget;
    std::string castlability;
    int halfmoveClock;
    int fullmoveNumber;
    void changeActiveColor();
    void print();
    static const int Length = 8;

private:
    std::string fen;
    char activeColor;
    std::map<std::string, Piece*> piecePlacement;
};

#endif
