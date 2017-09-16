#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <vector>

class Board
{
public:
    Board();
    void FEN2Board();
    void board2FEN();
    char& pieceAt(std::string notation);
    char& pieceAt(int i, int j) { return piecePlacement[i][j]; }
    std::vector<int> getIndices(std::string notation);
    std::string getNotation(int i, int j);
    char getPieceColor(char piece);
    char getPieceColorAt(std::string notation);
    char getPieceColorAt(int i, int j);
    bool move(std::string origin, std::string destination);
    std::string getDestination(std::string origin, int fileDirection, int rankDirection);
    std::vector<std::string> getAttackingSquaresAt(std::string notation);
    std::vector<std::string> getPossibleMovesAt(std::string notation);
    std::vector<std::string> getPawnAttackingSquares(std::string notation);
    std::vector<std::string> getPawnPossibleMoves(std::string notation);
    std::vector<std::string> getKnightAttackingSquares(std::string notation);
    std::vector<std::string> getKnightPossibleMoves(std::string notation);
    std::vector<std::string> getBishopAttackingSquares(std::string notation);
    std::vector<std::string> getBishopPossibleMoves(std::string notation);
    std::vector<std::string> getRookAttackingSquares(std::string notation);
    std::vector<std::string> getRookPossibleMoves(std::string notation);
    std::vector<std::string> getQueenAttackingSquares(std::string notation);
    std::vector<std::string> getQueenPossibleMoves(std::string notation);
    std::vector<std::string> getKingAttackingSquares(std::string notation);
    std::vector<std::string> getKingPossibleMoves(std::string notation);
    std::string getFEN() { return fen; }
    char getActiveColor() { return activeColor; }
    std::string getCastlability() { return castlability; }
    std::string getEnPassantTarget() { return enPassantTarget; }
    int getHalfmoveClock() { return halfmoveClock; }
    int getFullmoveNumber() { return fullmoveNumber; }
    void print();
    static const int Length = 8;

private:
    std::string fen;
    char activeColor;
    std::string castlability;
    std::string enPassantTarget;
    int halfmoveClock;
    int fullmoveNumber;
    char piecePlacement[Length][Length];
    void changeActiveColor();
};

#endif
