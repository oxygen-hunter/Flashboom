void aes_crypt_ecb( aes_context *ctx,
                    int mode,
                    const unsigned char input[16],
                    unsigned char output[16] )
{
    int i;
    unsigned long *RK, X0, X1, X2, X3, Y0, Y1, Y2, Y3;

#if defined(XYSSL_PADLOCK_C) && defined(XYSSL_HAVE_X86)
    if( padlock_supports( PADLOCK_ACE ) )
    {
        if( padlock_xcryptecb( ctx, mode, input, output ) == 0 )
            return;
     }
 #endif
 
     RK = ctx->rk;
 
     GET_ULONG_LE( X0, input,  0 ); X0 ^= *RK++;

    if( mode == AES_DECRYPT )
    {
        for( i = (ctx->nr >> 1) - 1; i > 0; i-- )
        {
            AES_RROUND( Y0, Y1, Y2, Y3, X0, X1, X2, X3 );
            AES_RROUND( X0, X1, X2, X3, Y0, Y1, Y2, Y3 );
        }

        AES_RROUND( Y0, Y1, Y2, Y3, X0, X1, X2, X3 );

        X0 = *RK++ ^ ( RSb[ ( Y0       ) & 0xFF ]       ) ^
                     ( RSb[ ( Y3 >>  8 ) & 0xFF ] <<  8 ) ^
                     ( RSb[ ( Y2 >> 16 ) & 0xFF ] << 16 ) ^
                     ( ((unsigned int)RSb[ ( Y1 >> 24 ) & 0xFF ]) << 24 );

        X1 = *RK++ ^ ( RSb[ ( Y1       ) & 0xFF ]       ) ^
                     ( RSb[ ( Y0 >>  8 ) & 0xFF ] <<  8 ) ^
                     ( RSb[ ( Y3 >> 16 ) & 0xFF ] << 16 ) ^
                     ( ((unsigned int)RSb[ ( Y2 >> 24 ) & 0xFF ]) << 24 );

        X2 = *RK++ ^ ( RSb[ ( Y2       ) & 0xFF ]       ) ^
                     ( RSb[ ( Y1 >>  8 ) & 0xFF ] <<  8 ) ^
                     ( RSb[ ( Y0 >> 16 ) & 0xFF ] << 16 ) ^
                     ( ((unsigned int)RSb[ ( Y3 >> 24 ) & 0xFF ]) << 24 );

        X3 = *RK++ ^ ( RSb[ ( Y3       ) & 0xFF ]       ) ^
                     ( RSb[ ( Y2 >>  8 ) & 0xFF ] <<  8 ) ^
                     ( RSb[ ( Y1 >> 16 ) & 0xFF ] << 16 ) ^
                     ( ((unsigned int)RSb[ ( Y0 >> 24 ) & 0xFF ]) << 24 );
    }
    else /* AES_ENCRYPT */
    {
        for( i = (ctx->nr >> 1) - 1; i > 0; i-- )
        {
            AES_FROUND( Y0, Y1, Y2, Y3, X0, X1, X2, X3 );
            AES_FROUND( X0, X1, X2, X3, Y0, Y1, Y2, Y3 );
        }

        AES_FROUND( Y0, Y1, Y2, Y3, X0, X1, X2, X3 );

        X0 = *RK++ ^ ( FSb[ ( Y0       ) & 0xFF ]       ) ^
                     ( FSb[ ( Y1 >>  8 ) & 0xFF ] <<  8 ) ^
                     ( FSb[ ( Y2 >> 16 ) & 0xFF ] << 16 ) ^
                     ( ((unsigned int)FSb[ ( Y3 >> 24 ) & 0xFF ]) << 24 );

        X1 = *RK++ ^ ( FSb[ ( Y1       ) & 0xFF ]       ) ^
                     ( FSb[ ( Y2 >>  8 ) & 0xFF ] <<  8 ) ^
                     ( FSb[ ( Y3 >> 16 ) & 0xFF ] << 16 ) ^
                     ( ((unsigned int)FSb[ ( Y0 >> 24 ) & 0xFF ]) << 24 );

        X2 = *RK++ ^ ( FSb[ ( Y2       ) & 0xFF ]       ) ^
                     ( FSb[ ( Y3 >>  8 ) & 0xFF ] <<  8 ) ^
                     ( FSb[ ( Y0 >> 16 ) & 0xFF ] << 16 ) ^
                     ( ((unsigned int)FSb[ ( Y1 >> 24 ) & 0xFF ]) << 24 );

        X3 = *RK++ ^ ( FSb[ ( Y3       ) & 0xFF ]       ) ^
                     ( FSb[ ( Y0 >>  8 ) & 0xFF ] <<  8 ) ^
                     ( FSb[ ( Y1 >> 16 ) & 0xFF ] << 16 ) ^
                     ( ((unsigned int)FSb[ ( Y2 >> 24 ) & 0xFF ]) << 24 );
    }

    PUT_ULONG_LE( X0, output,  0 );
    PUT_ULONG_LE( X1, output,  4 );
    PUT_ULONG_LE( X2, output,  8 );
    PUT_ULONG_LE( X3, output, 12 );
}


    void solve(vector<vector<char>>& board) {
        if (board.empty()) {
            return;
        }

        queue<pair<int, int>> q;
        for (int i = 0; i < board.size(); ++i) {
            if (board[i][0] == 'O') {
                board[i][0] = 'V';
                q.emplace(i, 0);
            }
            if (board[i][board[0].size() - 1] == 'O') {
                board[i][board[0].size() - 1] = 'V';
                q.emplace(i, board[0].size() - 1);
            }
        }

        for (int j = 1; j < board[0].size() - 1; ++j) {
            if (board[0][j] == 'O') {
                board[0][j] = 'V';
                q.emplace(0, j);
            }
            if (board[board.size() - 1][j] == 'O') {
                board[board.size() - 1][j] = 'V';
                q.emplace(board.size() - 1, j);
            }
        }
        while (!q.empty()) {
            int i, j;
            tie(i, j) = q.front();
            q.pop();
            static const vector<pair<int, int>> directions{{0, -1}, {0, 1},
                                                           {-1, 0}, {1, 0}};
            for (const auto& d : directions) {
                const int x = i + d.first, y = j + d.second;
                if (0 <= x && x < board.size() &&
                    0 <= y && y < board[0].size() &&
                    board[x][y] == 'O') {
                    board[x][y] = 'V';
                    q.emplace(x, y);
                }
            }
        }
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[0].size(); ++j) {
                if (board[i][j] != 'V') {
                    board[i][j] = 'X';
                } else {
                    board[i][j] = 'O';
                }
            }
        }
    }


