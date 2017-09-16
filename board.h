#ifndef BOARD_H
#define BOARD_H

#include <string>

class Board
{
public:
    Board();
    void FEN2Board();
    void board2FEN();
    char& pieceAt(std::string notation);
    char& pieceAt(int i, int j) { return piecePlacement[i][j]; }
    std::string getPieceColor(char piece);
    std::string getPieceColorAt(std::string notation);
    std::string getPieceColorAt(int i, int j);
    bool move(std::string origin, std::string destination);
    std::string getDestination(std::string origin, int fileDirection, int rankDirection);
    std::string getFEN() { return fen; }
    std::string getActiveColor() { return activeColor; }
    std::string getCastlability() { return castlability; }
    std::string getEnPassantTarget() { return enPassantTarget; }
    int getHalfmoveClock() { return halfmoveClock; }
    int getFullmoveNumber() { return fullmoveNumber; }
    static const int Length = 8;


private:
    std::string fen;
    std::string activeColor;
    std::string castlability;
    std::string enPassantTarget;
    int halfmoveClock;
    int fullmoveNumber;
    char piecePlacement[Length][Length];
    void changeActiveColor();
};

#endif
