#include "piece.h"

Piece::Piece(char color, std::string placement, Board& board)
{
    pieceColor = color;
    if(color == 'w'){
        opponentColor = 'b';
    } else {
        opponentColor = 'w';
    }
    board->pieceAt(placement) = this;
    playingBoard = board;
    position = placement;
    homePosition = placement;
}

Pawn::Pawn(char color, std::string placement, Board& board) : Piece(color, placement, board)
{
    name = "Pawn";
    if(color == 'w'){
        abbreviation = 'P';
        movingDirection = 1;
    } else {
        abbreviation = 'p';
        movingDirection = -1;
    }
}

std::vector<std::string> Pawn::getPossibleMoves()
{
    std::vector<std::string> possibleMoves;
    std::string candidateMove;

    candidateMove = playingBoard->getDestination(position, movingDirection, 0);
    if(candidateMove != "-"){
        if(playingBoard->pieceAt(candidateMove)->getName() == "Vacant"){
            possibleMoves.push_back(candidateMove);
            if(position == homePosition){
                candidateMove = playingBoard->getDestination(position, 2 * movingDirection, 0);
                if(playingBoard->pieceAt(candidateMove)->getName() == "Vacant"){
                    possibleMoves.push_back(candidateMove);
                }
            }
        }
    }

    for(int i = 0; i < 2; i++){
        candidateMove = playingBoard->getDestination(position, movingDirection, 2 * i - 1);
        if(candidateMove != "-"){
            if(playingBoard->getPieceColorAt(candidateMove) == opponentColor){
                possibleMoves.push_back(candidateMove);
            }
        }
    }

    return possibleMoves;
}

std::vector<std::string> Pawn::getAttackingSquares()
{
    std::string candidateSquare;
    std::vector<std::string> attackingSquares;
    for(int i = 0; i < 2; i++){
        candidateSquare = playingBoard->getDestination(position, movingDirection, 2 * i - 1);
        if(candidateSquare != "-"){
            attackingSquares.push_back(candidateSquare);
        }
    }
    return attackingSquares;
}

Knight::Knight(char color, std::string placement, Board& board) : Piece(color, placement, board)
{
    name = "Knight";
    if(color == 'w'){
        abbreviation = 'N';
    } else {
        abbreviation = 'n';
    }
}

std::vector<std::string> Knight::getPossibleMoves()
{
    static const int direction[8][2] = {
        {-1, 2}, {1, 2},  // front (from white's perspective)
        {2, 1}, {2, -1},  // right
        {-1, -2}, {1, -2},  // back
        {-2, 1}, {-2, -1}  // left
    };
    std::vector<std::string> possibleMoves;
    std::string candidate;

    for(int i = 0; i < 8; i++){
        candidate = playingBoard->getDestination(position, direction[i][0], direction[i][1]);
        if(candidate == "-") continue;
        if(playingBoard->getPieceColorAt(candidate) != pieceColor) possibleMoves.push_back(candidate);
    }

    return possibleMoves;
}

Bishop::Bishop(char color, std::string placement, Board& board) : Piece(color, placement, board)
{
    name = "Bishop";
    if(color == 'w'){
        abbreviation = 'B';
    } else {
        abbreviation = 'b';
    }
}

std::vector<std::string> Bishop::getPossibleMoves()
{
    std::vector<std::string> possibleMoves;
    std::string candidate;
    std::string color;
    static const int direction[4][2] = {
        {-1, 1}, {1, 1},
        {-1, -1}, {1, -1}
    };

    for(int i = 0; i < 4; i++){
        candidate = position;
        while(true){
            candidate = playingBoard->getDestination(candidate, direction[i][0], direction[i][1]);
            if(candidate == "-") break;
            color = playingBoard->getPieceColorAt(candidate);
            if(color == pieceColor){
                break;
            } else if(color == opponentColor){
                possibleMoves.push_back(candidate);
                break;
            } else {
                possibleMoves.push_back(candidate);
            }
        }
    }

    return possibleMoves;
}

