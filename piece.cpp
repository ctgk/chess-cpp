#include "piece.h"

Piece::Piece(char color, std::string name, char abbr) : color(color), opponentColor(color == 'w' ? 'b' : 'w'), name(name), abbreviation(abbr)
{
}

// std::vector<std::string> Knight::getPossibleMoves()
// {
//     static const int direction[8][2] = {
//         {-1, 2}, {1, 2},  // front (from white's perspective)
//         {2, 1}, {2, -1},  // right
//         {-1, -2}, {1, -2},  // back
//         {-2, 1}, {-2, -1}  // left
//     };
//     std::vector<std::string> possibleMoves;
//     std::string candidate;

//     for(int i = 0; i < 8; i++){
//         candidate = board->getDestination(position, direction[i][0], direction[i][1]);
//         if(candidate == "-") continue;
//         if(board->getPieceColorAt(candidate) != pieceColor) possibleMoves.push_back(candidate);
//     }

//     return possibleMoves;
// }


// std::vector<std::string> Bishop::getPossibleMoves()
// {
//     std::vector<std::string> possibleMoves;
//     std::string candidate;
//     std::string color;
//     static const int direction[4][2] = {
//         {-1, 1}, {1, 1},
//         {-1, -1}, {1, -1}
//     };

//     for(int i = 0; i < 4; i++){
//         candidate = position;
//         while(true){
//             candidate = board->getDestination(candidate, direction[i][0], direction[i][1]);
//             if(candidate == "-") break;
//             color = board->getPieceColorAt(candidate);
//             if(color == pieceColor){
//                 break;
//             } else if(color == opponentColor){
//                 possibleMoves.push_back(candidate);
//                 break;
//             } else {
//                 possibleMoves.push_back(candidate);
//             }
//         }
//     }

//     return possibleMoves;
// }

// std::vector<std::string> Rook::getPossibleMoves()
// {
//     std::vector<std::string> possibleMoves;
//     std::string candidate;
//     std::string color;
//     static const int direction[4][2] = {
//                 {0, 1},
//         {-1, 0},       {1, 0},
//                 {0, -1}
//     };

//     for(int i = 0; i < 4; i++){
//         candidate = position;
//         while(true){
//             candidate = board->getDestination(candidate, direction[i][0], direction[i][1]);
//             if(candidate == "-") break;
//             color = board->getPieceColorAt(candidate);
//             if(color == pieceColor){
//                 break;
//             } else if(color == opponentColor){
//                 possibleMoves.push_back(candidate);
//                 break;
//             } else {
//                 possibleMoves.push_back(candidate);
//             }
//         }
//     }

//     return possibleMoves;
// }


// std::vector<std::string> Queen::getPossibleMoves()
// {
//     std::vector<std::string> possibleMoves;
//     std::string candidate;
//     std::string color;
//     static const int direction[8][2] = {
//         {-1, 1}, {0, 1}, {1, 1},
//         {-1, 0},         {1, 0},
//         {-1, -1}, {0, -1}, {1, -1}
//     };

//     for(int i = 0; i < 8; i++){
//         candidate = position;
//         while(true){
//             candidate = board->getDestination(candidate, direction[i][0], direction[i][1]);
//             if(candidate == "-") break;
//             color = board->getPieceColorAt(candidate);
//             if(color == pieceColor){
//                 break;
//             } else if(color == opponentColor){
//                 possibleMoves.push_back(candidate);
//                 break;
//             } else {
//                 possibleMoves.push_back(candidate);
//             }
//         }
//     }

//     return possibleMoves;
// }

// std::vector<std::string> King::getPossibleMoves()
// {
//     std::vector<std::string> possibleMoves;

//     possibleMoves = getAttackingSquares();

//     return possibleMoves;
// }

// std::vector<std::string> King::getAttackingSquares()
// {
//     std::vector<std::string> attackingSquares;
//     std::string candidate;
//     std::string color;
//     static const int direction[8][2] = {
//         {-1, 1}, {0, 1}, {1, 1},
//         {-1, 0},         {1, 0},
//         {-1, -1}, {0, -1}, {1, -1}
//     };

//     for(int i = 0; i < 8; i++){
//         candidate = board->getDestination(candidate, direction[i][0], direction[i][1]);
//         if(candidate == "-") continue;
//         color = board->getPieceColorAt(candidate);
//         if(color == pieceColor){
//             continue;
//         } else {
//             attackingSquares.push_back(candidate);
//         }
//     }

//     return attackingSquares;
// }


// std::vector<std::string> getPossibleMoves()
// {
//     std::vector<std::string> possibleMoves;
//     return possibleMoves;
// }

Piece* abbr2piece(char abbreviation)
{
    char abbr;
    char color;
    if('A' < abbreviation && abbreviation < 'Z'){
        abbr = std::tolower(abbreviation, std::locale());
        color = 'w';
    } else if('a' < abbreviation && abbreviation < 'z'){
        abbr = abbreviation;
        color = 'b';
    }
    Piece* piece;
    switch(abbr){
        case 'p':
            piece = new Pawn(color);
            break;
        case 'n':
            piece = new Knight(color);
            break;
        case 'b':
            piece = new Bishop(color);
            break;
        case 'r':
            piece = new Rook(color);
            break;
        case 'q':
            piece = new Queen(color);
            break;
        case 'k':
            piece = new King(color);
            break;
        default:
            piece = new Vacant();
            break;
    }
    return piece;
}
