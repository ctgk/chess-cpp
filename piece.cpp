#include "piece.h"

Piece::Piece(char color, std::string placement, Board& board)
{
    pieceColor = color;
    assert(placeAt(placement, board));
}

bool Piece::placeAt(std::string placement, Board& board)
{
    if(board->pieceAt(placement)->getName() == "Vacant"){
        board->pieceAt(placement) = this;
        playingBoard = board;
        position = placement;
        return true;
    }
    return false;
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