Rook::Rook(char color, std::string placement, Board& board) : Piece(color, placement, board)
{
    name = "Rook";
    if(color == 'w'){
        abbreviation = 'R';
    } else {
        abbreviation = 'r';
    }
}

std::vector<std::string> Rook::getPossibleMoves()
{
    std::vector<std::string> possibleMoves;
    std::string candidate;
    std::string color;
    static const int direction[4][2] = {
                {0, 1},
        {-1, 0},       {1, 0},
                {0, -1}
    };

    for(int i = 0; i < 4; i++){
        candidate = position;
        while(true){
            candidate = playingBoard->getDestination(candidate, direction[i][0], direction[i][1]);
            if(candidate == "-") break;
            color = playingBoard->getPieceColorAt(candidate);
            if(color == pieceColor){
                break;
            } else if(color == opponentColor){
                possibleMoves.push_back(candidate);
                break;
            } else {
                possibleMoves.push_back(candidate);
            }
        }
    }

    return possibleMoves;
}

Queen::Queen(char color, std::string placement, Board& board) : Piece(color, placement, board)
{
    name = "Queen";
    if(color == 'w'){
        abbreviation = 'Q';
    } else {
        abbreviation = 'q';
    }
}

std::vector<std::string> Queen::getPossibleMoves()
{
    std::vector<std::string> possibleMoves;
    std::string candidate;
    std::string color;
    static const int direction[8][2] = {
        {-1, 1}, {0, 1}, {1, 1},
        {-1, 0},         {1, 0},
        {-1, -1}, {0, -1}, {1, -1}
    };

    for(int i = 0; i < 8; i++){
        candidate = position;
        while(true){
            candidate = playingBoard->getDestination(candidate, direction[i][0], direction[i][1]);
            if(candidate == "-") break;
            color = playingBoard->getPieceColorAt(candidate);
            if(color == pieceColor){
                break;
            } else if(color == opponentColor){
                possibleMoves.push_back(candidate);
                break;
            } else {
                possibleMoves.push_back(candidate);
            }
        }
    }

    return possibleMoves;
}

King::King(char color, std::string placement, Board& board) : Piece(color, placement, board)
{
    name = "King";
    if(color == 'w'){
        abbreviation = 'K';
    } else {
        abbreviation = 'k';
    }
}

std::vector<std::string> King::getPossibleMoves()
{
    std::vector<std::string> possibleMoves;

    possibleMoves = getAttackingSquares();

    return possibleMoves;
}

std::vector<std::string> King::getAttackingSquares()
{
    std::vector<std::string> attackingSquares;
    std::string candidate;
    std::string color;
    static const int direction[8][2] = {
        {-1, 1}, {0, 1}, {1, 1},
        {-1, 0},         {1, 0},
        {-1, -1}, {0, -1}, {1, -1}
    };

    for(int i = 0; i < 8; i++){
        candidate = playingBoard->getDestination(candidate, direction[i][0], direction[i][1]);
        if(candidate == "-") continue;
        color = playingBoard->getPieceColorAt(candidate);
        if(color == pieceColor){
            continue;
        } else {
            attackingSquares.push_back(candidate);
        }
    }

    return attackingSquares;
}

Vacant::Vacant(std::string placement, Board& board) : Piece('-', placement, board)
{
    name = "Vacant";
    abbreviation = '-';
}

std::vector<std::string> getPossibleMoves()
{
    std::vector<std::string> possibleMoves;
    return possibleMoves;
}

Piece abbr2piece(char abbreviation, std::string placement, Board& board)
{
    char abbr = '-';
    char color;
    if('A' < abbreviation && abbreviation < 'Z'){
        abbr = std::tolower(abbreviation, std::locale());
        color = 'w';
    } else if('a' < piece && piece < 'z'){
        abbr = abbreviation;
        color = 'b';
    }
    switch(abbr){
        case 'p':
            return Pawn(color, placement, board);
        case 'n':
            return Knight(color, placement, board);
        case 'b':
            return Bishop(color, placement, board);
        case 'r':
            return Rook(color, placement, board);
        case 'q':
            return Queen(color, placement, board);
        case 'k':
            return King(color, placement, board);
        default:
            return Vacant(placement, board);
    }
}