#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "board.h"

std::vector<std::string> split(std::string str, char sep)
{
    std::vector<std::string> str_blocks;
    std::stringstream ss(str);
    std::string buffer;
    while(std::getline(ss, buffer, sep)){
        str_blocks.push_back(buffer);
    }
    return str_blocks;
}

Board::Board()
{
    fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    FEN2Board();
}

void Board::FEN2Board()
{
    std::vector<std::string> fenBlocks = split(fen, ' ');
    assert(fenBlocks.size() == 6);

    for(int i = 0; i < fenBlocks[0].size(); i++){
        if(std::isdigit(fenBlocks[0][i])){
            fenBlocks[0].replace(i, 1, std::string(fenBlocks[0][i] - '0', '-'));
        }
    }
    std::vector<std::string> placements = split(fenBlocks[0], '/');
    assert(placements.size() == 8);
    for(int i = 0; i < Length; i++){
        for(int j = 0; j < Length; j++){
            pieceAt(i, j) = placements[i][j];
        }
    }

    activeColor = fenBlocks[1];
    castlability = fenBlocks[2];
    enPassantTarget = fenBlocks[3];
    halfmoveClock = std::stoi(fenBlocks[4]);
    fullmoveNumber = std::stoi(fenBlocks[5]);
}

void Board::board2FEN()
{
    fen = "";
    int vacant;
    for(int i = 0; i < Length; i++){
        vacant = 0;
        for(int j = 0; j < Length; j++){
            if(pieceAt(i, j) == '-'){
                vacant += 1;
            } else {
                if(vacant != 0){
                    fen += vacant + '0';
                    vacant = 0;
                }
                fen += pieceAt(i, j);
            }
        }
        if(vacant != 0){
            fen += vacant + '0';
        }
        if(i != Length - 1){
            fen += '/';
        }
    }

    fen += " " + activeColor;
    fen += " " + castlability;
    fen += " " + enPassantTarget;
    fen += " " + std::to_string(halfmoveClock);
    fen += " " + std::to_string(fullmoveNumber);
}

char& Board::pieceAt(std::string notation)
{
    assert(notation.size() == 2);
    assert('a' <= notation[0] && notation[0] <= 'h');
    assert('1' <= notation[1] && notation[1] <= '8');
    return pieceAt(7 - (notation[1] - '1'), notation[0] - 'a');
}

std::string Board::getPieceColor(char piece)
{
    if('A' < piece && piece < 'Z'){
        return "w";
    } else if('a' < piece && piece < 'z'){
        return "b";
    } else {
        return "-";
    }
}

std::string Board::getPieceColorAt(std::string notation)
{
    return getPieceColor(pieceAt(notation));
}

std::string Board::getPieceColorAt(int i, int j)
{
    return getPieceColor(pieceAt(i, j));
}

bool Board::move(std::string origin, std::string destination)
{
    std::string movingColor = getPieceColorAt(origin);
    if(movingColor == activeColor){
        pieceAt(destination) = pieceAt(origin);
        pieceAt(origin) = '-';
        changeActiveColor();
        if(movingColor == "b"){
            fullmoveNumber += 1;
        }
        board2FEN();
        return true;
    }
    return false;
}

void Board::changeActiveColor()
{
    if(activeColor == "w"){
        activeColor = "b";
    } else {
        activeColor = "w";
    }
}

// int main()
// {
//     Board board = Board();
//     std::cout << board.getFEN() << std::endl;
//     board.move("e2", "e4");
//     std::cout << board.getFEN() << std::endl;
// }
