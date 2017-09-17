#include <algorithm>
#include <cassert>
#include <complex>
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

    activeColor = fenBlocks[1][0];
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

    fen += " ";
    fen += activeColor;
    fen += " " + castlability;
    fen += " " + enPassantTarget;
    fen += " " + std::to_string(halfmoveClock);
    fen += " " + std::to_string(fullmoveNumber);
}

char& Board::pieceAt(std::string notation)
{
    std::vector<int> indices = getIndices(notation);
    return pieceAt(indices[0], indices[1]);
}

std::vector<int> Board::getIndices(std::string notation)
{
    assert(notation.size() == 2);
    assert('a' <= notation[0] && notation[0] <= 'h');
    assert('1' <= notation[1] && notation[1] <= '8');
    std::vector<int> indices;
    indices.push_back(7 - (notation[1] - '1'));
    indices.push_back(notation[0] - 'a');
    return indices;
}

std::string Board::getNotation(int i, int j)
{
    assert(0 <= i && i < Length);
    assert(0 <= j && j < Length);
    char file = 'a';
    char rank = '1';
    std::string notation;
    file += j;
    rank += Length - 1 - i;
    notation += file;
    notation += rank;
    return notation;
}

char Board::getPieceColor(char piece)
{
    if('A' < piece && piece < 'Z'){
        return 'w';
    } else if('a' < piece && piece < 'z'){
        return 'b';
    } else {
        return '-';
    }
}

char Board::getPieceColorAt(std::string notation)
{
    return getPieceColor(pieceAt(notation));
}

char Board::getPieceColorAt(int i, int j)
{
    return getPieceColor(pieceAt(i, j));
}

bool Board::move(std::string origin, std::string destination)
{
    char movingColor = getPieceColorAt(origin);
    if(movingColor != activeColor) return false;
    std::vector<std::string> moves = getPossibleMovesAt(origin);
    if(std::find(moves.begin(), moves.end(), destination) == moves.end())
        return false;
    bool captured = (pieceAt(destination) != '-');
    pieceAt(destination) = pieceAt(origin);
    pieceAt(origin) = '-';

    changeActiveColor();
    updateCastlability(origin, destination);
    updateEnPassantTarget(origin, destination);

    // update halfmove clock
    if(captured || pieceAt(destination) == 'p' || pieceAt(destination) == 'P'){
        halfmoveClock = 0;
    } else {
        halfmoveClock += 1;
    }

    // increase fullmove number
    if(movingColor == 'b'){
        fullmoveNumber += 1;
    }
    board2FEN();
    return true;
}

std::string Board::getDestination(std::string origin, int fileDirection, int rankDirection)
{
    char originFile = origin[0];
    char originRank = origin[1];
    std::string destination;
    char destinationFile = originFile + fileDirection;
    char destinationRank = originRank + rankDirection;

    if('a' <= destinationFile && destinationFile <= 'h'
    && '1' <= destinationRank && destinationRank <= '8'){
        destination += destinationFile;
        destination += destinationRank;
    } else {
        destination = "-";
    }
    return destination;
}

std::vector<std::string> Board::getAttackingSquaresAt(std::string notation)
{
    char piece = pieceAt(notation);
    std::vector<std::string> possibleMoves;
    piece = std::tolower(piece, std::locale());
    switch(piece){
        case 'p':
            return getPawnAttackingSquares(notation);
        case 'n':
            return getKnightAttackingSquares(notation);
        case 'b':
            return getBishopAttackingSquares(notation);
        case 'r':
            return getRookAttackingSquares(notation);
        case 'q':
            return getQueenAttackingSquares(notation);
        case 'k':
            return getKingAttackingSquares(notation);
        default:
            return possibleMoves;
    }
}

std::vector<std::string> Board::getPossibleMovesAt(std::string notation)
{
    char piece = pieceAt(notation);
    std::vector<std::string> possibleMoves;
    piece = std::tolower(piece, std::locale());
    switch(piece){
        case 'p':
            return getPawnPossibleMoves(notation);
        case 'n':
            return getKnightPossibleMoves(notation);
        case 'b':
            return getBishopPossibleMoves(notation);
        case 'r':
            return getRookPossibleMoves(notation);
        case 'q':
            return getQueenPossibleMoves(notation);
        case 'k':
            return getKingPossibleMoves(notation);
        default:
            return possibleMoves;
    }
}

