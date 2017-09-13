#ifndef PIECE_H
#define PIECE_H

#include <locale>
#include <string>
#include "board.h"

class Piece
{
public:
    Piece(char color, std::string placement, Board& board);
    bool placeAt(std::string placement, Board& board);
    std::string getName() { return name; }
    char getAbbreviation() { return abbreviation; }
    char getColor() { return pieceColor; }

protected:
    std::string name;
    char abbreviation;
    char pieceColor;
    Board playingBoard;
    std::string position;
};

class Pawn : public Piece
{
public:
    Pawn(char color, std::string placement, Board& board) : Piece(color, placement, board);
};

class Knight : public Piece
{
    Knight(char color, std::string placement, Board& board) : Piece(color, placement, board);
};

class Bishop : public Piece
{
    Bishop(char color, std::string placement, Board& board) : Piece(color, placement, board);
};

class Rook : public Piece
{
    Rook(char color, std::string placement, Board& board) : Piece(color, placement, board);
};

class Queen : public Piece
{
    Queen(char color, std::string placement, Board& board) : Piece(color, placement, board);
};

class King : public Piece
{
    King(char color, std::string placement, Board& board) : Piece(color, placement, board);
};

class Vacant : public Piece
{
    Vacant(std::string placement, Board& board) : Piece('-', placement, board);
}

Piece abbr2piece(char abbreviation, std::string placement, Board& board);
