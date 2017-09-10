#include "board.h"

void Board::LoadStartingPosition()
{
    board[0][0] = r; board[0][1] = n; board[0][2] = b; board[0][3] = q;
    board[0][4] = k; board[0][5] = b; board[0][6] = n; board[0][7] = r;
    for (int j = 0; j < 8; j++){
        board[1][j] = p;
    }
    for (int i = 2; i < 6; i++){
        for (int j = 0; j < 8; j++){
            board[i][j] = v;
        }
    }
    for (int j = 0; j < 8; j++){
        board[6][j] = P;
    }
    board[7][0] = R; board[7][1] = N; board[7][2] = B; board[7][3] = Q;
    board[7][4] = K; board[7][5] = B; board[7][6] = N; board[7][7] = R;
    //     { r, n, b, q, k, b, n, r },
    //     { p, p, p, p, p, p, p, p },
    //     { v, v, v, v, v, v, v, v },
    //     { v, v, v, v, v, v, v, v },
    //     { v, v, v, v, v, v, v, v },
    //     { v, v, v, v, v, v, v, v },
    //     { P, P, P, P, P, P, P, P },
    //     { R, N, B, Q, K, B, N, R }
}