std::vector<std::string> Board::getPawnAttackingSquares(std::string notation)
{
    std::vector<std::string> attackingSquares;
    std::string candidate;
    int direction;
    if(getPieceColorAt(notation) == 'w'){
        direction = 1;
    } else {
        direction = -1;
    }

    for(int i = 0; i < 2; i++){
        candidate = getDestination(notation, 2 * i - 1, direction);
        if(candidate == "-") continue;
        if(getPieceColorAt(candidate) != getPieceColorAt(notation))
            attackingSquares.push_back(candidate);
    }

    return attackingSquares;
}

std::vector<std::string> Board::getPawnPossibleMoves(std::string notation)
{
    std::vector<std::string> possibleMoves;
    std::string candidate;
    int direction;
    char opponentColor, homeRank;
    if(getPieceColorAt(notation) == 'w'){
        direction = 1;
        opponentColor = 'b';
        homeRank = '2';
    } else {
        direction = -1;
        opponentColor = 'w';
        homeRank = '7';
    }

    candidate = getDestination(notation, 0, direction);
    if(candidate != "-"){
        if(pieceAt(candidate) == '-'){
            possibleMoves.push_back(candidate);
            if(notation[1] == homeRank){
                candidate = getDestination(notation, 0, 2 * direction);
                if(pieceAt(candidate) == '-')
                    possibleMoves.push_back(candidate);
            }
        }
    }

    for(int i = 0; i < 2; i++){
        candidate = getDestination(notation, 2 * i - 1, direction);
        if(candidate == "-") continue;
        if(getPieceColorAt(candidate) == opponentColor)
            possibleMoves.push_back(candidate);
    }

    return possibleMoves;
}

std::vector<std::string> Board::getKnightAttackingSquares(std::string notation)
{
    std::vector<std::string> possibleMoves;
    std::string candidate;
    static const int direction[8][2] = {
        {-1, 2}, {1, 2},  // front (from white's perspective)
        {2, 1}, {2, -1},  // right
        {-1, -2}, {1, -2},  // back
        {-2, 1}, {-2, -1}  // left
    };

    for(int i = 0; i < 8; i++){
        candidate = getDestination(notation, direction[i][0], direction[i][1]);
        if(candidate == "-") continue;
        if(getPieceColorAt(candidate) != getPieceColorAt(notation))
            possibleMoves.push_back(candidate);
    }

    return possibleMoves;
}

std::vector<std::string> Board::getKnightPossibleMoves(std::string notation)
{
    return getKnightAttackingSquares(notation);
}

std::vector<std::string> Board::getBishopAttackingSquares(std::string notation)
{
    std::vector<std::string> attackingSquares;
    std::string candidate;
    static const int direction[4][2] = {
        {-1, 1}, {1, 1},
        {-1, -1}, {1, -1}
    };
    char pieceColor = getPieceColorAt(notation);
    char opponentColor, targetColor;
    if(pieceColor == 'w'){
        opponentColor = 'b';
    } else {
        opponentColor = 'w';
    }

    for(int i = 0; i < 4; i++){
        candidate = notation;
        while(true){
            candidate = getDestination(candidate, direction[i][0], direction[i][1]);
            if(candidate == "-") break;
            targetColor = getPieceColorAt(candidate);
            if(targetColor == pieceColor){
                break;
            } else if(targetColor == opponentColor){
                attackingSquares.push_back(candidate);
                break;
            } else {
                attackingSquares.push_back(candidate);
            }
        }
    }

    return attackingSquares;
}

std::vector<std::string> Board::getBishopPossibleMoves(std::string notation)
{
    return getBishopAttackingSquares(notation);
}

std::vector<std::string> Board::getRookAttackingSquares(std::string notation)
{
    std::vector<std::string> attackingSquares;
    std::string candidate;
    static const int direction[4][2] = {
            {0, 1},
        {-1, 0}, {1, 0},
            {0, -1}
    };
    char pieceColor = getPieceColorAt(notation);
    char opponentColor, targetColor;
    if(pieceColor =='w'){
        opponentColor = 'b';
    } else {
        opponentColor = 'w';
    }

    for(int i = 0; i < 4; i++){
        candidate = notation;
        while(true){
            candidate = getDestination(candidate, direction[i][0], direction[i][1]);
            if(candidate == "-") break;
            targetColor = getPieceColorAt(candidate);
            if(targetColor == pieceColor){
                break;
            } else if(targetColor == opponentColor){
                attackingSquares.push_back(candidate);
                break;
            } else {
                attackingSquares.push_back(candidate);
            }
        }
    }

    return attackingSquares;
}

