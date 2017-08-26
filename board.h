#ifndef BOARD_H
#define BOARD_H

enum chessPiece { p, n, b, r, q, k, P, N, B, R, Q, K, v };

class Board
{
public:
    Board() { LoadStartingPosition(); }
    void LoadStartingPosition();
    chessPiece& PieceAt(int x, int y) { return board[y][x]; }
    static const int Length = 8;

private:
    chessPiece board[Length][Length];
};

#endif
