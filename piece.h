#ifndef PIECE_H
#define PIECE_H

#include <locale>
#include <string>
#include <vector>
#include "board.h"

class Piece
{
public:
    Piece(char color, std::string placement, Board& board);
    std::string getName() { return name; }
    char getAbbreviation() { return abbreviation; }
    char getColor() { return pieceColor; }

protected:
    std::string name;
    char abbreviation;
    char pieceColor;
    char opponentColor;
    Board playingBoard;
    std::string position;
    std::string const homePosition;
};

class Pawn : public Piece
{
public:
    Pawn(char color, std::string placement, Board& board) : Piece(color, placement, board);
    std::vector<std::string> getPossibleMoves();
    std::vector<std::string> getAttackingSquares();
    bool moveTo(std::string destination);

protected:
    int movingDirection;
};

class Knight : public Piece
{
    Knight(char color, std::string placement, Board& board) : Piece(color, placement, board);
    std::vector<std::string> getPossibleMoves();
    std::vector<std::string> getAttackingSquares() { return getPossibleMoves() };
    bool moveTo(std::string destination);
};

class Bishop : public Piece
{
    Bishop(char color, std::string placement, Board& board) : Piece(color, placement, board);
    std::vector<std::string> getPossibleMoves();
    std::vector<std::string> getAttackingSquares() { return getPossibleMoves() };
    bool moveTo(std::string destination);
};

class Rook : public Piece
{
    Rook(char color, std::string placement, Board& board) : Piece(color, placement, board);
    std::vector<std::string> getPossibleMoves();
    std::vector<std::string> getAttackingSquares() { return getPossibleMoves() };
    bool moveTo(std::string destination);
};

class Queen : public Piece
{
    Queen(char color, std::string placement, Board& board) : Piece(color, placement, board);
    std::vector<std::string> getPossibleMoves();
    std::vector<std::string> getAttackingSquares() { return getPossibleMoves() };
    bool moveTo(std::string destination);
};

class King : public Piece
{
    King(char color, std::string placement, Board& board) : Piece(color, placement, board);
    std::vector<std::string> getPossibleMoves();
    std::vector<std::string> getAttackingSquares();
    bool moveTo(std::string destination);
};

class Vacant : public Piece
{
    Vacant(std::string placement, Board& board) : Piece('-', placement, board);
    std::vector<std::string> getPossibleMoves();
    std::vector<std::string> getAttackingSquares() { return getPossibleMoves() };
    bool moveTo(std::string destination);
}

Piece abbr2piece(char abbreviation, std::string placement, Board& board);