std::vector<std::string> Board::getRookPossibleMoves(std::string notation)
{
    return getRookAttackingSquares(notation);
}

std::vector<std::string> Board::getQueenAttackingSquares(std::string notation)
{
    std::vector<std::string> attackingSquares = getBishopAttackingSquares(notation);
    std::vector<std::string> tmp = getRookAttackingSquares(notation);
    attackingSquares.insert(attackingSquares.end(), tmp.begin(), tmp.end());
    return attackingSquares;
}

std::vector<std::string> Board::getQueenPossibleMoves(std::string notation)
{
    return getQueenAttackingSquares(notation);
}

std::vector<std::string> Board::getKingAttackingSquares(std::string notation)
{
    std::vector<std::string> attackingSquares;
    std::string candidate;
    static const int direction[8][2] = {
        {-1, 1}, {0, 1}, {1, 1},
        {-1, 0},         {1, 0},
        {-1, -1}, {0, -1}, {1, -1}
    };
    char pieceColor = getPieceColorAt(notation);
    char opponentColor, targetColor;
    if(pieceColor =='w'){
        opponentColor = 'b';
    } else {
        opponentColor = 'w';
    }

    for(int i = 0; i < 8; i++){
        candidate = getDestination(notation, direction[i][0], direction[i][1]);
        if(candidate == "-") continue;
        targetColor = getPieceColorAt(candidate);
        if(targetColor == pieceColor){
            continue;
        } else {
            attackingSquares.push_back(candidate);
        }
    }

    return attackingSquares;
}

std::vector<std::string> Board::getKingPossibleMoves(std::string notation)
{
    return getKingAttackingSquares(notation);
}

void Board::print()
{
    char file = 'a';
    for(int i = 0; i < Length; i++){
        std::cout << 8 - i << ' ';
        for(int j = 0; j < Length; j++){
            std::cout << pieceAt(i, j) << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << "  ";
    for(int i = 0; i < Length; i++){
        std::cout << file << ' ';
        file += 1;
    }
    std::cout << std::endl << getFEN() << std::endl;
}

void Board::changeActiveColor()
{
    if(activeColor == 'w'){
        activeColor = 'b';
    } else {
        activeColor = 'w';
    }
}

void Board::updateCastlability(std::string origin, std::string destination)
{
    int pos;
    if(pieceAt(destination) == 'K'){
        pos = castlability.find('K');
        if(pos != -1) castlability.erase(pos, 1);
        pos = castlability.find('Q');
        if(pos != -1) castlability.erase(pos, 1);
    } else if(pieceAt(destination) == 'k'){
        pos = castlability.find('k');
        if(pos != -1) castlability.erase(pos, 1);
        pos = castlability.find('q');
        if(pos != -1) castlability.erase(pos, 1);
    } else if(origin == "a1"){
        pos = castlability.find('Q');
        if(pos != -1) castlability.erase(pos, 1);
    } else if(origin == "h1"){
        pos = castlability.find('K');
        if(pos != -1) castlability.erase(pos, 1);
    } else if(origin == "a8"){
        pos = castlability.find('q');
        if(pos != -1) castlability.erase(pos, 1);
    } else if(origin == "h8"){
        pos = castlability.find('k');
        if(pos != -1) castlability.erase(pos, 1);
    }
    if(castlability.empty()) castlability = "-";
}

void Board::updateEnPassantTarget(std::string origin, std::string destination)
{
    if(pieceAt(destination) == 'p' || pieceAt(destination) == 'P'){
        if(std::abs(origin[1] - destination[1]) > 1){
            enPassantTarget = origin[0];
            enPassantTarget += (origin[1] + destination[1]) / 2;
        } else {
            enPassantTarget = "-";
        }
    } else {
        enPassantTarget = "-";
    }
}

// int main()
// {
//     Board board = Board();
//     board.print();
//     board.move("e2", "e4");
//     board.print();
//     board.move("e7", "e6");
//     board.print();
// }
